<script setup>
import Chesspp from '../components/Chesspp.vue';
import LoginForm from '../components/LoginForm.vue';

</script>

<template>

<div class="formPage">
    <Chesspp />
    <LoginForm></LoginForm>
    <router-link to="/register" class="link">
    i don't have an account yet
    </router-link>
</div>
</template>

<style scoped>
    .formPage{
        display: flex;
        align-items: center;
        justify-content: center;
        height: 100vh;
        flex-direction: column
    }

    .link{
        margin-top: 1.5rem;
        text-decoration: underline;
        cursor: pointer;
    }
    .link:visited{
        color: white;
    }
</style>
