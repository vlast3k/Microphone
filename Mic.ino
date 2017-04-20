
#define GAIN_60 1
#define GAIN_50 2
#define GAIN_40 3

const int sampleWindow = 100; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void readMic() {
  int g40, g50, g60;
  getPPAll(g40, g50, g60);
  avg40.addValue(g40);
 // avg50.addValue(g50);
  //avg60.addValue(g60);
}

void setGain(int gain) {
  switch(gain) {
    case GAIN_60: pinMode(PIN_GAIN, INPUT); break;
    case GAIN_50: pinMode(PIN_GAIN, OUTPUT); digitalWrite(PIN_GAIN, LOW); break;
    case GAIN_40: pinMode(PIN_GAIN, OUTPUT); digitalWrite(PIN_GAIN, HIGH); break;
  }
}

void getPPAll(int &g40, int &g50, int &g60) {
  g40 = getPP(GAIN_40);
 // g50 = getPP(GAIN_50);
 // g60 = getPP(GAIN_60);
}
int getPP(int gain) {
  // setGain(gain);
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow) {
      sample = analogRead(A0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   return peakToPeak;

}
