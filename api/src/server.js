import express from 'express'
import { Sequelize } from 'sequelize';


const app = express();

app.listen(8000, ()=>{
    console.log("listening on port 8000");
})

const sequelize = new Sequelize("chesspp", process.env.SEQUELIZE_USER, process.env.SEQUELIZE_PWD, {
    dialect: 'mariadb'
})

try {
    await sequelize.authenticate();
    console.log("DB succesfuly connected.");
} catch (err) {
    console.error("Credential error for DB");
}