import React from 'react';
import Chart from 'chart.js/auto';
import './homeChart.css'



let myChart;

const ages = ['0-4', '5-9', '10-14', '15-19', '20-24', '25-29', '30-34', '35-39', '40-44', '45-49', '50-54', '55-59', '60-64', '65-69', '70+'];

//Gonna need a call to the database to fill these out for real
const malePopulation = [10, 20, 30, 40, 50, 60];
const femalePopulation = [70, 60, 50, 40, 30, 20, 10]

/* Props:
    selectedCountry: Name of country to chart
*/
class HomeChart extends React.Component {

    constructor(props){
        super(props);
        this.state = {
            countryName: this.props.selectedCountry
        }
        this.chartRef = React.createRef();
    }

    //Initial chart render
    componentDidMount(){
       this.buildChart();
    }
    
    //rerenders chart with updated state if state has changed
    componentDidUpdate(prevProps){
        if(prevProps.selectedCountry !== this.props.selectedCountry){
            this.setState({countryName: this.props.selectedCountry})
        }
        this.buildChart();
    }

    //function to build chart obv
    buildChart(){

        if(typeof myChart !== "undefined"){
            myChart.destroy();
        }

        const ctx = this.chartRef.current.getContext("2d");

        //set chart title
        let abc = "Population of "
        let countrytitle = this.state.countryName
        let chartTitle = abc.concat(countrytitle);

        myChart = new Chart(ctx, {
            
            type: "bar",
       
            data: {
                labels: ages,
                datasets: [
                    {
                        label: "Male",
                        stack: "Stack 0",
                        backgroundColor: "#d41111",
                        data: malePopulation.map((k) => -k),
                    },
                    {
                        label: "Female",
                        stack: "Stack 0",
                        backgroundColor: "#3765b0",
                        data: femalePopulation,
                    },
                ],
            },

            options: {
                
                indexAxis: 'y', 
                plugins: {
                    title: {
                        display: true,
                        text: chartTitle,
                    },

                    tooltip: {
                        backgroundColor: '#000000',
                        intersect: true,
                        position: 'nearest',
                        callbacks: {
                            label: (c) => {
                                const value = Number(c.raw);
                                const positiveOnly = value < 0 ? -value : value;
                                let retStr ="";
                                let male = 'Male: ';
                                let female = 'Female: ';
                                if (c.datasetIndex == 0) {
                                    retStr = male.concat(positiveOnly.toString());
                                } else {
                                    retStr = female.concat(positiveOnly.toString());
                                }
                                return retStr;
                                },
                        },
                    }, 
                },

                responsive: true,
                legend: {
                    position: 'bottom',
                },

                scales: {
                    x: {
                        stacked: false,
                        ticks: {
                            beginAtZero: true,
                            callback: (value) => { 
                                const val = Number(value);
                                const positiveOnly = val < 0 ? -val : val;
                                let retStr = positiveOnly; 
                                return retStr;
                            }
                        },
                    },
                    
                    y: {
                        stacked: true,
                        ticks: {
                            beginAtZero: true,
                        },
                        position: "left",
                    },
                },  
            },
        });
    }

    render(){
        return (
            <canvas className="chart-container" id="popChart" ref={this.chartRef} ></canvas>  
        )
    }

}

export default HomeChart

