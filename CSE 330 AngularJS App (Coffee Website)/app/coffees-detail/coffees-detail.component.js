'use strict';

angular.module('myApp.coffees-detail', ['ngRoute'])

  .component('coffeesDetail', {
    templateUrl: '/coffees-detail/reviews.html',
    controller: ['$routeParams',
      function PhoneDetailController($routeParams, $scope) {
        this.coffeeId = $routeParams.coffeeId;
      }
    ]
  });
