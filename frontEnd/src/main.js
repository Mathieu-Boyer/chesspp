import { createApp } from 'vue'
import './style.css'
import App from './App.vue'
import PrimeVue from 'primevue/config'
import Aura from '@primeuix/themes/nora'
import router from './Router'
import socket, { loginSocket } from './utils/socket'
import Button from "primevue/button"
import axios from 'axios'

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
    loginSocket(token)
    axios.defaults.headers.common['Authorization'] = `Bearer ${token}`;

}
