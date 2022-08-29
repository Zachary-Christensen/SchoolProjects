require('dotenv').config()
const app = require('./index')
const mongoose = require('mongoose')

const port = 3001

mongoose.connect(process.env.CONNECTION_STRING, { useNewUrlParser: true, useUnifiedTopology: true }, err => {
  if (err) {
    console.log('Oh no', err)
    return
  }

  console.log('Connected!')
  app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`)
  })
})

