#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
bool state = false;
bool rainbow = false;
int color[3] = {0,0,0};
// Set these to run example.
#define FIREBASE_HOST "the-neon-lamp.firebaseio.com"
#define WIFI_SSID "Mayueeeee"
#define WIFI_PASSWORD ""

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
  Serial.print(color[0]);
  Serial.print(",");
  Serial.print(color[1]);
  Serial.print(",");
  Serial.print(color[2]);
  Serial.print(",");
  Serial.print(state);
  Serial.print(",");
  Serial.print(rainbow);
  Serial.println("]");

}
