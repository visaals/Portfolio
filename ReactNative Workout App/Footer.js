import React, { Component } from 'react';
import { Container, Content, Footer, FooterTab, Button, Icon, Text } from 'native-base';

//​export default class FooterPack  extends Component {
export default class FooterPack extends Component {

	constructor(props) {
		super(props);

		this.state = {
			selectedTab: "workouts"
		};

		this.renderSelectedTab = this.renderSelectedTab.bind(this);

		let updateViewHandler = this.props.handler;

	}

	renderSelectedTab(statevar) {

		
		switch (statevar) {

	      case 'home':
	        console.log("home");
	        break;
	      case 'workouts':
	       	console.log("workouts");
	        break;
	      case 'settings':
	       	console.log("settings");
	        break;
	      default:
	      	console.log("default");
  		}


	}



  render() {
    return (
      <Container style={{flex: 0.5}}>
        <Content />
        <Footer>

	          <FooterTab>
	            <Button active={this.state.selectedTab === "home"}
	            		onPress={() => this.setState({ selectedTab: "home" }, this.props.handler("home"))} >
	              <Icon name="home"/>
	              <Text>Home</Text>
	            </Button>
	            
	            <Button active={this.state.selectedTab === "workouts"}
	            		onPress={() => this.setState({ selectedTab: "workouts" }, this.props.handler("workouts")) }>
	              <Icon name="settings" />
	              <Text>Workouts</Text>
	            </Button> 

	            <Button active={this.state.selectedTab === "settings"}
	            		onPress={() => this.setState({ selectedTab: "settings" }, this.props.handler("settings")) }>
	              <Icon name="settings" />
	              <Text>Settings</Text>
	            </Button> 


	          </FooterTab>
        </Footer>
      </Container>
    );
  }
}