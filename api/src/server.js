import express from 'express'
import db from './models/index.js';
import auth from './routes/Auth.js';
import userSelf from './routes/UserSelf.js';
import user from './routes/User.js';
import queue from './routes/Queue.js';
import { authenticate } from './middlewares/jwt.js';
import { checkRole } from './middlewares/roles.js';


const app = express();

app.use(express.json())

app.listen(8000, ()=>{
    console.log("listening on port 8000");
})


app.use("/api/v1/auth", auth);
app.use("/api/v1/users/self", userSelf);
app.use("/api/v1/users", user);
app.use("/api/v1/queue", queue);


app.post("/testing_jwt", authenticate, (req, res)=>{
    console.log(req.id , req.email, req.username, req.role)
    res.json("token passed validation !!")
});

app.post("/testing_role_protection", authenticate , checkRole("admin"), (req, res)=>{
    console.log(req.id , req.email, req.username, req.role)
    res.json("role validated !!")
});

try {
    // await db.Users.drop();

    // await db.sequelize.sync()
    await db.sequelize.authenticate()

    console.log("Connected to DB.")

} catch (err) {
    console.error("Credential error for DB", err.message);
}
