import express from 'express'
import db from './models/index.js';
import auth from './routes/Auth.js';
const app = express();

app.use(express.json())

app.listen(8000, ()=>{
    console.log("listening on port 8000");
})


app.use("/api/v1/auth", auth)
try {
    // await db.Users.drop();

    // await db.sequelize.sync()
    await db.sequelize.authenticate()

    console.log("Connected to DB.")

} catch (err) {
    console.error("Credential error for DB", err.message);
}
