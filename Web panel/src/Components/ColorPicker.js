import React from 'react'
import { CirclePicker } from 'react-color';
import Colors from '../colors.json'

export default class ColorPicker extends React.Component {
  constructor(props) {
    super(props);
    this.state = { 
      width: 0, 
      height: 0 ,
      color: this.props.color
    };
    this.updateWindowDimensions = this.updateWindowDimensions.bind(this);
  }
  
  componentDidMount() {
    this.updateWindowDimensions();
    window.addEventListener('resize', this.updateWindowDimensions);
  }
  
  componentWillUnmount() {
    window.removeEventListener('resize', this.updateWindowDimensions);
  }
  
  updateWindowDimensions() {
    this.setState({ width: window.innerWidth, height: window.innerHeight });
    console.log("width "+window.innerWidth+" height"+window.innerHeight)
  }

  calculateSize = () =>{
    if(this.state.width>=1024){
      return this.state.width*6/100
    }
    else{
      return this.state.width*20/100
    }
  }

  handleColorChange = (color, event) => {
    // console.log(color.hex)
    // this.setState({color: color.hex})
    // console.log(this.state.color)
    this.props.handleSetColor(color)

  }

  render() {
    var x = this.calculateSize()
    return (
      <div className="text-center">
        <CirclePicker circleSize={x} width="auto" colors = {Colors} onChange={ this.handleColorChange }/>
      </div>
     
         
        
     
    )
  }
}