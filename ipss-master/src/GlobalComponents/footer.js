import React from "react";
import {IonFooter, IonToolbar, IonButton, IonButtons, IonIcon, IonPopover} from '@ionic/react'
import { Link } from 'react-router-dom'
import { globeOutline, homeOutline, listOutline, saveOutline, shareOutline, statsChartOutline,  locationOutline} from 'ionicons/icons';

import MenuPop from "../HomePageComponents/menuPopover";

class PageFooter extends React.Component {
    constructor(props){
        super(props)
        this.state = {
            showMenuPop: false,
            menuPopEvent: undefined,
        }
    }

    createMenuPop(e, ii){
        this.setState({showMenuPop: ii, menuPopEvent: e})
    }

    dismissMenuPop(ii){
        this.setState({showMenuPop: ii})
    }



    render(){
        return(
            <IonFooter className="home-footer">
                <IonToolbar color="primary" className="footer-toolbar">
                
                <IonButtons slot="start" >
                
                    <Link to="/HomePage" className="footer-icons">
                        <IonButton>
                            <IonIcon  size= "large" slot="start" icon={homeOutline} ></IonIcon>    
                                Home 
                        </IonButton>
                    </Link>
                    <Link to="/Page2" className="footer-icons">
                        <IonButton >
                            <IonIcon  size= "large" slot="start" icon={locationOutline}  ></IonIcon>
                            Page 2
                        </IonButton>
                    </Link>

                </IonButtons>
                
                <IonButtons slot="end">
                    <IonButton>
                        <IonIcon  size= "large"  icon={globeOutline} ></IonIcon>  
                    </IonButton>

                    <IonButton>
                        <IonIcon  size= "large"  icon={statsChartOutline} ></IonIcon>
                    </IonButton>

                    <IonButton>
                        <IonIcon  size= "large"  icon={saveOutline} ></IonIcon>
                    </IonButton>

                    <IonButton>
                        <IonIcon  size= "large" icon={shareOutline} ></IonIcon>
                    </IonButton>
                    
                    <IonPopover 
                            
                            className="menu-popover"  
                            isOpen={this.state.showMenuPop} 
                            onDidDismiss={() => this.dismissMenuPop(false)}
                            showBackdrop={false}
                            event = {this.state.menuPopEvent}
                        >
                            <MenuPop></MenuPop>

                        </IonPopover>
                    <IonButton onClick={(e) => this.createMenuPop(e, true)}>
                        <IonIcon  size= "large" icon={listOutline} ></IonIcon>
                    </IonButton>
                    
                </IonButtons>
                </IonToolbar>
            </IonFooter>
        )
    }
}

export default PageFooter