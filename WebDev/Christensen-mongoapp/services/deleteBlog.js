const Blog = require('../models/Blogs')

const DeleteBlog = async (req, res, next) => {
    
    try {
        const id = req.query.id

        await Blog.findByIdAndDelete(id)

        res.send("Deleted")
        
    } catch (e) {
        res.status(400).send('Unable to get customers')
    }
}

module.exports = DeleteBlog