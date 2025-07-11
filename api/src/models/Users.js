export default (sequelize, DataTypes)=>{
    let Users = sequelize.define("Users", {
        username: {
            type: DataTypes.STRING,
            allowNull: false,
            unique: true,
        },
        role: {
            type: DataTypes.STRING,
            allowNull: false,
        },
        email: {
            type: DataTypes.STRING,
            allowNull : false,
            unique : true,
            validate : {
                isEmail : true,
            }
        },
        password: {
            type: DataTypes.STRING,
            allowNull: false,
        }
    });

    Users.prototype.toJSON = function (){
        const values = { ...this.get() };
        delete values.password;
        return values;
    }
    return Users;
};