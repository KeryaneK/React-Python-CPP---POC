import { useState } from 'react'
import { Routes, Route, Navigate } from "react-router-dom"

import AddPost from './components/AddPost/AddPost'
import Login from './components/Login/Login'
import Mainpage from './components/Mainpage/Mainpage'
import Navbar from './components/Navbar/Navbar'
import UserPosts from './components/UserPosts/UserPosts'


function App() {

  const [user, setUser] = useState({name: 'none', id: 0})

  return (
    <>
      {user.name != 'none' ? <Navbar/> : <></>}

      <Routes>
        {user.name == 'none' ?
        <>
          <Route path='/' element={<Navigate to='/login'/>}/>
          <Route path='/addPost' element={<Navigate to='/login'/>}/>
          <Route path='/userPosts' element={<Navigate to='/login'/>}/>
          <Route path='/login' element={<Login setUser={setUser} />}/>
        </>
        :
        <>
          <Route path='/' element={<Mainpage/>}/>
          <Route path='/addPost' element={<AddPost user={user}/>}/>
          <Route path='/userPosts' element={<UserPosts user={user} />}/>
          <Route path='/login' element={<Navigate to='/'/>}/>
        </>
        }
      </Routes>
    </>
  )
}

export default App
