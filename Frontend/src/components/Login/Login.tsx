import './Login.css'
import { useRef, useState } from 'react';

interface props {
  setUser: React.Dispatch<React.SetStateAction<{
    name: string;
    id: number;
  }>>
}

const Login: React.FC<props> = ({ setUser }) => {

  const [isRegister, setIsRegister] = useState(false);
  const [message, setMessage] = useState('');

  const login = useRef<HTMLInputElement>(null);
  const password = useRef<HTMLInputElement>(null);
  const rePassword = useRef<HTMLInputElement>(null);

  const checkUserLogin = async () => {
    if (login.current?.value == '' || password.current?.value == '') {
      setMessage('No login or password provided.');
      return;
    }
    try {
      const response = await fetch('http://localhost:5000/api/checkUser?login=' + login.current?.value + '&password=' + password.current?.value)
      if (!response.ok) {
        setMessage('Error while connecting to the API.');
        return;
      }
      const data = await response.text();
      if (data == 'ERROR') {
        setMessage('Error while connecting to the API.');
        return;
      }
      if ((data == 'NOT_OK') || (data == 'FORBIDDEN_LOGIN') || (data == 'FORBIDDEN_PASSWORD')) {
        setMessage('Wrong login and/or password.');
        return;
      }
      setUser({name: login.current!.value, id: parseInt(data)});
      setMessage('');
    } catch (error) {
      setMessage('Error while connecting to the API.');
      return;
    }
  }

  const registerUser = async () => {
    if (login.current?.value == '' || password.current?.value == '') {
      setMessage('No login or password provided.');
      return;
    }
    if (password.current?.value != rePassword.current?.value) {
      setMessage('Passwords do not match!');
      return;
    }

    try {
      const response = await fetch('http://localhost:5000/api/addUser?login=' + login.current?.value + '&password=' + password.current?.value)
      if (!response.ok) {
        setMessage('Error while connecting to the API.');
        return;
      }
      const data = await response.text();
      if (data == 'ERROR') {
        setMessage('Error while connecting to the API.');
        return;
      }
      if (data == 'NOT_OK') {
        setMessage('Wrong login and/or password.');
        return;
      }
      if (data == 'FORBIDDEN_LOGIN') {
        setMessage('Login can contain only letters, numbers and _.');
      }
      if (data == 'FORBIDDEN_PASSWORD') {
        setMessage('Please use different password due to security reasons.');
      }
      if (data == 'USER_EXISTS') {
        setMessage('This login is already taken.');
      }
      if (data == 'OK') {
        setMessage('Account created. Now you can log-in.');
        setIsRegister(false);
      }
    } catch (error) {
      setMessage('Error while connecting to the API.');
      return;
    }
  }

  return (
    <div className='flex flex-col h-screen items-center justify-center bg-sky-500 p-4'>
      <div className='flex flex-col px-8 py-4 bg-white rounded border border-slate-900/10 gap-2'>
        <p className='text-sm italic'>Login:</p>
        <input ref={login} className='border rounded border-slate-900/10 p-1' type='text'/>
        <p className='text-sm italic'>Password:</p>
        <input ref={password} className='border rounded border-slate-900/10 p-1' type='password'/>
        {isRegister && <> <p className='text-sm italic'>Re-type password:</p>
        <input ref={rePassword} className='border rounded border-slate-900/10 p-1' type='password'/></>}
        {message != '' && <div><p className='w-full text-red-500 text-sm text-wrap'>{message}</p></div>}
        <div className='flex flex-row items-center gap-2 justify-between'>
          {isRegister ? <>
          <button onClick={() => {registerUser();}} className='px-4 py-1 bg-sky-500 rounded text-white'>Register</button>
          <button onClick={() => {setIsRegister(false); setMessage('')}} className='py-1 text-sky-500 text-sm underline'>Log in</button>
          </> :
          <>
          <button onClick={() => {checkUserLogin();}} className='px-4 py-1 bg-sky-500 rounded text-white'>Login</button>
          <button onClick={() => {setIsRegister(true); setMessage('')}} className='py-1 text-sky-500 text-sm underline'>Register</button>
          </>
          }
        </div>
      </div>
    </div>
  )
}

export default Login