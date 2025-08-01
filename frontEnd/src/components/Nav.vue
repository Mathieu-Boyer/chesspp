<script setup lang="ts">
import { ref, watch, onMounted, onBeforeUnmount } from 'vue';
import { FloatLabel, InputText, Avatar } from 'primevue';
import 'primeicons/primeicons.css';
import axios from 'axios';
import router from '../Router';
import { useRoute } from 'vue-router';
import { v1 } from '../utils/api';

const route = useRoute();
const navBans = ['/login', '/register', '/queue', '/game', '/game/selection'];

const navIsDisplayed = ref(true);
const isMobile = ref(false);
const hover = ref(false);
const manualToggle = ref(false);

const searchbarContent = ref('');
const foundUsers = ref([]);

watch(() => route.fullPath, (newVal) => {
  navIsDisplayed.value = !navBans.includes(newVal);
});

function updateDeviceMode() {
  isMobile.value = window.innerWidth <= 768;
}

function toggleMobileNav() {
  manualToggle.value = !manualToggle.value;
}

async function handleSearch() {
  if (!searchbarContent.value) {
    foundUsers.value = [];
    return;
  }
  const response = await axios.get(`${v1}users/?search=${searchbarContent.value}`);
  foundUsers.value = response.data.users.slice(0, 5);
}

function handleLogout() {
  localStorage.removeItem('token');
  hover.value = true;
  router.push('/login');
}

onMounted(() => {
  updateDeviceMode();
  window.addEventListener('resize', updateDeviceMode);
});

onBeforeUnmount(() => {
  window.removeEventListener('resize', updateDeviceMode);
});
</script>

<template>
  <div v-if="navIsDisplayed && isMobile" class="burgerButton" @click="toggleMobileNav">
    <span class="pi pi-bars"></span>
  </div>


  <div
    v-if="navIsDisplayed"
    class="navBar"
    @mouseenter="!isMobile && (hover = true)"
    @mouseleave="!isMobile && (hover = false)"
    :class="[
      isMobile ? (manualToggle ? 'opened' : 'closed') : (hover ? 'opened' : 'closed')
    ]"
  >

    <div class="searchSection">
      <div class="searchUsers">
        <div v-if="hover || isMobile && manualToggle" class="searchBarContainer">
          <FloatLabel class="input" variant="on">
            <InputText @input="handleSearch" type="text" v-model="searchbarContent" />
            <label for="on_label">Search</label>
          </FloatLabel>
          <span class="pi pi-search"></span>
        </div>
        <div class="users">
          <div
            v-for="user in foundUsers"
            :key="user.id"
            class="user"
            v-if="(hover || isMobile && manualToggle) && searchbarContent.length > 0"
            @click="hover = false; manualToggle = false; router.push('/profile/' + user.id)"
          >
            <Avatar :image="'/avatars/' + user.avatar" />
            <h4>{{ user.username }}</h4>
          </div>
        </div>
      </div>
    </div>


    <nav :style="{ padding: hover || (isMobile && manualToggle) ? '0 2rem' : '0' }">
      <span @click="manualToggle = false , router.push('/')" class="navElem">
        <span class="pi pi-crown"></span>
        <h4 :class="hover || (isMobile && manualToggle) ? 'visible' : 'hidden'">Gamemodes</h4>
      </span>
      <span @click="manualToggle = false ,router.push('/profile')" class="navElem">
        <span class="pi pi-user"></span>
        <h4 :class="hover || (isMobile && manualToggle) ? 'visible' : 'hidden'">Profile</h4>
      </span>
    </nav>


    <div @click="handleLogout" class="disconnectContainer">
      <span class="pi pi-sign-out"></span>
      <h6 :class="hover || (isMobile && manualToggle) ? 'visible' : 'hidden'">sign-out</h6>
    </div>
  </div>
</template>

<style scoped>
.navBar {
  display: flex;
  flex-direction: column;
  justify-content: space-between;
  align-items: center;
  height: 100vh;
  padding: 1rem;
  background-color: #161616;
  border-right: 1px solid #2b2b2b;
  position: fixed;
  top: 0;
  left: 0;
  transition: all 0.5s;
  z-index: 999;
}

.opened {
  width: 20rem;
}

.closed {
  width: 4rem;
}

@media (max-width: 768px) {
  .opened {
    transform: translateX(0);
  }

  .closed {
    transform: translateX(-100%);
  }

  .navBar {
    width: 20rem !important;
    height: 100vh;
    transition: transform 0.3s ease-in-out;
  }
}

.burgerButton {
  position: fixed;
  top: 1rem;
  left: 1rem;
  background-color: #161616;
  border: 1px solid #2b2b2b;
  border-radius: 0.5rem;
  padding: 0.5rem;
  z-index: 1000;
  cursor: pointer;
  display: none;
}

.burgerButton .pi {
  font-size: 1.5rem;
  color: white;
}



.searchSection {
  display: flex;
  flex-direction: column;
  width: 100%;
  min-height: 5rem;
}

.searchUsers {
  position: relative;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-direction: column;
  width: 100%;
}

@media (max-width: 768px) {
  .burgerButton {
    display: block;
  }

  .searchUsers{
    margin-top: 4rem;
  }
}

.searchBarContainer {
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

.users {
  top: 100%;
  position: absolute;
  width: 100%;
  display: flex;
  justify-content: flex-start;
  align-items: flex-start;
  flex-direction: column;
}

.user {
  width: 80%;
  display: flex;
  justify-content: flex-start;
  gap: 1rem;
  align-items: center;
  padding: 1rem;
  background-color: rgb(38, 38, 38);
  border-bottom: 1px solid rgb(33, 33, 33);
}

.user:hover {
  background-color: rgb(49, 49, 49);
  cursor: pointer;
}

.navElem {
  margin: 2rem 0;
  display: flex;
  align-items: center;
  justify-content: flex-start;
  gap: 1rem;
  cursor: pointer;
}

.hidden {
  opacity: 0;
  transition: all 0.2s;
}

.visible {
  opacity: 1;
  transition: all 1s;
}

.navElem h4 {
  position: absolute;
  left: 6rem;
}

.navElem .pi {
  font-size: 1.5rem;
}

nav {
  display: flex;
  flex-direction: column;
  width: 100%;
}

.disconnectContainer {
  display: flex;
  align-items: center;
  justify-content: flex-start;
  gap: 1rem;
  width: 100%;
  cursor: pointer;
}

.disconnectContainer h6 {
  position: absolute;
  left: 3rem;
}
</style>
