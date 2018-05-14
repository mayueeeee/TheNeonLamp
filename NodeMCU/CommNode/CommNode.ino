#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
bool state = false;
bool rainbow = false;
int color[3] = {0,0,0};
char r[3],g[3],b[3];
// Set these to run example.
#define FIREBASE_HOST "the-neon-lamp.firebaseio.com"
#define WIFI_SSID "PoRr!!"
#define WIFI_PASSWORD "por123456"
String S_receive;

bool stringToBool(String bibi){
  if(bibi.toInt()==0){
    return false;
  }
  return true;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST);
}

void loop() {
  // put your main code here, to run repeatedly:
  state = Firebase.getBool("state");
  rainbow = Firebase.getBool("color/rainbow");
  color[0] = Firebase.getInt("color/rgb/r");
  color[1] = Firebase.getInt("color/rgb/g");
  color[2] = Firebase.getInt("color/rgb/b");
  digitalWrite(2, state);
  Serial.print("[");
  sprintf(r,"%03d",color[0]);
  //  Serial.print(color[0]);
  Serial.print(r);
  Serial.print(",");
  sprintf(g,"%03d",color[1]);
//  Serial.print(color[1]);
  Serial.print(g);
  Serial.print(",");
  sprintf(b,"%03d",color[2]);
//  Serial.print(color[2]);
  Serial.print(b);
  Serial.print(",");
  Serial.print(state);
  Serial.print(",");
  Serial.print(rainbow);
  Serial.println("]");

  if (Serial.available() > 0) {    
    S_receive = Serial.readStringUntil('\n');
    Serial.print("R: ");
    Serial.println(S_receive.substring(1,4));
    Serial.print("G: ");
    Serial.println(S_receive.substring(5,8));
    Serial.print("B: ");
    Serial.println(S_receive.substring(9,12));
    Serial.print("State: ");
    Serial.println(S_receive.substring(13,14));
    Serial.print("Rainbow: ");
    Serial.println(S_receive.substring(15,16));
    // Push value to Firebase
    Firebase.setInt("color/rgb/r",S_receive.substring(1,4).toInt());
    Firebase.setInt("color/rgb/g",S_receive.substring(5,8).toInt());
    Firebase.setInt("color/rgb/b",S_receive.substring(9,12).toInt());
    Firebase.setBool("color/rainbow",stringToBool(S_receive.substring(13,14)));
    Firebase.setBool("state",stringToBool(S_receive.substring(15,16)));
    
    
  }

}
