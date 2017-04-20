#define Cred     RgbColor(255, 0, 0)
#define Cpink    RgbColor(255, 0, 128)
#define Clila    RgbColor(255, 0, 255)
#define Clila    RgbColor(255, 0, 255)
#define Cviolet  RgbColor(128, 0, 255)
#define Cblue    RgbColor(0, 0, 255)
#define Cmblue   RgbColor(0, 128, 255)
#define Ccyan    RgbColor(0, 255, 255)
#define Cgreen2   RgbColor(0, 255, 64)
#define Cgreen   RgbColor(0, 255, 0)
#define Cyellow  RgbColor(255, 255, 0)
#define Corange  RgbColor(255, 100, 0)
#define Cwhite   RgbColor(255, 255, 255)
#define Cblack   RgbColor(0)

#define NUMPIX 4

RgbColor oldColor = Cblack;

void setLedColor(const RgbColor &color) {
  if (color == oldColor) return;
  oldColor = color;
  //Serial <<"set color" << endl;
  for (int i=0; i < NUMPIX; i++) strip.SetPixelColor(i, color);
//  currentColor = color;
  strip.Show();


  //delay(10);
}


void mapColor(int current, int minVal, int maxVal) {
  //String colorRange ="uyrv";
  String colorRange ="gyr";
  // int minVal = 400;
  // int maxVal = 3400; //3000  ... /4 = 750
  //int current = 1300; // divv = 900
  current = constrain(current, minVal, maxVal);
  if (DEBUG) Serial << "mapcolor" << current << "," << minVal << "," << maxVal << endl;
  int steps = colorRange.length() - 1;
  float numPerVal = (float)(maxVal - minVal) / steps; // = 750
  int colorIdx = (current - minVal) / numPerVal; // = 1
  char colorStart = colorRange.charAt(colorIdx);
  char colorEnd   = colorRange.charAt(colorIdx + 1);
  int rangeStart = minVal + numPerVal * colorIdx;
  int currentX = current - rangeStart;
  float place = (float)currentX/numPerVal;
  RgbColor cStart = getColorMapping(colorStart);
  RgbColor cEnd   = getColorMapping(colorEnd);
  if (DEBUG) Serial << "color " << colorIdx << "," << place << endl;
  RgbColor c = RgbColor::LinearBlend(cStart, cEnd, place);
  c = RgbColor::LinearBlend(c, Cblack, min(1.0F, (float)analogRead(A1)/1020));
  setLedColor(c);

  //Serial << "curr: " << current << ", cs: " << colorStart << ", ce: " << colorEnd << ", place = " <<place << endl;
}

RgbColor getColorMapping(char c) {
  switch (c) {
    case 'r': return Cred;
    case 'v': return Cviolet;
    case 'b': return Cmblue;
    case 'u': return Cgreen2;
    case 'g': return Cgreen;
    case 'y': return Cyellow;
    case 'w': return Cwhite;
    case 'l': return Clila;
    case 'c': return Ccyan;
    case 'm': return Cmblue;
    default: return Cblack;
  }
}
