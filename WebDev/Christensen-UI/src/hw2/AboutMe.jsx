import React from 'react'
import { Container, Image } from 'react-bootstrap'
import zeroAndOne from '../images/zeroAndOne.jpg'


const AboutMe = () => {
  return (
      <Container className="my-auto">
        <div>I am a computer science student. It is amazing to see how far a little logic can go</div>

        <Image src={zeroAndOne}></Image>
      </Container>
  )
}

export default AboutMe
