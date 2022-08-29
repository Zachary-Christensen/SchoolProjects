import React from 'react'
import { Container, Image } from 'react-bootstrap'
import squirrels from '../images/squirrels.jpg'

const Hobbies = () => {
  return (

      <Container className="my-auto">
        <div>Squirrels are fun creatures when they are not destoying something</div>

        <Image src={squirrels}></Image>
      </Container>

  )
}

export default Hobbies