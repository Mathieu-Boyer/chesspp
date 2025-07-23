import axios from "axios";
import router from "../Router"

export const joinQueue = async ()=>{

    try{
        await axios.post("http://localhost:8000/api/v1/queue/join");
        router.push("/queue");
    }catch (e){
        console.log(e)
    }
}

export const quitQueue = ()=>{
    router.push("/");
}