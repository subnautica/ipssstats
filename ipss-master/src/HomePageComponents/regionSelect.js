import React from 'react';
import {IonContent, IonItem, IonItemOption, IonItemSliding, IonList, IonText, IonItemOptions, } from '@ionic/react'
import './regionSelect.css'
import { setMaxListeners } from 'process';
import { Link } from 'react-router-dom'
import { key } from 'ionicons/icons';


/* Props:
    key: country name, keeps list in order
    selectedCountry: name of country
    removeRegion: handler funciton to remove region for projection queue
*/
class RegionItem extends React.Component {
    constructor(props){
        super(props);
        this.state = {
            countryName: this.props.selectedCountry,
            key: this.props.selectedCountry
        }
    }

    render(){
        return (
            <IonItemSliding> 
                <IonItemOptions side="start">
                    <IonItemOption color="danger" onClick={() => this.props.removeRegion(this.state.countryName)}> Delete </IonItemOption>
                </IonItemOptions>
                <Link to= 'Page2'>
               
                <IonItem detail={true}>
                    <img className="item-image" alt="United States" src="http://purecatamphetamine.github.io/country-flag-icons/3x2/US.svg"/>
                    <IonText className='country-name'>
                        {this.state.countryName} 
                    </IonText>
                    
                </IonItem>
                </Link>
            </IonItemSliding>
        )
    }
}

/* Props:
    selectedCountry: country currently selected
    projCOuntryList: list of countries in projection queue
    removeRegion: handler for removing region
*/
class RegionSelect extends React.Component {
    constructor(props){
        super(props);
        this.removeRegion = this.removeRegion.bind(this)
    }

    removeRegion(region){
        this.props.removeRegion(region)
    }

    render(){
        return(
            <div className="region-select">
                <IonContent scrollEvents={true} scrollY={true}>
                    <IonList>
                        {this.props.projCountryList.map((item) => (
                            <RegionItem key={item} selectedCountry={item} removeRegion={this.removeRegion}></RegionItem>
                        ))}
                    </IonList>
                </IonContent>
            </div>
        )
    }

}

export default RegionSelect