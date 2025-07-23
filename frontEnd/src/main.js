import { createApp } from 'vue'
import './style.css'
import App from './App.vue'
import PrimeVue from 'primevue/config'
import Aura from '@primeuix/themes/nora'
import Button from "primevue/button"
import router from './Router'



const app = createApp(App)


app.use(PrimeVue, {
    theme : {
        preset : Aura
    }
});

app.use(router);


app.mount('#app');