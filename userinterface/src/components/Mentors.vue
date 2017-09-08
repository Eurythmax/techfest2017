<template>
  <div class="mentors">
  <el-table
    :data="this.$store.state.mentors.tableData3"
    style="width: 100%">
    <el-table-column type="expand">
      <template scope="props">
        <p>Name: {{ props.row.firstname }} {{ props.row.lastname }}</p>
        <p>City: {{ props.row.city }}</p>
      
      </template>
    </el-table-column>
    <el-table-column
      label="First Name"
      prop="firstname">
    </el-table-column>
    <el-table-column
      label="Last Name"
      prop="lastname">
    </el-table-column>
  </el-table>
  <div>counter: {{count}}</div>
</div>
</template>

<script>

  export default {
    computed: {
      count(){
        return this.$store.state.counter
      },
      getMentors(){
        return this.$store.state.mentors
      }
    }
  }
</script>
