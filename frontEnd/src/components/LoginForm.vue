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
            <Button type="submit" label="login"/>
        </Form>
    </div>

</template>

<style scoped>

.container {
    display: flex;
    align-items: center;
    justify-content: center;
    flex-direction: column;
    padding: 2rem;
    width: 100%;
    max-width: 400px;
    background-color: #312e2b;
    border-radius: 0.5rem;
    box-shadow: 0 0 10px rgba(0, 0, 0, 0.3);
}

.form {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
    width: 100%;
}

input {
    border: #6a6a6a solid 1px;
    padding: 0.5rem;
    font-size: 1rem;
    width: 100%;
    box-sizing: border-box;
}

button {
    margin-top: 1rem;
}

@media (max-width: 480px) {
    .container {
        padding: 1.5rem;
        border-radius: 0.25rem;
        max-width: 90vw;
    }

    input, button {
        font-size: 0.95rem;
    }
}
</style>