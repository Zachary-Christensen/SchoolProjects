const Customer = require('../models/Customers')

const GrantPoints = async (req, res, next) => {
    
    try {
        // const id = req.query.id
        // const points = Number(req.query.points)

        // const oldCustomer = await Customer.findById(id)

        // const newCustomer = await Customer.findByIdAndUpdate(id, {
        //     loyaltyPoints: oldCustomer.loyaltyPoints + points
        // })


        // const newCustomer = await Customer.findByIdAndUpdate(id, {
        //     $inc: {
        //         loyaltyPoints: points
        //     }
        // })

        // res.send(newCustomer)

        // await Customer.updateMany({
        //     lastname: "Weinberg"
        // }, {
        //     loyaltyPoints: 150
        // })

        // res.send('Success!')

        const results = await Customer.find({
            loyaltyPoints: { $gt: 100 }
        }, 'firstName lastName')

        res.send(results)
        
    } catch (e) {
        res.status(400).send('Unable to get customers')
    }
}

module.exports = GrantPoints