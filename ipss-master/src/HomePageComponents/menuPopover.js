import { IonItem, IonContent, IonIcon, IonText } from "@ionic/react";
import React from "react";
import { Link } from "react-router-dom";
import { bookOutline, cloudOutline, informationCircleOutline, newspaperOutline, personCircleOutline, settingsOutline } from 'ionicons/icons'

import './menuPopover.css'

/* Props:
    none
*/
class MenuPop extends React.Component {

    render(){
        return (
                
                <IonContent className="menu-pop-list">

                    

                    <Link >
                        <IonItem className="menu-item">
                            <IonIcon icon={personCircleOutline} size='medium'></IonIcon>
                            <IonText className="menu-text">
                                Welcome!
                            </IonText>
                        </IonItem>
                    </Link>

                    <Link>
                        <IonItem>
                            <IonIcon icon={newspaperOutline} size='medium'></IonIcon>
                           <IonText className="menu-text">
                               News
                            </IonText>
                        </IonItem>
                    </Link>

                    <Link>
                        <IonItem>
                            <IonIcon icon={cloudOutline} size='medium'></IonIcon>
                            <IonText className="menu-text">
                               iCloud
                            </IonText>
                        </IonItem>
                    </Link>

                    <Link>
                        <IonItem>
                            <IonIcon icon={bookOutline} size='medium'></IonIcon>
                            <IonText className="menu-text">
                               iBook
                            </IonText>
                        </IonItem>
                    </Link>

                    <Link>
                        <IonItem>
                            <IonIcon icon={informationCircleOutline} size='medium'></IonIcon>
                            <IonText className="menu-text">
                               About
                            </IonText>
                        </IonItem>
                    </Link>

                    <Link>
                        <IonItem>
                            <IonIcon icon={settingsOutline} size='medium'></IonIcon>
                            <IonText className="menu-text">
                               Settings
                            </IonText>
                        </IonItem>
                    </Link>
                </IonContent>
           
        )
    }


}

export default MenuPop