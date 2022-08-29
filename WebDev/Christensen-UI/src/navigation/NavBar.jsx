import React from 'react'
import { Nav, Navbar } from 'react-bootstrap'
import { LinkContainer } from 'react-router-bootstrap'


class NavBar extends React.Component {
  render() {
    return (

      <Navbar bg="dark" variant="dark" className="justify-content-center">
        
        <LinkContainer to="/">
          <Navbar.Brand>Home</Navbar.Brand>
        </LinkContainer>

        <Nav>

          <Nav.Item>
            <LinkContainer to="/hw2/aboutme">
              <Nav.Link>About Me</Nav.Link>
            </LinkContainer>
          </Nav.Item>
          <Nav.Item>
            <LinkContainer to="/hw2/hobbies">
              <Nav.Link>Hobbies</Nav.Link>
            </LinkContainer>
          </Nav.Item>
          <Nav.Item>
            <LinkContainer to="/hw2/create">
              <Nav.Link>Create Blog</Nav.Link>
            </LinkContainer>
          </Nav.Item>

        </Nav>
        
      </Navbar>

    )
  }
}

export default NavBar