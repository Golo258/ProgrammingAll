<template>
  <div>
    <h2>{{ fullName }}</h2>
    <input type="text" v-model="firstName" />
  </div>
  <div>
    <h2>Total: {{ total }}</h2>
    <h2>reduceExamples: {{ reduceExamples }}</h2>
    <h2>mapExamples: {{ mapExamples }}</h2>
    <h2>mapExamples: {{ countLetterOccuranceFromUrl }}</h2>
  </div>
  <div>
    <h2 v-for="item in filteredItems" :key="item.id">
        {{ item.price }} {{ item.title}}
    </h2>
  </div>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      firstName: "Bruce",
      lastName: "Wayne",
      items: [
        {
          id: 1,
          title: "Laptop",
          price: 300,
        },
        {
          id: 2,
          title: "PC",
          price: 451,
        },
        {
          id: 3,
          title: "Macbook",
          price: 800,
        },
      ],
    };
  },
  methods: {},
  computed: {
    fullName() {
      return `${this.firstName} ${this.lastName}`;
    },
    total() {
      return this.items.reduce((total, current) => (total += current.price), 0);
    },
    reduceExamples() {
      // COunting sum under condition
      const table = [6, 3, 12, 5, 81];
      const charTable = ["a", "b", "c", "d"];
      const countedSum = table.reduce((acc, current, currentIndex, array) => {
        console.log(
          `acc: ${acc}, current: ${current}, currentIndex: ${currentIndex}, array: ${array}`
        );
        if (current % 2 == 0) {
          acc += current;
        } else {
          acc += current * 2;
        }
        return acc;
      }, 0);
      console.log(countedSum);

      const initalValue = {};
      const arrayToObject = charTable.reduce((acc, key) => {
        acc[key] = key.toUpperCase();
        return acc;
      }, initalValue);
      console.log(arrayToObject);

      return null;
    },
    mapExamples() {
      // changing each element
      const numbers = [12, 5, 7, 34, 82];
      const double = numbers.map((numb) => numb * 2);

      // formatting objects,
      const users = [
        { name: "John", age: 30 },
        { name: "Alice", age: 25 },
        { name: "Bob", age: 35 },
      ];
      const formatedUsers = users.map(
        (user) => ` ${user.name} ${user.age} years old`
      );
      console.log(formatedUsers);
      return double;
    },
    otherMethods() {
      const numbers = [1, 2, 4, 5];
      // Foreach
      numbers.forEach((num) => console.log(num));

      // Find
      const firstEven = numbers.find((num) => num % 2 === 0);
      return firstEven;
    },
    filteredItems() {
      return this.items.filter((item) => item.price > 100);
    },
  },
};
</script>
