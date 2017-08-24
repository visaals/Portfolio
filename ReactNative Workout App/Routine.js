import React, { Component } from 'react';
import Workout from './Workout.js';

import { AsyncStorage, ScrollView, FlatList, AppRegistry, Text, TextInput, View, Button, StyleSheet, Alert, Dimensions } from 'react-native';
import { Container, Content, Card, CardItem, Body } from 'native-base';
import { Form, Item, Input, Label } from 'native-base';

//Routine
//
export default class Routine extends Component {

	constructor(props) {
		super(props);

		// state variables
	    this.state = {
	      workoutList: this.workoutList,
	    };
	    
	    // binding state change functions
	    this.addWorkout = this.addWorkout.bind(this);
	    this.deleteWorkout = this.deleteWorkout.bind(this);


	}

	addWorkout() {

	}

	deleteWorkout() {
		
	}


  render(){
    

    // var listItems = this.state.exerciseList.map((item, i) =>
          
    //       <Exercise name={item.name} numSets={item.numSets} numReps={item.numReps} weight={item.weight} key={i}  />

    //   );


    return(

	    <View style={{flex: 1}}>
	    <Workout name='Bare Necessities Workout' 
                exercises={[
                {"id": 1, "name": "bench press", "numSets": 5, "numReps": 5, "weight": 135},
                {"id": 2, "name": "bicep curl", "numSets": 3, "numReps": 10, "weight": 30}
                ]} /> 
	 	</View>

    );
  }


}