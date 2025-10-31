<template>
  <div>
    <button @click="generateSumOfRandoms(5)">Generated 5 numbers</button>
    <div v-for="number in generatedNumbers" :key="number">
      {{ number }}
    </div>
    <h2>Sum: {{ sum }}</h2>
  </div>

  <hr />
  <div>
    <input type="number" v-model="inputNumber" />
    <button @click="generateAndSum">Generate and Sum</button>
    <p v-if="generatedNumbers.length > 0">{{ sum }}</p>
  </div>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      generatedNumbers: [],
      sum: 0,
      inputNumber: 1,
    };
  },
  methods: {
    generateSumOfRandoms(countOfNumbers) {
      // let sumOfRandom = 0;
      this.generatedNumbers = [];
      this.sum = 0;
      for (let i = 0; i < countOfNumbers; i++) {
        const randomNr = Math.floor(Math.random() * 100) + 1;
        this.generatedNumbers.push(randomNr);
        this.sum += randomNr;
      }
    },
    generateAndSum() {
      const count = parseInt(this.inputNumber);
      if (isNaN(count) || count <= 0) {
        alert("Please enter a valid number greater than 0");
        return;
      }
      this.generatedNumbers = [];
      this.sum = 0;
      for (let i = 0; i < this.inputNumber; i++) {
        const randomNr = Math.floor(Math.random() * 100) + 1;
        this.generatedNumbers.push(randomNr);
        this.sum += randomNr;
      }
    },
  },
};
</script>
