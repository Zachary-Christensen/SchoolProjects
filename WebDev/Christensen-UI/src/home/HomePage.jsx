import React, { useState, useEffect } from 'react'
import { Container, Button, Table } from 'react-bootstrap'

const HomePage = () => {

  const [data, setData] = useState([])

  useEffect(() => {
    getData("http://localhost:3001/read")
  }, [])

  const getData = async (apiUrl) =>
  {
    fetch(apiUrl)
    .then((response) => response.json())
    .then(json => setData(json))
  }


  return (
    <Container className="justify-content-center">
      <div>Home Page!</div>
      <Table striped bordered>
        <thead>
          <tr>
            <th>Title</th>
            <th>Text</th>
            <th></th>
            <th></th>
          </tr>
        </thead>
        <tbody>
        {
          data.map((info) => {
            return (
              <tr>
                <td>{info.title}</td>
                <td>{info.text}</td>
                <td><Button variant="primary" href={`/hw2/edit?id=${info._id}`}>Edit</Button></td>
                <td><Button variant="danger" href={`/hw2/delete?id=${info._id}`}>Delete</Button></td>
              </tr>
            )})
        }
        </tbody>
      </Table>
      
    </Container>
  )
}

export default HomePage
