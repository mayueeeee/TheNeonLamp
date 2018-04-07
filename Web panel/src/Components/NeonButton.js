import {Button} from 'reactstrap'
import styled from 'styled-components'

const NeonBtn = styled(Button)`
    margin-top: 10px;
    border: 4px solid #00fff5;
    background-color: transparent;
    border-radius: 100px 100px 100px 100px;
    color: #00fff5;
    font-family: 'monotonregular';
    &:hover {
        // background-color: #00fff5;
        background-color: transparent;
        box-shadow: 0 0 20px #00fff5; 
        border-color: #00fff5;
        color: #00fff5;
    }
`

export default NeonBtn