const Blog = require('../models/Blogs')

const GetBlog = async (req, res, next) => {
    
    try {
        const blogs = await Blog.find({})
        res.send(blogs)
    } catch (e) {
        res.status(400).send('Unable to get customers')
    }
}

module.exports = GetBlog