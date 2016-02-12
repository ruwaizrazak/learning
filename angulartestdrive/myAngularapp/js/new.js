var demoapp = angular.module("myApp", []);


demoapp.controller("SimpleController",function ($scope) {
    $scope.students=[{name:"Thanusha",course:"PHP"},
    				{name:"Maneesha",course:"PHP"},
    				{name:"Thanveer",course:"PHP"},
    				{name:"Ranjisha",course:"ANDROID"},
    				{name:"Ranjith",course:"ANDROID"}
    				];
    $scope.age=24;
    $scope.viewLoad=function(){
    				$scope.students.push(
    						{
    							name:$scope.menteeNew.mName,
    							course:$scope.menteeNew.mCourse
    						}
    					)
    }
});
/*
demoapp.config(function($routes){
	$routes
	.when('/1',{
		controller="SimpleController",
		templateUrl="../stage4.html"
	}),
	.when('/2',{
		controller="SimpleController",
		templateUrl="../stage1.html"
	}),
	.otherwise({redirectTo:"/1"});
});
*/