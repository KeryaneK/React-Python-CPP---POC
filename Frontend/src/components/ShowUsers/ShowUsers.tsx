import { useState, useEffect } from "react";

const ShowUsers = () => {

  const [users, setUsers] = useState<{id: string, login: string, isAdmin: string}[] | null>(null);
  const [status, setStatus] = useState('LOADING');

  useEffect(() => {
    fetchUsers();
  }, []);

  const fetchUsers = async () => {
    try {
      const response = await fetch('http://141.147.58.226/api/getUsers');
      if (!response.ok) {
        setStatus('ERROR');
        return;
      }
      const data = await response.json();
      if (data == 'ERROR') {

        setStatus('ERROR');
        return;
      }
      setStatus('OK');
      const object = JSON.parse(data);
      setUsers(object);
    } catch (error) {
      console.log(error);
    }
  }
  
  return (
    <div className="flex flex-col px-8 lg:px-32 py-4 items-center justify-center gap-4">

      <p className="text-2xl text-sky-500 italic semibold">All users (ADMIN):</p>

      {status == 'LOADING' && <p className="text-xl font-semibold">Loading users...</p>}
      {status == 'ERROR' && <p className="text-xl font-semibold">There is a problem with the API. Please try again later.</p>}

      {status == 'OK' && users?.map(user => (
        <div key={user.id} className="w-full flex flex-row items-center px-4 py-2 border rounded bg-slate-200 border-slate-900/10 gap-2">
          <p>{user.id}:</p>
          <p>{user.login}</p>
          <p className="text-xs italic text-slate-900/60">Admin: {user.isAdmin}</p>
        </div>
      ))}
      
    </div>
  )
}

export default ShowUsers