import React, {Component} from 'react';
import styled from 'styled-components'
import BGWarpper from './Components/BackgroundWarpper'
import NeonText from './Components/NeonText'
import NeonButton from './Components/NeonButton'
import {Col, Row, Container, Button} from 'reactstrap'
import ColorSelect from './Components/ColorPicker'
import {db,updateColor,toggleLight,toggleRainbow} from './Utils/Firebase'
const FlexContainer = styled(Container)`
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
`

const HeaderWarper = styled.div `
  padding-top: 3.5vh
`

const SectionWarper = styled.div `
  margin-top: 4vh;
`
class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      color: "#000",
      status: true
    }
  }

  setColor = (color) => {
    // console.log(color)
    this.setState({color: color.hex})
    console.log("Change color to" + color.hex)
    updateColor(color)

  }

  handleToggleLight = () =>{
    toggleLight()
  }

  render() {
    return (
      <BGWarpper color="#000" full className="text-center">
        <Container fluid>
          <HeaderWarper>
            <Row>

              <Col xs={12}>
                <NeonText glow_color={this.state.color}>THE NEON LAMP</NeonText>
              </Col>

            </Row>
          </HeaderWarper>
          <Row>
            <Col
              xs={12}
              md={{
              size: 6,
              offset: 3
            }}><ColorSelect color={this.state.color} handleSetColor={this.setColor}/></Col>
          </Row>
          <SectionWarper>
            <Container>
            <Row>
              
              <Col>
                <NeonButton color="primary" size="lg" block onClick={toggleLight}>Turn On/Off</NeonButton>
              </Col>
              <Col>
                <NeonButton color="primary" size="lg" block onClick={toggleRainbow}>Rainbow</NeonButton>
              </Col>
            </Row>
            </Container>
          </SectionWarper>
        </Container>

      </BGWarpper>
    );
  }
}

export default App;
