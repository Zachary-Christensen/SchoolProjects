const express = require('express')
const app = express()
const { corsOptionsRequests, corsSimpleRequests } = require('./middleware/cors')
const bodyParser = require('body-parser')
const removePoweredBy = require('./middleware/removePoweredBy')
const req = require('express/lib/request')
const GetBlogs = require('./services/getBlogs')
const CreateBlog = require("./services/createBlog")
const UpdateBlog = require("./services/updateBlog")
const DeleteBlog = require("./services/deleteBlog")

app.options('*', corsOptionsRequests)
app.use(corsSimpleRequests)
app.use(bodyParser.json())
app.use(bodyParser.urlencoded({ extended: true }))
app.use(removePoweredBy)

app.get('/read', GetBlogs)
app.post('/createBlog', CreateBlog)
app.put('/updateBlog', UpdateBlog)
app.delete('/deleteBlog', DeleteBlog)

module.exports = app