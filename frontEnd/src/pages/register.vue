<script setup>
import Chesspp from '../components/Chesspp.vue';
import LoginForm from '../components/LoginForm.vue';
import RegisterForm from '../components/registerForm.vue';

</script>

<template>

<div class="formPage">
    <Chesspp />
    <RegisterForm></RegisterForm>
    <router-link to="/login" class="link">
    i already have account
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
        color: white;

    }

    .link:visited{
        color: white;
    }
</style>
