import axios from "axios";
import router from "../../Router";
import socket, { loginSocket } from "../socket.js";


export const login = async (email, password)=>{
    try {

        let response = await axios.post("http://localhost:8000/api/v1/auth/login", {
                email : email,
                password : password,
            }
        );

        localStorage.setItem("token" , response.data.token);
        loginSocket(response.data.token);
        axios.defaults.headers.common['Authorization'] = `Bearer ${response.data.token}`;

        router.push('/');
    }catch(err){
        console.log(err);
    }
}

export const register = async (email, username , password, passwordConfirmation)=>{

    try {
        if (password != passwordConfirmation)
            throw ("password confirmation must be the same as password")
        let test = await axios.post("http://localhost:8000/api/v1/auth/register", {
                email,
                username,
                password
            }
        );


        await login(email, password)
    }catch(err){
        if (err.response)
            console.log(err.response.data);
        else
            console.log(err);

    }
}
