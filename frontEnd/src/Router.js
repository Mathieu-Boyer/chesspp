import { createRouter, createWebHistory } from 'vue-router'

import Login from './pages/login.vue'
import Register from './pages/register.vue'
import Index from './pages/index.vue'
import queue from './pages/queue.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'index',
      component: Index ,
    },
    {
      path: '/queue',
      name: 'queue',
      component: queue ,
    },
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