import React, { Component } from 'react';
import { AsyncStorage, ScrollView, FlatList, AppRegistry, Text, TextInput, View, StyleSheet, Alert, Dimensions } from 'react-native';
import { Container, Content, Card, CardItem, Body, Button,Icon } from 'native-base';
  

export default class Stopwatch extends Component {

  constructor(props) {
    super(props);

    this.state = { 
      secondsElapsed: 0, 
      lastClearedIncrementer: null
    };

    this.incrementer = null;

    this.start = this.handleStartClick.bind(this);
    this.stop = this.handleStopClick.bind(this);
    this.reset = this.handleResetClick.bind(this);
  }  
    
  handleStartClick() {

    console.log(this.incrementer);

    this.incrementer = setInterval( () => {
      
      var newCount = this.state.secondsElapsed + 1;

      this.setState({
        secondsElapsed: newCount
      }); }

    , 1000);

  }
  
  handleStopClick() {

    clearInterval(this.incrementer);

    this.setState({
      lastClearedIncrementer: this.incrementer
    });

  }
  
  handleResetClick() {

    clearInterval(this.incrementer);

    this.setState({
      secondsElapsed: 0,
      lastClearedIncrementer: 0
    });


  }


  render() {

    var sendReset = this.props.handler;

    const formattedSeconds = (sec) =>
        Math.floor(sec / 60) +
          ':' +
        ('0' + sec % 60).slice(-2);

    // took me two damn hours to get this to work... I'm an idiot
    // sends warning "Cannot update during an existing state transition"
    // but it works...I'll get back to it later
    if ( this.props.reset ) {
      this.reset();
      sendReset(); //changes this.props.reset to false in Exercise component so this will not be called again
      this.start();
    }
  
    // control flow of whether onPress should start or stop the timer
    if (this.state.secondsElapsed === 0 || this.incrementer === this.state.lastClearedIncrementer) {

      var timer = <Button onPress={this.start} transparent><Text style={textStyles.timerText}>{formattedSeconds(this.state.secondsElapsed)}</Text></Button>;
    
    } else {

      var timer = <Button onPress={this.stop} transparent><Text style={textStyles.timerText}>{formattedSeconds(this.state.secondsElapsed)}</Text></Button>;
    
    }

    // configure reset button to change the state of Exercise {started: false} so timer stops
    var resetButton = <Button onPress={ () => { sendReset(), this.reset() } } transparent><Text style={textStyles.timerText}>reset</Text></Button>;

    return (

      <View style={{flex: 1}}>
        <View style={{flex: 1, flexDirection: 'row' }}>
          {timer}{resetButton}
        </View>
      </View>

    );
  }
}


const textStyles = StyleSheet.create({
  timerText: {
    fontFamily: 'HelveticaNeue-Light',
    color: 'white',

    // 'Helvetica Neue UltraLight',
      //         'Helvetica Neueu', Helvetica, Arial, sans-serif;
  },
  titleText: {
    fontSize: 20,
    fontWeight: 'bold',
  },
});

