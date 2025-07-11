import bcrypt from "bcrypt"

export const validatePassword = (password)=>{
    if (password.length < 7)
        throw "password is too short."
    if (password.includes(" "))
        throw "password cannot contain any space."
}

export const comparePasswords = async (realPasswordHash, receivedPassword)=>{
    if (!(await bcrypt.compare(receivedPassword, realPasswordHash)))
        throw "Invalid password, please try again";
}