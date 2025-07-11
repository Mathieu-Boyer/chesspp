import { Sequelize } from 'sequelize';
import Users from './Users.js';

const sequelize = new Sequelize("chesspp", process.env.SEQUELIZE_USER, process.env.SEQUELIZE_PWD, {
    dialect: 'mariadb'
})


export default {
    sequelize,
    Sequelize,
    Users : Users(sequelize, Sequelize.DataTypes)
}