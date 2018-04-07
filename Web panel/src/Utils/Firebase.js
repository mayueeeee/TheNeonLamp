import firebase from 'firebase'
import config from '../config.json'
const firebaseConfig = config.firebase_config
firebase.initializeApp(firebaseConfig);
export var db = firebase.database()

export const getColor  = () => {
    

}

export const updateColor = (color) => {
    console.log(color)
    // firebase.database().ref('color/rgb').set(color.rgb)
    // firebase.database().ref('color/hex').set(color.hex);
    firebase.database().ref('color').set({
        hex:color.hex,
        rainbow:false,
        rgb:color.rgb
    });

}

export const toggleLight = () => {
    firebase.database().ref('state').once("value").then(snapshot=>{
        console.log(snapshot.val())
        firebase.database().ref('state').set(!snapshot.val());
    })
}

export const toggleRainbow = () => {
    firebase.database().ref('color/rainbow').set(true);
}