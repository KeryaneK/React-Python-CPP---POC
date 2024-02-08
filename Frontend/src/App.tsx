import './App.css'
import { Routes, Route } from "react-router-dom"

function App() {

  return (
    <>
      <Routes>
        <Route path='/' element={<></>}/>
        <Route path='/addPost' element={<></>}/>
        <Route path='/userPosts' element={<></>}/>
      </Routes>
    </>
  )
}

export default App
