<template>
  <div v-for="name in namesArray" v-bind:key="name">
    {{ name }}
  </div>
  <div v-for="(name, index) in namesArray" :key="name">
    {{ index }} {{ name }}
  </div>
   <div v-for="person in personsArray" v-bind:key="person.first">
    {{ person.first }} {{person.last}}
  </div>
  

</template>

<script>
export default {
  name: "App",
  data() {
    return {
      namesArray: ["Jake", "Steven", "Mark"],
      personsArray: [
        { first: "Jake", last: "Wayne" },
        { first: "Clark", last: "Lee" },
        { first: "Mark", last: "Diana" },
      ],
    };
  },
};
</script>
