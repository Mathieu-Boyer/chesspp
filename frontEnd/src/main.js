import { createApp } from 'vue'
import './style.css'
import App from './App.vue'
import PrimeVue from 'primevue/config'
import Aura from '@primeuix/themes/nora'
import router from './Router'
import socket, { loginSocket } from './utils/socket'
import Button from "primevue/button"
import axios from 'axios'
import game from './utils/board/game'
import { quitQueue } from './utils/queue'

const app = createApp(App)

app.use(PrimeVue, {
    theme : {
        preset : Aura
    }
});

app.use(router);
app.mount('#app');


const token = localStorage.getItem("token");

if (token){
    axios.defaults.headers.common['Authorization'] = `Bearer ${token}`;
    await quitQueue();
    await loginSocket(token)
}else{
    router.push("/login")
}


router.beforeEach((to, from, next) => {
  if (game.gameInfos) {
    console.log(game.gameInfos)
    
    if (game.gameInfos.status === "active" && to.path !== "/game") {
      return next("/game")
    }

    if (game.gameInfos.status === "selection" && to.path !== "/game/selection") {
      return next("/game/selection")
    }
  }

  next()
})
