<script setup>
import Button from "primevue/button"
import { Form } from '@primevue/forms';
import { InputText } from "primevue";
import { register } from "../utils/auth/post";
import { ref } from "vue";


let email = ref('');
let username = ref('');
let password = ref('');
let passwordConfirmation = ref('');


async function handleSubmit() {
  await register(email.value, username.value, password.value, passwordConfirmation.value);
}

</script>

<template>

    <div class="container">
        <Form class="form" @submit="handleSubmit">
            <div class="infos">
                <InputText v-model="email" name="email" type="email" placeholder="email" />
                <InputText v-model="username" name="username" type="text" placeholder="username" />
            </div>
            <InputText v-model="password" name="password" type="password" placeholder="password"/>
            <InputText v-model="passwordConfirmation" name="confirmPassword" type="password" placeholder="confirm password"/>
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
        background-color: #312e2b;
        border-radius: .5rem;
    }

    .infos {
        display: flex;
        gap: 5px;
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