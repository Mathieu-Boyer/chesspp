import express from 'express'
import db from './models/index.js';
import auth from './routes/Auth.js';
import { authenticate } from './middlewares/jwt.js';
const app = express();

app.use(express.json())

app.listen(8000, ()=>{
    console.log("listening on port 8000");
})


app.use("/api/v1/auth", auth)
app.post("/testing_jwt", authenticate, (req, res)=>{
    console.log(req.id , req.email, req.username, req.role)
    res.json("token passed validation !!")
});

try {
    // await db.Users.drop();

    // await db.sequelize.sync()
    await db.sequelize.authenticate()

    console.log("Connected to DB.")

} catch (err) {
    console.error("Credential error for DB", err.message);
}
