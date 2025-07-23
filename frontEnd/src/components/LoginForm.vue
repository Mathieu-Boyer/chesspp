<script setup>
import Button from "primevue/button"
import { Form } from '@primevue/forms';
import { InputText } from "primevue";

import axios from "axios";
import { ref } from "vue";

import { login } from "../utils/auth/post.js";

let email = ref('');
let password = ref('');


async function handleSubmit() {
  await login(email.value, password.value);
}


</script>

<template>

    <div class="container">
        <Form class="form" @submit="handleSubmit">
            <InputText v-model="email" name="email" type="email" placeholder="email" />
            <InputText v-model="password" name="password" type="password" placeholder="password"/>
            <Button type="submit" label="Sign in"/>
        </Form>
    </div>

</template>

<style scoped>
    .container{
        display: flex;
        align-items: center;
        justify-content: center;
        flex-direction: column;
        padding: 3rem;
        width: fit-content;
        background-color: #312e2b;
        border-radius: .5rem;
    }

    .form{
        display: flex;
        flex-direction: column;
        gap: 0.5rem;
        min-width: 20rem;
    }

    input {
        border: #6a6a6a solid 1px;
    }
    
    button {
        margin-top: 1rem;
    }
</style>