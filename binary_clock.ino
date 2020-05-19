#include <Adafruit_CircuitPlayground.h>
#define DEBOUNCE 150
#define MAX_HOUR 12
#define MAX_MINUTE 60

int minute;
int hour;
bool leftButton;
bool rightButton;
const long interval = 60000;
unsigned long previousMillis;


void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  minute = 0;
  hour = 0;
  previousMillis = 0;
}

void loop() {
  checkButtonPress();
  checkTime();
}

void displayBinary(int timeElement, int colorCode, bool reverse=false) {
  String binaryTime = String(timeElement, BIN);
  int stringLength = binaryTime.length();
  if(reverse) {
    for(int i=stringLength - 1, l=0; i >= 0; i--, l++){
      if(binaryTime[i] == '1') {
        setPixel(l, colorCode);
      }
    }
  }
  else {
    for(int i=stringLength - 1, l=9; i >= 0; i--, l--){
      if(binaryTime[i] == '1') {
        setPixel(l, colorCode);
      }
    }
  }
}

void setPixel(int pixelNumber, int colorCode) {
  if(colorCode == 1) {
    CircuitPlayground.setPixelColor(pixelNumber, 255, 255, 255);
  }
  if(colorCode == 2) {
    CircuitPlayground.setPixelColor(pixelNumber, 255, 0, 0);
  }
}

void checkButtonPress() {
  leftButton = CircuitPlayground.leftButton();
  rightButton = CircuitPlayground.rightButton();
  if(leftButton) {
    hour++;
    redrawFace();
    delay(DEBOUNCE);
  }
  if(rightButton) {
    minute++;
    redrawFace();
    delay(DEBOUNCE);
  }
  
}

void checkTime() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    minute ++;
    redrawFace();
  }
  
}

void checkTimeOverflow() {
  if(minute >= MAX_MINUTE) {
    minute = 0;
    hour ++;
  }
  if(hour > MAX_HOUR) hour = 0;
}

void redrawFace() {
  checkTimeOverflow();
  CircuitPlayground.clearPixels();
  displayBinary(minute, 1);
  displayBinary(hour, 2, true);
  String currentTime = (String) hour + ':' +  (String) minute;
  Serial.println(currentTime);
}
