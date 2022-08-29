import React, { useState, useEffect } from 'react'
import {Redirect} from 'react-router-dom';
import { Container, Table, Form, FormControl, Button } from 'react-bootstrap'


const CreateBlog = () => {

  const [title, setTitle] = useState("")
  const [text, setText] = useState("")
  const [redirect, setRedirect] = useState(false)

  const handleSubmit = async (e) => {
    e.preventDefault()
    console.log(`Title ${title}`)
    console.log(`Text ${text}`)
    try {
        const bodyStr = JSON.stringify({
          title: title,
          text: text,
        })
        const createUrl = "http://localhost:3001/createBlog"
        const res = await fetch(createUrl, {
            method: "POST",
            headers: {
              'Content-Type': 'application/json'
            },
            body: bodyStr,
        })

        if (res.status === 200) {
            setTitle("")
            setText("Blog create successfully")
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
          <div>create blog</div>

        <form onSubmit={handleSubmit}>
            <input type="text" value={title} placeholder="Title" onChange={(e) => setTitle(e.target.value)} />
            <input type="textarea" value={text} placeholder="Type blog here" onChange={(e) => setText(e.target.value)} />
            {RenderRedirect()}
            <Button variant="primary" type="submit">
                Create
            </Button>
        </form>

      </Container>
  )
}

export default CreateBlog
