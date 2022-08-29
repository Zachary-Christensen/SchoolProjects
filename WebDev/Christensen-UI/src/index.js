import React from 'react'
import ReactDOM from 'react-dom'
import HW2 from './hw2/HW2'
import HomePage from './home/HomePage'
import { BrowserRouter, Route } from 'react-router-dom'
import NavBar from './navigation/NavBar'
import 'bootstrap/dist/css/bootstrap.min.css'

const AppContainer = () => {
  return (
    <BrowserRouter>
      <NavBar style={{ marginBottom: '10px' }} />
      <Route component={HomePage} exact path='/' />
      <Route component={HW2} path='/hw2' />
    </BrowserRouter>
  )
}


ReactDOM.render(<AppContainer />, document.querySelector('#root'))

