import React from 'react'
import { Route, useRouteMatch } from 'react-router-dom'
import AboutMe from './AboutMe'
import Hobbies from './Hobbies'
import EditBlog from './EditBlog'
import DeleteBlog from './DeleteBlog'
import CreateBlog from './CreateBlog'

const HW2 = () => {
  const { path } = useRouteMatch()

  return (
    <>
      <Route component={AboutMe} path={`${path}/aboutme`} />
      <Route component={Hobbies} path={`${path}/hobbies`} />
      <Route component={EditBlog} path={`${path}/edit`} />
      <Route component={DeleteBlog} path={`${path}/delete`} />
      <Route component={CreateBlog} path={`${path}/create`} />
    </>
  )
}

export default HW2
