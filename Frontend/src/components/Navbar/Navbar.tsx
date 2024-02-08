import { useState } from "react";
import { Link } from "react-router-dom";

const Navbar = () => {
  const [isMenuVisible, setIsMenuVisible] = useState(false);

  return (

    <nav className='flex flex-col px-8 lg:px-32 py-4 backdrop-blur-md bg-white/60 border border-slate-900/10 sticky z-50 top-0'>
      <div className="flex items-center justify-between">
        <div className="lg:w-auto flex justify-center items-center gap-4">
          <p className="text-xl font-semibold">PostSite</p>
        </div>
        <div className="hidden md:flex items-center justify-center gap-4 flex-wrap">
          <Link onClick={() => {setIsMenuVisible(false);}} to='/' className="text-lg font-medium hover:text-sky-500">Mainpage</Link>
          <Link onClick={() => {setIsMenuVisible(false);}} to='/userPosts' className="text-lg font-medium hover:text-sky-500">My posts</Link>
          <Link onClick={() => {setIsMenuVisible(false);}} to='/addPost' className="text-lg font-medium hover:text-sky-500">Add post</Link>
        </div>
        <button onClick={() => {
          setIsMenuVisible(current => {return !current})
        }} className="flex md:hidden items-center justify-center"><span className="material-symbols-outlined text-2xl font-medium">menu</span></button>
      </div>
      {isMenuVisible &&
      <div className="flex flex-col gap-2">
        <div className='border-b border-slate-900/10'></div>
        <Link onClick={() => {setIsMenuVisible(false);}} to='/' className="text-lg flex items-center justify-end px-2 py-1 border rounded-md border-slate-900/10 text-slate-700 font-medium">Mainpage</Link>
        <Link onClick={() => {setIsMenuVisible(false);}} to='/userPosts' className="text-lg flex items-center justify-end px-2 py-1 border rounded-md border-slate-900/10 text-slate-700 font-medium">My posts</Link>
        <Link onClick={() => {setIsMenuVisible(false);}} to='/addPost' className="text-lg flex items-center justify-end px-2 py-1 border rounded-md border-slate-900/10 text-slate-700 font-medium">Add post</Link>
      </div>
      }

    </nav>
  )
}

export default Navbar