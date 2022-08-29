const Blog = require('../models/Blogs')

const CreateBlog = async (req, res, next) => {
    
    try {
        const blog = new Blog({
            title: req.body.title,
            text: req.body.text
        })

        const result = await blog.save()

        res.send(result)
    } catch (e) {
        res.status(400).send('Youre missing something')
    }
}

module.exports = CreateBlog