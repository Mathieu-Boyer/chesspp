import axios from "axios";
import router from "../Router"
import { v1 } from "./api";

export const joinQueue = async ()=>{

    try{
        router.push("/queue");
        await axios.post(`${v1}queue/join`);
    }catch (e){
        console.log(e)
    }
}

export const quitQueue = ()=>{
    router.push("/");
}