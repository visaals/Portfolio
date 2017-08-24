import React, { Component } from 'react';
import Exercise from './Exercise.js';
import FooterPack from './Footer.js';

import { AsyncStorage, ScrollView, FlatList, AppRegistry, Text, TextInput, View, Button, StyleSheet, Alert, Dimensions } from 'react-native';
import { Container, Content, Card, CardItem, Body } from 'native-base';
import { Form, Item, Input, Label } from 'native-base';


export default class Workout extends Component{
  /* props:
    <Exercise name='bicep curl' numSets={3} numreps={10} />

    <Workout name='Bare Necessities Workout' 
                exercises={[
                {"id": 1, "name": "bench press", "numSets": 5, "numReps": 5, "weight": 135},
                {"id": 2, "name": "bicep curl", "numSets": 3, "numReps": 10, "weight": 30}
                ]} /> 
  */
  constructor(props) {
    super(props);

    // creating unique id's for buttons
    this.add_button_id = 'id' + (new Date()).getTime() + (17 * Math.random());
    this.delete_button_id = 'id' + (new Date()).getTime() + (31 * Math.random());

    // instance variables
    this.name = this.props.name;
    this.key = 3 ;
    this.exerciseList = this.props.exercises;

   
    // state variables
    this.state = {
      exerciseList: this.exerciseList,
      inputName: "dope exercise",
      inputReps: 5,
      inputWeight: 0,
    };
    

    // binding state change functions
    this.addExercise = this.addExercise.bind(this);
    this.deleteExercise = this.deleteExercise.bind(this);
  }


 async componentWillMount() {

    try {


      let rawData = await AsyncStorage.getItem('data');
      if (rawData !== null){
        // We have data!!

        // parsing raw data (string -> obj)
        var listObj = JSON.parse(rawData);

        // setting 
        this.setState({
          "exerciseList": listObj,
          "inputName": "dope exercise",
        });

      } else {

         alert("Failed to load saved workout.");

      }


    } catch (error) {

      // Error retrieving data
      alert(error);

    }
    
  }

  saveData(value) {

    try {

      AsyncStorage.setItem('data', value);
      console.log("successfully saved");

    } catch (error) {

      console.log("save failed: " + error);

    }

  }

  //changes class variables as it is typed
  addExercise(event) {

    // incrememnting a unique key
    var newKey = this.key + 1;
    this.key = newKey;
    // pushing new exercise to list
    this.state.exerciseList.push({"key": newKey , "name": this.state.inputName, "numSets" : 5 ,
     "numReps": this.state.inputReps, "weight": this.state.inputWeight});

    // saving data to local device
    this.saveData(JSON.stringify(this.state.exerciseList));

    // adding new exercise object to list 
    this.setState({
      exerciseList: this.state.exerciseList,
    });

  }

  deleteExercise(event) {

    if (this.state.exerciseList.length > 0) {

      // remove last item from exerciseList
      this.state.exerciseList.pop();

      // changing state
      this.setState({
        exerciseList: this.state.exerciseList,
      });

    } else {

      alert("There are no exercises left to remove for your " + this.name + " workout");

    }

  }
  /*
  
<FlatList 
          style={{flex: 1}}
          data = {this.state.exerciseList}
          renderItem={ ({item}) => <Exercise name={item.name} numreps={item.numreps} numSets={item.numSets} /> } 
        / > 

   */
  render(){
    

    var listItems = this.state.exerciseList.map((item, i) =>
          
          <Exercise name={item.name} numSets={item.numSets} numReps={item.numReps} weight={item.weight} key={i}  />

      );


    return(


    <View style={{flex: 1}}>
    <ScrollView style={{flex: 1}}>
        {listItems}
      <Card>
        <View style={{flex: 1}}>

          <CardItem header>
              <Text>Add</Text>
              <Text> {this.state.inputName}, {this.state.inputReps} reps </Text>

          </CardItem>

          <CardItem>
            <Body>
                  <TextInput
                    style={{flex: 1, height: 30 }}
                    onChangeText={(inputName) => this.setState({inputName})}
                    placeholder="Enter exercise name"
                  />

                  <TextInput
                    style={{flex: 1, height: 30 , borderColor: 'black'}}
                    onChangeText={(inputReps) => this.setState({inputReps})}
                    placeholder="Enter number of reps"
                    keyboardType="numeric"
                  />
                  <TextInput
                    style={{flex: 1, height: 30 , borderColor: 'black'}}
                    onChangeText={(inputWeight) => this.setState({inputWeight})}
                    placeholder="Enter weight"
                    keyboardType="numeric"
                  />


            </Body>
          </CardItem>

          <CardItem footer>

              <View style={{ flexDirection: 'row', justifyContent: 'flex-start'}}>

                <View style={{ width: 50, height:50, backgroundColor:'powderblue' }}>
                  <Button 
                          onPress={this.addExercise}
                          color="black"
                          title="+"
                        />
                </View>

                <View style={{ width: 50, height:50, backgroundColor:'powderblue' }}>
                  <Button 
                          onPress={this.deleteExercise}
                          color="black"
                          title="-"
                        />
                </View>


              </View>

          </CardItem>

        </View>

      </Card>
    </ScrollView>
    </View>

    );
  }
}

        // <div className='Workout'>
        //   <div className='title'>
        //     <strong>{this.name}</strong>
        //   </div>
        //     <br />
        //     {listItems}
        //     <br />

        //   <div className='title'>
        //     <label><code>Name:</code></label>
        //     <input type="text" id={this.ex_name} defaultValue="dope exercise" required />
        //     <br />
        //     <label><code>Num Reps:</code></label>
        //     <input type="number" id={this.ex_reps} defaultValue="8"  />
        //     <br />

        //     <button id={this.add_button_id} className="Set" onClick={this.addExercise} >
        //         + 
        //     </button>
        //     <button id={this.delete_button_id} className="Set" onClick={this.deleteExercise} >
        //         -
        //     </button>

        //   </div>
        // </div>

        /*



        */
