import React, { Component } from 'react';
import { TouchableHighlight, Image, AppRegistry, Text, TextInput, View, Button, StyleSheet, Alert } from 'react-native';


export default class Set extends Component {
  constructor(props) {
    super(props);

    //creating button id
    this.id = 'id' + (new Date()).getTime() + (17 * Math.random()) ;

    this.state = {
      color: 'white',
    };

    this._onPressButton = this._onPressButton.bind(this);
    this.numReps = this.props.numReps;

   // console.log(this.numReps);
  }


  _onPressButton() {
      
      if(this.state.color === 'white'){

        // changing button color
        this.setState({
          color: 'black'
        });

      } else {

        // changing button color
        this.setState({
          color: 'white'
        });

      }

    }


  render() {

    // updatehandler triggers exercise to trigger it's stopwatch to start
    var updatehandler = this.props.handler;

    var button_color = this.state.color;

    if (this.numReps){

          var numReps = this.numReps.toString();

    } else {

      var numReps = "5";

    }

    return (

      <View style={styles.square}>

        <Button 
          onPress={ () => {
            updatehandler()
            this._onPressButton()
          }}
          title={numReps}
          color= {button_color}
        />

      </View>
    );
  }
}

let iconSize = 50;
const styles =  StyleSheet.create({
 
 circle: {
    width: iconSize,
    height: iconSize,
    borderRadius: iconSize/2,
    backgroundColor: 'red'
},
container: {
    flex: 1,
  },
imageContainer: {
  height:50,
  width: 50,
  borderRadius: 25
},
image: {
  height:50,
  width: 50,
  borderRadius: 25
},
square: {
  width: 45,
  height: 45,
}
});

const textStyles = StyleSheet.create({
  setText: {
    color: 'white',

    // 'Helvetica Neue UltraLight',
      //         'Helvetica Neueu', Helvetica, Arial, sans-serif;
  },
  titleText: {
    fontSize: 20,
    fontWeight: 'bold',
  },
});

 // <View style={styles.container}>
 //           <TouchableHighlight style={ styles.imageContainer }>
 //                <Image style={ styles.image } source={{ uri: 'http://www.free-avatars.com/data/media/37/cat_avatar_0597.jpg' }} />
 //           </TouchableHighlight> 

 //        </View> 


// skip this line if using Create React Native App
// AppRegistry.registerComponent('PizzaTranslator', () => PizzaTranslator);