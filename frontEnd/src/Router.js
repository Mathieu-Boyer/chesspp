import { createRouter, createWebHistory } from 'vue-router'

import Login from './pages/login.vue'
import Register from './pages/register.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/login',
      name: 'login',
      component: Login ,
    },
    {
      path: '/register',
      name: 'register',
      component: Register ,
    }
  ],
})

export default router