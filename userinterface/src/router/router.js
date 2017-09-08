import Vue from 'vue';
import Router from 'vue-router';
import LiveAdminTable from '../components/LiveAdminTable.vue';


Vue.use(Router);

export default new Router({
  mode: 'history',
  routes: [
    {
      path: '/admin',
      name: 'LiveAdminTable',
      component: LiveAdminTable,
    }
  ],
});
