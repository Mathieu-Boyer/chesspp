import axios from "axios";
import router from "../Router"

export const joinQueue = async ()=>{

    try{
        router.push("/queue");
        await axios.post("http://localhost:8000/api/v1/queue/join");
    }catch (e){
        console.log(e)
    }
}

export const quitQueue = ()=>{
    router.push("/");
}