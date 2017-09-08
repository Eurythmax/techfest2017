<template>
  <div class="liveAdminTable">
  <el-table
    :data="this.$store.state.transactions"
    style="width: 100%">

    <el-table-column
      label="asset"
      prop="metadata.asset_id">
    </el-table-column>
    <el-table-column
      label="operation"
      prop="operation">
    </el-table-column>
    <el-table-column
      label="Metadata"
      prop="metadata.what">
    </el-table-column>
    <el-table-column
      label="Transaction ID"
      prop="id">
    </el-table-column>
    <el-table-column
      label="Asset ID"
      prop="id">
    </el-table-column>
    <el-table-column
      label="time"
      prop="metadata.time">
    </el-table-column>
  </el-table>
</div>
</template>

<script>

  export default {
    computed: {

    }
  }
</script>
