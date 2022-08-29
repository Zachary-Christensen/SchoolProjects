import React, { useState, useEffect } from 'react'
import {Redirect} from 'react-router-dom';
import { Container, Table, Form, FormControl, Button } from 'react-bootstrap'


const DeleteBlog = () => {

  const [redirect, setRedirect] = useState(false)

  const params = new URLSearchParams(window.location.search)
  const idValue = params.get("id")
  console.log(idValue)

  useEffect(() => {
    getData("http://localhost:3001/deleteBlog/?id=" + idValue)
  }, [])

  const getData = async (apiUrl) =>
  {
    await fetch(apiUrl, { method: "DELETE" })

    setRedirect(true)
  }
  const RenderRedirect = () => {
    if (redirect) {
      return <Redirect to="/" />
    }
  }
  return (
      <>
      {RenderRedirect()}
      </>
  )
}

export default DeleteBlog
