import { Router } from "express";
import db from "../models/index.js"
import { authenticate } from "../middlewares/jwt.js";
import { validatePassword } from "../utils/validators.js";
import bcrypt from "bcrypt"

const router = Router();

router.get("/", authenticate , async (req, res)=>{
    const foundUser = await db.Users.findOne({
        where : {
            id : req.id
        }
    })

    res.status(200).json({
        user : foundUser
    });
})

router.put("/", authenticate , async (req, res)=>{
    if (!req.body)
        return res.status(400).json({message : "Body received was null, please enter valid input."})

    let foundUser = await db.Users.findOne({
        where : {
            id : req.id
        }
    })

    const {email, password, username} = req.body;

    email    ? foundUser.email = email : "";
    username ? foundUser.username = username : "";

    if (password){
        try{
            validatePassword(password);
        } catch (err) {
            return res.status(400).json({message : "Password does not respect constraints in the following way: " + err})
        }

        const passwordHash = await bcrypt.hash(password, 10);
        foundUser.password = passwordHash;
    }

    foundUser = await foundUser.save();

    res.status(200).json({
        user : foundUser
    });
})

router.delete("/", authenticate , async (req, res)=>{
    await db.Users.destroy({
        where : {
            id : req.id
        }
    })

    res.status(200).json({
        message : "User was deleted"
    });
})

export default router;