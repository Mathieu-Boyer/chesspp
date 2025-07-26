<script setup lang="ts">
import { Suspense } from 'vue';
import { RouterView } from 'vue-router'
import { ref } from 'vue';
import { FloatLabel, InputText, Avatar } from 'primevue';
import 'primeicons/primeicons.css'
import axios from 'axios';
const hover = ref(false);
const userHover = ref(-1);
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
<div @mouseenter="hover = true" @mouseleave="hover = false"  :class="hover ? 'opened' : 'closed'" class="navBar">

    <div class="searchUsers">
      <div v-if="hover" class="searchBarContainer">
        <FloatLabel class="input" variant="on">
           <InputText @input="handleSearch" type="text" v-model="searchbarContent" />
            <label for="on_label">Search</label>
        </FloatLabel>
        <span class="pi pi-search"></span>
    </div>

    <div class="users">


        <div class="user" v-if="hover && searchbarContent.length > 0" v-for="user in foundUsers"  :key="user.id">
          <Avatar :image="'/avatars/' + user.avatar"></Avatar>
          <h4> {{ user.username }}</h4>

        </div>
    </div>

  </div>

</div>
<Suspense>
    <template #default>
      <RouterView />
    </template>
    <template #fallback>
      <div>...loading</div>
    </template>
</Suspense>

</template>

<style scoped>
.navBar{
  display: flex;
  align-items: self-start;
  justify-content: center;
  height: 100vh;
  padding: 2rem 1rem;
  background-color: #161616;
  border-right: 1px solid #2b2b2b;
  position: fixed;

  transition: all .5s;
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
</style>