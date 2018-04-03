import styled,{keyframes} from 'styled-components'

// const neonGlow = keyframes`
//     from {
//         text-shadow: 0 0 10px #fff, 0 0 20px #fff, 0 0 30px #fff, 0 0 40px #FF1177, 0 0 70px #FF1177, 0 0 80px #FF1177, 0 0 100px #FF1177, 0 0 150px #FF1177;
//     }
//     to {
//         text-shadow: 0 0 5px #fff, 0 0 10px #fff, 0 0 15px #fff, 0 0 20px #FF1177, 0 0 35px #FF1177, 0 0 40px #FF1177, 0 0 50px #FF1177, 0 0 75px #FF1177;
//     }
// `


const neonGlow = keyframes`
    from {
        text-shadow: 0 0 10px #fff, 0 0 20px #fff, 0 0 30px #fff, 0 0 40px ${props => props.glow_color}, 0 0 70px ${props => props.glow_color}, 0 0 80px ${props => props.glow_color}, 0 0 100px ${props => props.glow_color}, 0 0 150px ${props => props.glow_color};
    }
    to {
        text-shadow: 0 0 5px #fff, 0 0 10px #fff, 0 0 15px #fff, 0 0 20px ${props => props.glow_color}, 0 0 35px ${props => props.glow_color}, 0 0 40px ${props => props.glow_color}, 0 0 50px ${props => props.glow_color}, 0 0 75px ${props => props.glow_color};
    }
`



const neonTXT = styled.h1`
    color: #fff;
    font-family: 'monotonregular';
    font-size: 3.5rem;
    animation: neon 1.5s ease-in-out infinite alternate;
    @media only screen and (min-width: 1024px) {       
        font-size: 5.5em;
    }

    @keyframes neon {
        from {
            text-shadow: 0 0 10px #fff, 0 0 20px #fff, 0 0 30px #fff, 0 0 40px ${props => props.glow_color}, 0 0 70px ${props => props.glow_color}, 0 0 80px ${props => props.glow_color}, 0 0 100px ${props => props.glow_color}, 0 0 150px ${props => props.glow_color};
        }
        to {
            text-shadow: 0 0 5px #fff, 0 0 10px #fff, 0 0 15px #fff, 0 0 20px ${props => props.glow_color}, 0 0 35px ${props => props.glow_color}, 0 0 40px ${props => props.glow_color}, 0 0 50px ${props => props.glow_color}, 0 0 75px ${props => props.glow_color};
        }
      }
    
`


export default neonTXT