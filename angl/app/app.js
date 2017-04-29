'use strict';

// Declare app level module which depends on views, and components
angular.module('myApp', [
  'ngRoute',
  'myApp.view1',
  'myApp.view2',
  'myApp.coffees-list',
  'myApp.coffees-detail',
  'myApp.version'
]).
config(['$locationProvider', '$routeProvider', function($locationProvider, $routeProvider) {
  $locationProvider.hashPrefix('!');
  $routeProvider.when('/coffees-list/:coffeeId', {
      template: '<coffees-detail></coffees-detail>'
    });


  //otherwise({redirectTo: '/coffees-list'});

}]);
