
import mapboxgl from 'mapbox-gl';
import 'mapbox-gl/dist/mapbox-gl.css';
import React from 'react';
import MapMenu from './mapMenu';

import './map.css'
import { map } from 'ionicons/icons';

<div>
<meta charSet="utf-8"/>
<meta name="viewport" content="initial-scale=1,maximum-scale=1,user-scalable=no" />
<script src="https://api.mapbox.com/mapbox-gl-js/v2.2.0/mapbox-gl.js"></script>
</div>

mapboxgl.accessToken = 'pk.eyJ1IjoiY2Z5ZmUiLCJhIjoiY2tva2R3MDJ6MDMxczJ2a3licnF1YnhlbSJ9.njj8QRU3p_d4qW13Puhc5A';

// TODO: 
// Make country fill stay on country once clicked until either something else is clicked or zoom level is changed
// Need to add a number of beacons/buttons/icons on map to represent regions and sub regions. Maybe something in the info box to diplay region of county
// Need to make map rerender properly when it is resized, whether through movement or the side button


/* Props:
  selectedCountry: currently selected country (Mostly passed up)
  onCountryChange: handles country change
  buttonClick: think its supposed to handle the side menu opening, but don't think it works rn
*/
class WorldMap extends React.PureComponent {
  
  constructor(props) {
    super(props);
    this.state = {
    lng: -9.59,
    lat: 42.13,
    zoom: 1.75,
    clickedCountry: 'World',
    menuEvent: this.props.buttonEvent
    };
    this.mapContainer = React.createRef();
    this.handleCountryChange = this.handleCountryChange.bind(this);
    }

    //updates state in homepage
  handleCountryChange(){
    this.props.onCountryChange(this.state.clickedCountry)
  }
  
  renderMap(){
   //creates map and links it to container
   const { lng, lat, zoom } = this.state;
   const map = new mapboxgl.Map({
   container: this.mapContainer.current,
   style: 'mapbox://styles/cfyfe/ckokdx6er0v7n19mkirg70crx',
   //center: [lng, lat],
   //zoom: zoom,
   bounds: [[-175, -58.5], [197, 85]]
   });

   //colors for region tiling
   const regionColors = ['#bfd5b0', '#dddaab', '#96c2dc',  '#e6b4b2', '#f8d4a8', '#f3cbaf',  '#d6b1ae',  '#a36e50',  '#f3cda8',  '#8ecce9', '#664b80'];
   
   map.on('load', () => {
     

     map.resize();

     //Adds Country Vecotr tile source, Vector source is country-boundaries-v1, but the actual layer of country boundaries is called country_boundaries
     map.addSource('countryVector', {
       type: "vector",
       url: 'mapbox://mapbox.country-boundaries-v1'
     });


    /* Layer test */ 
   /* 
   map.addLayer({
       id: 'hello',
       type: 'fill',
       source: 'countryVector',
       'source-layer' : 'country_boundaries',
       filter: ['==', ['get', 'region'], 'Africa'],
       paint: {
         "fill-color" :  '#f8d4a8'
       
     })   
     */

     
     // Vector tile layer for countries
     map.addLayer({
       id: 'country-fills',
       type: 'fill',
       source: 'countryVector',
       'source-layer': 'country_boundaries',
       paint: {
         'fill-color': [
           'case',
             ["==", ["get", 'region'], "Africa"], regionColors[0],
             ["==", ["get", 'subregion'], "Latin America and the Caribbean"], regionColors[1],
             ["==", ["get", 'subregion'], "Northern America"], regionColors[2],
             ["==", ["get", 'region'], "Europe"], regionColors[3],
             ["==", ["get", 'subregion'], "Central Asia"], regionColors[4],
             ["==", ["get", 'subregion'], "Eastern Asia"], regionColors[5],
             ["==", ["get", 'subregion'], "Southern Asia"], regionColors[6],
             ["==", ["get", 'subregion'], "South-eastern Asia"], regionColors[7],
             ["==", ["get", 'subregion'], "Western Asia"], regionColors[8],
             ["==", ["get", 'region'], "Oceania"], regionColors[9],
             regionColors[10]
           
         ],
         //expression for setting country vector tile to opaque on hover
         'fill-opacity': [
           'case',
           ['boolean', ['feature-state', 'hover'], false],
           1,
           0.5
           ] 
       }
     })

     //Filters out the double fills of countries from multiple worldviews
     const filters = [
       'all',
       ['match', ['get', 'worldview'], ['all', 'US'], true, false],
     ]
     map.setFilter('country-fills', filters)

   })
   
   
   var hoveredCountryId;

   //Sets country vector tile feature state, hover, to false on mouseover
   map.on('mousemove', 'country-fills', (e) =>{
     if (e.features.length > 0){
       if(hoveredCountryId !== null){
         map.setFeatureState(
           {source: 'countryVector', sourceLayer: 'country_boundaries', id: hoveredCountryId},
           {hover: false}
         );
       }
       hoveredCountryId = e.features[0].id;
       map.setFeatureState(
         {source: 'countryVector', sourceLayer: 'country_boundaries', id: hoveredCountryId},
         {hover: true}
       );
     }
   }
   )
   //Sets country vector tile feature state, hover, to true when mouse leaves tile
   map.on('mouseleave', 'country-fills', () => {
     if (hoveredCountryId !== null){
       map.setFeatureState(
         {source: 'countryVector', sourceLayer: 'country_boundaries', id: hoveredCountryId},
         {hover: false}
       );
     }
     hoveredCountryId = null;
   } )

   //array of region centers and zooms. Indexes are aligned with colors array
   const regionCenterLng = [20.3619, -66.0798, -96.2236, 13.2079, 67.4389, 110.1944, 70.5705, 117.0242, 43.2843, 153.3587];
   const regionCenterLat = [1.5408, -18.3571, 66.8906, 55, 46.8645, 39.5402, 25.7980, 8.3769, 29.5455, -22.4658];
   
   
  
   //Function that recenters map to center the region on click
   map.on('click', 'country-fills', (e) => {
     
     var clickedRegion = e.features[0].properties.region;
     var clickedSubRegion = e.features[0].properties.subregion;

     switch(clickedRegion){
       case 'Africa': 
         // map.flyTo({center: [regionCenterLng[0], regionCenterLat[0]], zoom: regionZoom[0]});
         map.fitBounds([
           [-28, -36.4], [53.26, 38.8]
         ])
         break;
       case 'Europe':
         //map.flyTo({center: [regionCenterLng[3], regionCenterLat[3]], zoom: regionZoom[3]});
         map.fitBounds([
           [-27.8, 32.8], [52, 72.3]
         ])
         break;
       case 'Oceania':
         //map.flyTo({center: [regionCenterLng[9], regionCenterLat[9]], zoom: regionZoom[9]});
         map.fitBounds([
           [109.14, -49.5], [232.7, 20.9]
         ])
         break;
     }

     switch(clickedSubRegion){
       case 'Latin America and the Caribbean':
         //map.flyTo({center: [regionCenterLng[1], regionCenterLat[1]], zoom: regionZoom[1]});
         map.fitBounds([
           [-120.29, -58], [-24.5, 35]
         ])
         break;
       case 'Northern America':
         /* map.flyTo({center: [regionCenterLng[2], regionCenterLat[2]], zoom: regionZoom[2]}); */ 
          map.fitBounds([
            [-172.9, 23.54], [-10.43, 83.8]
          ])
         break;
       case 'Central Asia':
         //map.flyTo({center: [regionCenterLng[4], regionCenterLat[4]], zoom: regionZoom[4]}); 
         map.fitBounds([
           [44.8, 34.2], [90.2, 56.2]
         ])
         break;
       case 'Eastern Asia':
         //map.flyTo({center: [regionCenterLng[5], regionCenterLat[5]], zoom: regionZoom[5]});
         map.fitBounds([
            [71.75, 16.47], [149.19, 54.6]
          ])
         break;
       case 'Southern Asia':
         //map.flyTo({center: [regionCenterLng[6], regionCenterLat[6]], zoom: regionZoom[6]});
         map.fitBounds([
           [42.15, 1.677], [99.29, 41]
         ])
         break;
       case 'South-eastern Asia':
         //map.flyTo({center: [regionCenterLng[7], regionCenterLat[7]], zoom: regionZoom[7]});
         map.fitBounds([
           [89.8, -12.26], [143.8, 31.2]
         ])
         break;
       case 'Western Asia':
         //map.flyTo({center: [regionCenterLng[8], regionCenterLat[8]], zoom: regionZoom[8]});
         map.fitBounds([
           [24.27, 10.5], [62.53, 45.2]
         ])
         break;
     }


   })

   

   //gets clicked country and calls func to update WorldMap 
   map.on('click', 'country-fills', (e) =>{
     var clickCountry = e.features[0].properties.name_en;

     this.state.clickedCountry = clickCountry;
     this.handleCountryChange();


   })
   
  //Gets lat and lng for sidebar
   /* map.on('move', () => {
     this.setState({
     lng: map.getCenter().lng.toFixed(4),
     lat: map.getCenter().lat.toFixed(4),
     zoom: map.getZoom().toFixed(2)
     })
     }); */

    /*  map.on('click', (e) => {
       this.setState({
         lng: e.lngLat.lng,
         lat: e.lngLat.lat,
       })
     }) */

  }


  componentDidMount() {
   this.renderMap()
  }

  shouldComponentUpdate(nextProps, nextState){
    if(this.state == nextState && this.props == nextProps){
      return false
    }
  }

  componentDidUpdate(){
    document.getElementById('map').innerHTML = ''
    this.renderMap()
  } 

  

  render() {
    return (
      <div>
        <div className="sidebar">
              Longitude: {this.state.lng} | Latitude: {this.state.lat} | Zoom: {this.state.zoom}
        </div>
        
        <div id ='map' ref={this.mapContainer} className="map-container" />
      </div>
    );
  }
}

export default WorldMap



