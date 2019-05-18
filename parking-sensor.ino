#include <NewPing.h>

//need to find pinout for my microcontroller
#define TRIGGER_PIN A2
#define ECHO_PIN A3
#define MAX_DISTANCE 400

//lights
#define RED_LIGHT 15
#define YELLOW_LIGHT 18
#define GREEN_LIGHT 19


//distances
#define RED_DISTANCE 30
#define YELLOW_DISTANCE 50
#define GREEN_DISTANCE 80

// NewPing setup of pins and maximum distance
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(GREEN_LIGHT, OUTPUT);
  pinMode(YELLOW_LIGHT, OUTPUT);
  pinMode(RED_LIGHT, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned int distance = getDistance();
  traffic(distance);
  delay(500);
}

void traffic(unsigned int distance) {
  int lightToTurnOn = getLightByDistance(distance);
  allLightsOff();
  if (lightToTurnOn != -1) {
    lightOn(lightToTurnOn);
  }
}

int getLightByDistance(unsigned int distance) {
  if (distance < 10) { //This first if statment is to help hide my failing sensor
    return -1;
  } else if (distance < RED_DISTANCE){
    return RED_LIGHT;
  } else if (distance < YELLOW_DISTANCE) {
    return YELLOW_LIGHT;
  }
  //default to green
  return GREEN_LIGHT;
}

void allLightsOff() {
  Serial.println("all off");
  digitalWrite(RED_LIGHT, LOW);
  digitalWrite(YELLOW_LIGHT, LOW);
  digitalWrite(GREEN_LIGHT, LOW);
}

void lightOff(int light) {
  digitalWrite(light, LOW);
}

void lightOn(int light) {
  Serial.print(light);
  Serial.println(" on");
  digitalWrite(light, HIGH);
}

unsigned int getDistance(){
  digitalWrite(17, LOW);
  unsigned int distance = sonar.ping_cm();
  Serial.print(distance);
  Serial.println("cm");
  digitalWrite(17, HIGH);
  return distance;
}
