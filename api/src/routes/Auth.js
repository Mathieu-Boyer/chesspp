import { Router } from "express";
import bcrypt from "bcrypt"
import db  from "../models/index.js";
import { comparePasswords, validatePassword } from "../utils/validators.js";
import { where } from "sequelize";
const router = Router();
const Users = db.Users;

router.post("/register", async (req, res)=>{

    if (!req.body)
        return res.status(400).json({message : "Body received was null, please enter valid input."})

    const { email, username, password } = req.body;

    const foundUser = await Users.findOne({
        where : {email: email}
    })
    if (foundUser)
        return res.status(400).json({message : "This email is already associated to an account. Try to log in instead"})

    try{
        validatePassword(password);
    } catch (err) {
        return res.status(400).json({message : "Password does not respect constraints in the following way: " + err})
    }
    
    try {
        const passwordHash = await bcrypt.hash(password, 10);
        const user = await Users.create({ email, username, password: passwordHash })
        res.status(201).json({message : "User created.", user: user})
    } catch (error) {
        res.status(409).json({message : "A user with these credentials already exists.", error})
    }
})


router.post("/login", async (req, res)=>{
    if (!req.body)
        return res.status(400).json({message : "Body received was null, please enter valid input."})

    const { email, password } = req.body;
    const foundUser = await Users.findOne({
        where : {email: email}
    })

    if (!foundUser)
        return res.status(400).json({message : "This email is not associated to any account."})
    try{
        await comparePasswords(foundUser.password, password);
    } catch (err) {
        return res.status(400).json({message : err})
    }
    // implement the creation of jwt.
    res.status(200).json({message: "Login sucessful", token : "no Token for now cause not implemented rn"})
})


export default router;