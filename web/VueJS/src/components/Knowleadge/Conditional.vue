<template>
    <h2 v-if="numb === 0">The number is zero</h2>
    <h2 v-else-if="numb === 2">The number is two</h2>
    <h2 v-else>The number is different</h2>
    <div v-show="isDivDisplayed" >
        <ul>
            <li>One</li>
            <li>Two</li>
            <li>Three</li>
        </ul>
    </div>

</template>

<script>
export default {
  name: "App",
  data() {
    return {
      numb: 5,
      isDivDisplayed: false,
    };
  },
};
</script>

