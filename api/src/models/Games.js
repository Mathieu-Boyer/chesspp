        // whitePlayerId : {
        //     type: DataTypes.INTEGER,
        //     references : {
        //         model : "Users",
        //         key: "id",
        //     },
        //     allowNull : false,
        // },
        // blackPlayerId : {
        //     type: DataTypes.INTEGER,
        //     references : {
        //         model : "Users",
        //         key: "id",
        //     },
        //     allowNull : false,
        // },
        // winnerId : {
        //     type: DataTypes.INTEGER,
        //     references : {
        //         model : "Users",
        //         key: "id",
        //     },
        //     allowNull : true,
        // },
        // drawProposerId : {
        //     type: DataTypes.INTEGER,
        //     references : {
        //         model : "Users",
        //         key: "id",
        //     },
        //     allowNull : true,
        // },
export default (sequelize, DataTypes)=>{
    const Games = sequelize.define("Games",{
        status : {
            type: DataTypes.STRING
        },
        fenList : {
            type : DataTypes.JSON,
        },
        moveList : {
            type : DataTypes.JSON,
            allowNull : true,
        },
        colorToPlay : {
            type : DataTypes.STRING,
            default : "White"
        },
        blackSelectedPiece : {
            type: DataTypes.STRING,
            defaultValue : "-"
        },
        whiteSelectedPiece : {
            type : DataTypes.STRING,
            defaultValue : "-"
        },
        whitePlayerId : {
            type: DataTypes.INTEGER,
            references : {
                model : "Users",
                key: "id",
            },
            allowNull : false,
        },
        blackPlayerId : {
            type: DataTypes.INTEGER,
            references : {
                model : "Users",
                key: "id",
            },
            allowNull : false,
        },
        winnerId : {
            type: DataTypes.INTEGER,
            references : {
                model : "Users",
                key: "id",
            },
            allowNull : true,
        },
        drawProposerId : {
            type: DataTypes.INTEGER,
            references : {
                model : "Users",
                key: "id",
            },
            allowNull : true,
        }
    })
    Games.prototype.toJSON = function (){
        const values = { ...this.get() };
        delete values.whitePlayerId;
        delete values.blackPlayerId;
        delete values.winnerId;
        delete values.drawProposerId;
        return values;
    }
    return Games;
}