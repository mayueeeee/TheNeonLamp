import styled from 'styled-components'
const bg = styled.div`
  background-color: ${props => props.color};
  ${props => props.full ? 'width: 100vw' : ''}
  ${props => props.full ? 'height: 120vh' : ''}
`
export default bg