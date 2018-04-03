import React, {Component} from 'react';
import styled from 'styled-components'
import BGWarpper from './Components/BackgroundWarpper'
import NeonText from './Components/NeonText'
import {Col, Row, Container} from 'reactstrap'
import ColorSelect from './Components/ColorPicker'

const FlexContainer = styled(Container)`
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
`

const HeaderWarper = styled.div `
  padding-top: 3.5vh
`
class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      color: "#000",
      status: true
    }
  }

  setColor = (color) =>{
    this.setState({color: color.hex})
    console.log("Change color to"+color.hex)

  }

  render() {
    return (
      <BGWarpper color="#000" full className="text-center">
        <Container fluid>
          <HeaderWarper>
            <Row>

              <Col xs={12}>
                <NeonText glow_color={this.state.color} >THE NEON LAMP</NeonText>
              </Col>

            </Row>
          </HeaderWarper>
          <Row>
            <Col
              xs={12}
              md={{
              size: 6,
              offset: 3
            }}><ColorSelect color={this.state.color} handleSetColor={this.setColor} /></Col>
          </Row>

        </Container>

      </BGWarpper>
    );
  }
}

export default App;
