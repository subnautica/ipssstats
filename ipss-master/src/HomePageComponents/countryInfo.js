//React Compnent for displaying region/country data

import React from 'react';
import {IonGrid, IonRow, IonCol, IonIcon, IonText, IonButton} from '@ionic/react'
import {add, arrowForward} from 'ionicons/icons'
import './countryInfo.css'


// TODO:
// something to click on to display region/subregion info

/* Props
    selectedCountry: currently selected Country
    handleAddRegion: handles adding region to projection queue
    handleMenuClick: handles button click to toggle map side menu
*/
class CountryInfo extends React.Component {

    constructor(props){
        super(props);
        this.state = {
            countryName: this.props.selectedCountry,
        };
       
    }
    
    componentDidUpdate(prevProps){
        if(prevProps.selectedCountry !== this.props.selectedCountry){
            this.setState({countryName: this.props.selectedCountry})
        } 
    }

    render(){
        return (
            <div className="info-pane">
            <IonGrid >
                <IonRow>
                    <IonCol> 
                        <IonButton onClick={this.props.handleAddRegion}>
                            <IonIcon size= "large" icon={add}></IonIcon> 
                        </IonButton>
                        
                    </IonCol>
                            
                    <IonCol>
                        <div>
                            {this.state.countryName}
                        </div>
                    </IonCol>
                            
                    <IonCol>
                        <IonButton onClick={(e) => this.props.handleMenuClick(e)}>
                            <IonIcon class="ion-float-right" size= "large" icon={arrowForward}></IonIcon>
                        </IonButton>
                    </IonCol>
                            
                </IonRow>
                <IonRow>       
                    <IonText>
                        <p className="pop-info"> 
                            Population:  1<br/>
                            Median Age: 34 <br/>
                            Pop. Growth Rate <br/>
                            Birth Rate: 18.2/ 1000 <br/>
                            Death Rate: 7.45/ 1000 <br/>
                            Infant mortality rate: 30 / 1000 <br/>
                            Life Expectancy: 72.5 
                        </p>
                    </IonText>
                </IonRow>
            </IonGrid>
            </div>
        );
    }


}

export default CountryInfo