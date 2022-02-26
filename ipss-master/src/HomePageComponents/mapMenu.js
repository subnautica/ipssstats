import React from "react";
import {IonHeader,  IonContent, IonItem, IonMenuButton, IonSplitPane, IonCol, IonList, IonItemDivider, IonLabel } from '@ionic/react'
import './mapMenu.css'

import Collapsible from 'react-collapsible'


const northamericaList = ['USA', 'Canada', 'Greenland']
const latinamericanList = ['Mexico', 'Argentina', 'Brazil']

/* Props:
   none
*/
class MapMenu extends React.Component {

    

    render(){

        return(
            <IonCol size='3'>
                <IonHeader className='menu-header' color='primary'>
                    Country Selector
                </IonHeader>

                <Collapsible contentInnerClassName='subregion' openedClassName='region-header' className='region-header' trigger='North America'>
                        <IonList>
                            {northamericaList.map((item) => (
                                <p> {item} </p>
                            ))}
                        </IonList>
                </Collapsible>

                <Collapsible openedClassName='region-header' className='region-header' trigger='Latin America and the Carribean'>
                        <p> country 1 </p>
                        <Collapsible trigger='country 3'>
                        <p> Country 2 </p>
                        </Collapsible>
                </Collapsible>

                <Collapsible openedClassName='region-header' className='region-header' trigger='Europe'>
                        <p> country 1 </p>
                        <Collapsible trigger='country 3'>
                        <p> Country 2 </p>
                        </Collapsible>
                </Collapsible>

                <Collapsible openedClassName='region-header' className='region-header' trigger='Africa'>
                        <p> country 1 </p>
                        <Collapsible trigger='country 3'>
                        <p> Country 2 </p>
                        </Collapsible>
                </Collapsible>

                <Collapsible openedClassName='region-header' className='region-header' trigger='Eastern Asia'>
                        <p> country 1 </p>
                        <Collapsible trigger='country 3'>
                        <p> Country 2 </p>
                        </Collapsible>
                </Collapsible>

                <Collapsible openedClassName='region-header' className='region-header' trigger='Central Asia'>
                        <p> country 1 </p>
                        <Collapsible trigger='country 3'>
                        <p> Country 2 </p>
                        </Collapsible>
                </Collapsible>

                <Collapsible openedClassName='region-header' className='region-header' trigger='Western Asia'>
                        <p> country 1 </p>
                        <Collapsible trigger='country 3'>
                        <p> Country 2 </p>
                        </Collapsible>
                </Collapsible>

                <Collapsible openedClassName='region-header' className='region-header' trigger='South-Western Asia'>
                        <p> country 1 </p>
                        <Collapsible trigger='country 3'>
                        <p> Country 2 </p>
                        </Collapsible>
                </Collapsible>

                <Collapsible openedClassName='region-header' className='region-header' trigger='Southern Asia'>
                        <p> country 1 </p>
                        <Collapsible trigger='country 3'>
                        <p> Country 2 </p>
                        </Collapsible>
                </Collapsible>

                <Collapsible openedClassName='region-header' className='region-header' trigger='Oceania'>
                        <p> country 1 </p>
                        <Collapsible trigger='country 3'>
                        <p> Country 2 </p>
                        </Collapsible>
                </Collapsible>

            </IonCol>
        )
    }
}

export default MapMenu