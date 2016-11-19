
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(1, 0); // RX, TX

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleStream.h>
#include <SimpleTimer.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "670882a7b1a848d393d00cda0c6b8266";

WidgetRTC rtc;
BLYNK_ATTACH_WIDGET(rtc, V5);

WidgetBridge bridge1(V12);

SimpleTimer tm;

int relay1 = 14;
int automode = 7; //on and off on timer specified time
int timermode = 8; //timer in blynk app
int manualmode = 9; //turn on without timer in app

void switchrelay() {
  if((digitalRead(automode)==HIGH) && ((digitalRead(timermode)==HIGH) || (digitalRead(manualmode)==HIGH))) {
    if(digitalRead(relay1)==LOW) {
      digitalWrite(relay1,HIGH);
    }
    else {
      digitalWrite(relay1,LOW);
    }
  }
  else if((digitalRead(automode)==LOW) && ((digitalRead(timermode)==HIGH) || (digitalRead(manualmode)==HIGH))) {
    digitalWrite(relay1,LOW);
  }
  else if((digitalRead(timermode)==LOW) && (digitalRead(manualmode)==LOW)) {
    digitalWrite(relay1,HIGH);
  }
}

void setup()
{
  // Debug console
  DebugSerial.begin(115200);

  // Blynk will work through Serial
  Serial.begin(115200);
  Blynk.begin(auth, Serial);
  pinMode(relay1,OUTPUT);
  pinMode(automode,OUTPUT);
  pinMode(timermode,OUTPUT);
  pinMode(manualmode,OUTPUT);

  rtc.begin();

  tm.setInterval(30000L, switchrelay);
}

void loop()
{
  Blynk.run();
  tm.run();
}

