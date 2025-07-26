import { Router } from "express";
import db from "../models/index.js"
import { Op } from "sequelize";
import { authenticate } from "../middlewares/jwt.js";
import { checkRole } from "../middlewares/roles.js";

const like = Op.like;

const router = Router();

router.get("/", authenticate, async (req, res)=>{
    let foundUsers;
    if (req.query && req.query.search)
        foundUsers = await db.Users.findAll({ where: { username : { [like] : `%${req.query.search}%` }}})
    else
        foundUsers = await db.Users.findAll();
    res.status(200).json({users : foundUsers});
})


router.get("/:id", authenticate, async (req, res)=>{
    const id = req.params.id;
    if (!id)
        return res.status(400).json({message : "You must provide an id to use this route."})

    const foundUser = await db.Users.findOne({
        where : {
            id : id
        }
    })
    if(!foundUser)
        return res.status(404).json({message : "User not found."})

    res.status(200).json({
        user : foundUser
    });
})

router.put("/:id", authenticate, checkRole("admin") ,async (req, res)=>{

    if (!req.body)
        return res.status(400).json({message : "Body received was null, please enter valid input."})

    const id = req.params.id;
    if (!id)
        return res.status(400).json({message : "You must provide an id to use this route."})

    let foundUser = await db.Users.findOne({
        where : {
            id : id
        }
    })
    if(!foundUser)
        return res.status(404).json({message : "User not found."})

    const {email, username} = req.body;

    email    ? foundUser.email = email : "";
    username ? foundUser.username = username : "";


    foundUser = await foundUser.save();
    res.status(200).json({
        user : foundUser
    });
})

router.delete("/:id", authenticate, checkRole("admin") ,async (req, res)=>{

    const id = req.params.id;
    if (!id)
        return res.status(400).json({message : "You must provide an id to use this route."})

    await db.Users.destroy({
        where : {
            id : id
        }
    })

    res.status(200).json({
        message : "User was deleted."
    });
})

export default router;