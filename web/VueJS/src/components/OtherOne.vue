<template>
  <div>
    <h2>Name: {{ name }}</h2>
  </div>
</template>

<script>
export default {
    name: "OtherOne",
    props : [
        'name'
    ]
}
</script>

<style lang="scss" scoped></style>
