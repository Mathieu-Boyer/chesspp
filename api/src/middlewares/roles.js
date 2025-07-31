
export const checkRole = (role)=>{
    return (req, res, next)=>{
        console.log(req.role , role)
        if (req.role != role)
            return res.status(403).json({message : "You do not have the correct permission to perform this action"});
        next();
    }
}