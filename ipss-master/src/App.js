import { Redirect, Route } from 'react-router-dom';
import { IonApp, IonRouterOutlet } from '@ionic/react';
import { IonReactRouter } from '@ionic/react-router';
import React from 'react';
import HomePage from './pages/HomePage';
import Page2 from './pages/Page2';
import TestPage from './pages/TestPage';
import CountryData from './GlobalComponents/CountryDataClass';

/* Core CSS required for Ionic components to work properly */
import '@ionic/react/css/core.css';

/* Basic CSS for apps built with Ionic */
import '@ionic/react/css/normalize.css';
import '@ionic/react/css/structure.css';
import '@ionic/react/css/typography.css';

/* Optional CSS utils that can be commented out */
//import '@ionic/react/css/padding.css';
/* import '@ionic/react/css/float-elements.css';
import '@ionic/react/css/text-alignment.css';
import '@ionic/react/css/text-transformation.css';
import '@ionic/react/css/flex-utils.css';
import '@ionic/react/css/display.css'; */

/* Theme variables */
import './theme/variables.css';

class App extends React.Component {
  constructor(props){
    super(props);
    this.state = {
      projCountryList: []
    }
    this.handleListUpdate = this.handleListUpdate.bind(this)
  }

  createNewCountryData(countryName){
    const newData = []//import json or whatever

  }

  removeCountryFromProjectionQueue(countryName){
    
  }

  handleListUpdate(list){
    this.setState({projCountryList: list.map(item => item)})
  }
  
  render(){
    return(<IonApp>
    <IonReactRouter>
      <IonRouterOutlet>
        <Route exact path="/HomePage">
          <HomePage globalListUpdate={this.handleListUpdate} projCountryList={this.state.projCountryList}/>
        </Route>
        <Route exact path="/">
          <Redirect to="/HomePage" />
        </Route>
        <Route exact path="/Page2">
          <Page2 projCountryList={this.state.projCountryList} globalListUpdate={this.handleListUpdate}></Page2>
        </Route>
        <Route exact path='/testPage'>
          <TestPage></TestPage>
        </Route>
      </IonRouterOutlet>
    </IonReactRouter>
  </IonApp>
  )}
}

export default App;
