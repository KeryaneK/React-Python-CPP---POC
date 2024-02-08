import { useRef, useState } from "react"

interface props {
  user: {
    name: string;
    id: number;
  }
}

const AddPost:React.FC<props> = ({user}) => {

  const [message, setMessage] = useState('');
  const title = useRef<HTMLInputElement>(null);
  const content = useRef<HTMLTextAreaElement>(null);

  const addPost = async () => {
    if (title.current!.value == '' || content.current!.value == '') {
      setMessage('Fields cannot be empty.');
      setTimeout(() => {setMessage('')}, 3000);
      return;
    }
    try {
      const response = await fetch('http://141.147.58.226/api/addPost?title=' + title.current!.value + '&content=' + content.current!.value + '&userId=' + user.id);
      if (!response.ok) {
        setMessage('Error while adding a post.');
        setTimeout(() => {setMessage('')}, 3000);
        return;
      }
      const data = await response.text();
      if (data == 'ERROR') {
        setMessage('Error while adding a post.');
        setTimeout(() => {setMessage('')}, 3000);
        return;
      }
      if (data == 'OK') {
        title.current!.value = '';
        content.current!.value = '';
        setMessage('Post added successfully.');
        setTimeout(() => {setMessage('')}, 3000);
      }

    } catch (error) {
      console.log(error);
    }
  }

  return (
    <div className="flex flex-col px-8 lg:px-32 py-4 justify-center gap-4">
      <p>Title:</p>
      <input ref={title} className="outline-none focus:border-sky-500 border rounded border-slate-900/10 p-1" type='text'/>
      <p>Content:</p>
      <textarea ref={content} className="h-24 outline-none focus:border-sky-500 border rounded border-slate-900/10 p-1"/>
      <div className="flex flex-row items-center justify-end">
        <button onClick={() => {
          addPost();
        }} className="px-4 py-1 bg-sky-500 rounded text-white">Add post</button>
      </div>
      {message != '' && <p className="text-sm text-red-500">{message}</p>}
    </div>
  )
}

export default AddPost