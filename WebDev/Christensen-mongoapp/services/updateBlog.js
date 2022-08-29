const Blog = require('../models/Blogs')

const UpdateBlog = async (req, res, next) => {
    
    try {
        const id = req.query.id

        const oldBlog = await Blog.findByIdAndUpdate(id, {
            title: req.body.title,
            text: req.body.text
        })

        const newBlog = await Blog.findById(id)

        res.send(newBlog)
        
    } catch (e) {
        res.status(400).send('Unable to get customers')
    }
}

module.exports = UpdateBlog