import React, { Component } from 'react';
import { AppRegistry, Text, TextInput, View, Button, StyleSheet, Alert } from 'react-native';
import { Container, Content, Card, CardItem, Body } from 'native-base';

import Set from './Set.js';
import Stopwatch from './Stopwatch.js';

export default class Exercise extends Component {
   constructor(props) {
    super(props);

    /* props:
    <Exercise name='bicep curl' numSets={3} numReps={10} />
    */
  
    this.numSets = this.props.numSets;
    this.name = this.props.name;
    this.numReps = this.props.numReps;
    this.weight = this.props.weight;

    var tempList = [];
    for (var i = 1; i <= this.numSets; i++) {
      tempList.push(i);
    }
 
    this.state = {
      setList: tempList,
      reset: false,
    };

    this.addSet = this.addSet.bind(this);
    this.deleteSet = this.deleteSet.bind(this);
    this.setHandler = this.setHandler.bind(this);
    this.stopwatchHandler =this.stopwatchHandler.bind(this);

  }

  //changes class variables as it is typed
  addSet(event) {
    this.numSets += 1;

    var newList = [];
    newList = this.state.setList;
    newList.push(this.numSets);

    this.setState({
      setList: newList,
    });

  }

  deleteSet(event) {
    if (this.numSets > 0) {
      this.numSets -= 1;

      var newList = [];
      newList = this.state.setList;
      // remove last item from setList
      newList.pop();
      // changing state
      this.setState({
        setList: newList,
      });

    } else {
      alert("There are no sets left to remove for " + this.name);
    }

  }

 
  setHandler() {

    console.log("start timer");
    this.setState({
        reset: true,
      });

    // if the last set has finished, turn it into a "good job message" and 
    // display the total time spent doing that set
    
  }

  stopwatchHandler() {
    console.log("reset timer");
    this.setState({
        reset: false,
      });

  }

  render(){

    var Sets = this.state.setList.map((number, i) =>
      <Set numReps={this.numReps} handler={this.setHandler} key={i} />
    );

    return(

        <View >
        
          <Card>
          <CardItem header>
              <Text>{this.name}, {this.weight} lbs </Text>
            </CardItem>
          <View style={{flexDirection: 'row', backgroundColor:"black" }}>
              {Sets}
          </View>
          <View style={{flexDirection: 'row'}}>
            <View 
              style={{ 
                width: 50, height:50, backgroundColor:'powderblue' 
              }}>
            
              <Button 
                onPress={this.addSet}
                color="black"
                title="+"
              />
            </View>

            <View 
              style={{ 
                width: 50, height:50, backgroundColor:'powderblue' 
              }}>
              <Button 
                onPress={this.deleteSet}
                color="black"
                title="-"
              />
            </View>
            <View style={{ 
                width: 125, height:50, backgroundColor: '#1990b8'
              }}>
              <Stopwatch reset={this.state.reset} handler={this.stopwatchHandler} />
            </View>
          </View>
          </Card>

        </View>
    );
  }
}