import React, { useState, useEffect } from 'react'
import {Redirect} from 'react-router-dom';
import { Container, Table, Form, FormControl, Button } from 'react-bootstrap'


const EditBlog = () => {

  const params = new URLSearchParams(window.location.search)
  const idValue = params.get("id")
  console.log(idValue)

  const [id, setID] = useState("")
  const [title, setTitle] = useState("")
  const [text, setText] = useState("")
  const [redirect, setRedirect] = useState(false)

  useEffect(() => {
    getData("http://localhost:3001/read")
  }, [])

  const getData = async (apiUrl) =>
  {
    fetch(apiUrl)
    .then((response) => response.json())
    .then(json => {
        json.filter(x => x._id == idValue).map(x => { setID(x._id); setTitle(x.title); setText(x.text); })
    })
  }

  const handleSubmit = async (e) => {
    e.preventDefault()
    console.log(`Title ${title}`)
    console.log(`Text ${text}`)
    try {
        const bodyStr = JSON.stringify({
          title: title,
          text: text,
        })
        const updateUrl = "http://localhost:3001/updateBlog?id=" + id
        const res = await fetch(updateUrl, {
            method: "PUT",
            headers: {
              'Content-Type': 'application/json'
            },
            body: bodyStr,
        })

        if (res.status === 200) {
            setID("")
            setTitle("")
            setText("Blog updated successfully")
            setRedirect(true)
        }
        else {
            setText("Some error occurred")
        }
    } catch (err) {
        console.log(err)
    }
  }

  const RenderRedirect = () => {
    if (redirect) {
      return <Redirect to="/" />
    }
  }
    
  return (
      <Container className="my-auto">
          <div>edit blog</div>

        <form onSubmit={handleSubmit}>
            <input type="text" value={title} placeholder="Title" onChange={(e) => setTitle(e.target.value)} />
            <input type="textarea" value={text} placeholder="Type blog here" onChange={(e) => setText(e.target.value)} />
            {RenderRedirect()}
            <Button variant="primary" type="submit">
                Update
            </Button>
        </form>

      </Container>
  )
}

export default EditBlog
