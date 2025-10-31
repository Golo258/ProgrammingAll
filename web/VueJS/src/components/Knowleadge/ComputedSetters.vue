<template>
  <div>
    <h2>{{ fullName }}</h2>
    <button @click="changeFullName">Change Name</button>
  </div>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      firstName: "Bruce",
      lastName: "Wayne",
    };
  },
  methods: {
    changeFullName() {
      this.fullName = "Macius Pierwszy";
    },
  },
  computed: {
    fullName: {
      get() {
        return `${this.firstName} ${this.lastName}`;
      },
      set(value) {
        const names = value.split(" ");
        if (names.length >= 2) {
          this.firstName = names[0];
          this.lastName = names[1];
        } else {
          console.log("Names cannot be changed");
        }
      },
    },
  },
};
</script>
