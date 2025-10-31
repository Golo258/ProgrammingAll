<template>
  <div>
    <pre>
      {{ JSON.stringify(formValues, null, 2) }}
    </pre>
  </div>
  <form @submit.prevent="postSelectedData">
    <div>
      <label for="name"> Name</label>
      <input type="text" id="name" v-model.trim.lazy="formValues.name" />
    </div>

    <div>
      <label for="profile">Profile Summary</label>
      <textarea id="profile" v-model="formValues.profileSummary"></textarea>
    </div>

    <div>
      <label for="country">Country</label>
      <select id="country" v-model="formValues.countries">
        <option value="">Select a country</option>
        <option value="india">India</option>
        <option value="vietnam">Vietnam</option>
        <option value="poland">Poland</option>
      </select>
    </div>

    <div>
      <label for="job-Location">job Location</label>
      <select id="job-Location" multiple v-model="formValues.jobLocation">
        <option value="">Select a job location</option>
        <option value="india">India</option>
        <option value="vietnam">Vietnam</option>
        <option value="poland">Poland</option>
      </select>
    </div>
    <div>
      <input type="checkbox" id="remote" v-model="formValues.remoteWork" />
      <label for="remote">Remote Work</label>
    </div>
    <div v-if="formValues.remoteWork">
      <h2>The remote Work is fine</h2>
    </div>

    <div>
      <label> Skills</label>
      <input
        type="checkbox"
        id="html"
        value="html"
        v-model="formValues.skills"
      />
      <label for="html">Html</label>
      <input
        type="checkbox"
        id="python"
        value="python"
        v-model="formValues.skills"
      />
      <label for="python">Python</label>
      <input
        type="checkbox"
        id="java"
        value="java"
        v-model="formValues.skills"
      />
      <label for="java">Java</label>
    </div>

    <div>
      <label>Years of Experience</label>
      <input
        type="radio"
        id="02"
        value="0-2"
        v-model="formValues.exprienceYears"
      />
      <label for="02">0 - 2</label>

      <input
        type="radio"
        id="24"
        value="2-4"
        v-model="formValues.exprienceYears"
      />
      <label for="24">2 - 4</label>

      <input
        type="radio"
        id="46"
        value="4-6"
        v-model="formValues.exprienceYears"
      />
      <label for="46">4 - 6 </label>
    </div>
    <div>
        <input type="number" id="age" v-model.number="formValues.age">
        <label for="age" style="margin-left:30px" >Age</label>
    </div>

    <div>
        <input @keyup.q="postSelectedData" type="number" id="age"  v-model.number="formValues.age">
        <label for="age" style="margin-left:30px">Something Else</label>
    </div>
    <!-- <div>
      <button type="submit">Submit</button>
    </div> -->
    <!-- many checkboxes -->
  </form>
</template>

<script>
export default {
  name: "App",
  data() {
    return {
      formValues: {
        name: "",
        profileSummary: "",
        countries: "",
        jobLocation: [],
        remoteWork: false,
        skills: [],
        exprienceYears: [],
        age: null,
      },
    };
  },
  methods: {
    postSelectedData(event) {
        // event.preventDefault()
    console.log(event)
      console.log("Form Values: ", this.formValues);
    },
  },
};
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
label {
  font-weight: bold;
  display: flex;
  margin-bottom: 5px;
}
input + label {
  font-weight: bold;
  display: inline-flex;
  margin-right: 20px;
}

input[type="text"],
textarea,
select {
  display: block;
  width: 400px;
  padding: 6px 12px;
  font-size: 14px;
  line-height: 1.428;
  color: #555;
  background-color: #fff;
  background-image: none;
  border: 1px solid #ccc;
  border-radius: 4px;
}
</style>
