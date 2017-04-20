/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/
#include <Streaming.h>
#include <RunningAverage.h>
#include <NeoPixelBus.h>
#define PIN_GAIN 3

bool DEBUG = true;

int lowCur = 100, lowPrev = 7;
uint32_t lowPrevTime = 0;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(4, 4);
RunningAverage avg(30), avg40(30), avg50(20), avg60(20);

void setup() {
   Serial.begin(115200L);
   strip.Begin();
   mapColor(30, 0, 40);
   pinMode(PIN_GAIN, OUTPUT);
   digitalWrite(PIN_GAIN, HIGH);
}

void loop() {
   readPots();
   readMic();
   //int y = handleLow(getPP() / 6);
   //avg.addValue(y);
   //int iavg = avg.getAverage();
   //drawSerial(y, iavg);
   drawSerial2();
   mapColor(getDB(), 30, map(analogRead(A2), 0, 1024, 50, 95));
}

void readPots() {
  if (DEBUG) Serial << analogRead(A1) << " " << analogRead(A2) << endl;
}

int handleLow(int y) {
  lowCur = min(y, lowCur);
  if (millis() - lowPrevTime > 60000) {
    lowPrev = lowCur;
    lowPrevTime = millis(); 
    lowCur = 100;
  }
  return max(y - lowPrev, 0);
}

int getDB() {
  double db = log10(avg40.getAverage()) * 35;
  return round(db);
}
void drawSerial() {
  double db = log10(avg40.getAverage()) * 35;
  if (DEBUG) Serial << avg40.getAverage() << " " << db << endl;
//  Serial << avg40.getAverage() << " " <<  avg50.getAverage() << " " << avg60.getAverage() << " -- ";
//  Serial << avg50.getAverage()  / avg40.getAverage() << " " <<  avg60.getAverage() / avg50.getAverage() << " " << avg60.getAverage() / avg40.getAverage() << endl;
}
void drawSerial2() {
   if (DEBUG) {
     int i =0;
     int db = getDB();
     Serial << db << " ";
     for (; i < db - 30; i++) Serial << "#";
     Serial << endl;
   }
}



