import { Sequelize } from 'sequelize';
import Users from './Users.js';
import Games from './Games.js';


console.log(process.env.SEQUELIZE_USER, process.env.SEQUELIZE_PWD);
const sequelize = new Sequelize("chesspp", process.env.SEQUELIZE_USER, process.env.SEQUELIZE_PWD, {
    dialect: 'mariadb'
})


export default {
    sequelize,
    Sequelize,
    Users : Users(sequelize, Sequelize.DataTypes),
    Games : Games(sequelize, Sequelize.DataTypes)
}