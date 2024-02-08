import { useState, useEffect } from "react"

const Mainpage = () => {

  const [posts, setPosts] = useState<{id: number, title: string, content: string, user: string}[] | null>(null);
  const [status, setStatus] = useState('LOADING');

  useEffect(() => {
    fetchPosts();
  }, []);

  const fetchPosts = async () => {
    try {
      const response = await fetch('http://141.147.58.226/api/getPosts?userId=all');
      if (!response.ok) {
        setStatus('ERROR');
        return;
      }
      const data = await response.json();
      if (data == 'NO_POSTS') {
        setStatus('NO_POSTS');
        return;
      }
      if (data == 'ERROR') {
        setStatus('ERROR');
        return;
      }
      setStatus('OK');
      const object = JSON.parse(data);
      setPosts(object);
    } catch (error) {
      console.log(error);
    }
  }

  return (
    <div className="flex flex-col px-8 lg:px-32 py-4 items-center justify-center gap-4">

      <p className="text-2xl text-sky-500 italic semibold">All posts:</p>

      {status == 'LOADING' && <p className="text-xl font-semibold">Loading posts...</p>}
      {status == 'ERROR' && <p className="text-xl font-semibold">There is a problem with the API. Please try again later.</p>}
      {status == 'NO_POSTS' && <p className="text-xl font-semibold">No posts currently in the database.</p>}

      {status == 'OK' && posts?.map(post => (
        <div key={post.id} className="w-full flex flex-col px-4 py-2 border rounded bg-slate-200 border-slate-900/10 gap-2">
    
          <p className="text-xl font-semibold">{post.title}</p>
          <div className="border-b border-slate-900/10"/>
          <p className="">{post.content}</p>
          <div className="border-b border-slate-900/10"/>
          <p className="text-xs italic place-self-end text-slate-900/60">Created by {post.user}</p>
        </div>
      ))}
      
    </div>
  )
}

export default Mainpage