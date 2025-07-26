<script setup lang="ts">

import { ref, watch } from 'vue';
import { FloatLabel, InputText, Avatar } from 'primevue';
import 'primeicons/primeicons.css'
import axios from 'axios';
import router from '../Router';
import { useRoute } from 'vue-router';
const route = useRoute()


const navBans = ['/login', '/register', '/queue', '/game'];
const navIsDisplayed = ref(true);
watch(()=>route.fullPath, async (newVal, oldVal) => {
    if (navBans.includes(newVal))
        navIsDisplayed.value = false;
    else
        navIsDisplayed.value = true;

    console.log(newVal)
})

const hover = ref(false);

const searchbarContent = ref('');
const foundUsers = ref([]);
async function handleSearch(){
  console.log(searchbarContent.value)
  console.log(`http://localhost:8000/api/v1/users/?search=${searchbarContent.value}`)
 let response = await axios.get(`http://localhost:8000/api/v1/users/?search=${searchbarContent.value}`);

 console.log(response.data)

 foundUsers.value = response.data.users.slice(0,5)
} 

</script>
<template>
<div v-if="navIsDisplayed" @mouseenter="hover = true" @mouseleave="hover = false"  :class="hover ? 'opened' : 'closed'" class="navBar">

    <div class="searchSection">
        <div class="searchUsers">
            <div v-if="hover" class="searchBarContainer">
                <FloatLabel class="input" variant="on">
                <InputText @input="handleSearch" type="text" v-model="searchbarContent" />
                    <label for="on_label">Search</label>
                </FloatLabel>
                <span class="pi pi-search"></span>
            </div>
            <div class="users">
                <div @click="hover=false,router.push('/profile/'+ user.id)" class="user" v-if="hover && searchbarContent.length > 0" v-for="user in foundUsers"  :key="user.id">
                <Avatar :image="'/avatars/' + user.avatar"></Avatar>
                <h4> {{ user.username }}</h4>
                </div>
            </div>
        </div>
    </div>

  <nav>
        <span @click="router.push('/')" class="navElem">
            <span  class="pi pi-crown"></span>
            <h4 :class="hover ? 'visible' : 'hidden'">Gamemodes</h4>
        </span>
        <span @click="router.push('/profile')" class="navElem">
            <span  class="pi pi-user"></span>
            <h4 :class="hover ? 'visible' : 'hidden'">Profile</h4>
        </span>
  </nav>

  <div></div>
</div>
</template>

<style scoped>
.navBar{
  display: flex;
  flex-direction: column;

  justify-content: space-between;
  align-items: center;
  height: 100vh;
  width: 100%;

  padding: 2rem;
  background-color: #161616;
  border-right: 1px solid #2b2b2b;
  position: fixed;

  transition: all .5s;
}

.searchSection {
    display: flex;
    flex-direction: column;
    width: 100%;
}

.opened{
  width: 20rem;
}

.closed{
  width: 2rem;
}



.searchUsers{
  position: relative;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-direction: column;
  width: 100%;
}

.searchBarContainer{
  display: flex;
  align-items: center;
  gap: 1rem;
  width: 100%;
  height: 3rem;
}

.searchBarContainer .pi {
  font-size: 1.5rem;
}

.input {
  width: 80%;
  height: 100%;
}

input {
  width: 100%;
  height: 100%;
}

.users{
  top: 100%;
  position: absolute;
  width: 100%;
  display: flex;
  justify-content: flex-start;
  align-items: flex-start;
  flex-direction: column;
}

.user{
  width: 80%;
  display: flex;
  justify-content: flex-start;
  gap: 1rem;
  align-items: center;
  padding: 1rem;
  background-color: rgb(38, 38, 38);
  border-bottom: 1px solid rgb(33, 33, 33);;
}


.user:hover{
  background-color: rgb(49, 49, 49);
  cursor: pointer;
}



.navElem{
    margin: 2rem 0;
    display: flex;
    align-items: center;
    justify-content: flex-start;
    gap: 1rem;
    cursor: pointer;
}


.hidden{
    display: none;
    transition: all .2s;
}

.visible{
    visibility: block;
    transition: all 1s;
}



.navElem .pi {
    font-size: 1.5rem;
}
</style>