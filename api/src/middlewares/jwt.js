import jwt from "jsonwebtoken"

export const authenticate = (req, res, next)=>{
    const authHeader = req.headers.authorization;
    if (!authHeader)
        return res.status(400).json("A token must be provided.");
    const token = authHeader.split(" ")[1];
    if (!token)
        return res.status(400).json("Token format is not respected");

    try {
        const decoded = jwt.verify(token, process.env.JWT_SECRET);
        req.id = decoded.id;
        req.email = decoded.email;
        req.username = decoded.username;
        req.role = decoded.role;
        next();
    }
    catch (err){

        console.log(err);
        return res.status(400).json("Token didn't pass verification", err);
    }
}