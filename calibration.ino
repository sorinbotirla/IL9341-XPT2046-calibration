/*
  Sketch to generate the setup() calibration values, these are reported
  to the Serial Monitor.

  The sketch has been tested on the ESP8266 and screen with XPT2046 driver.
*/

#include <SPI.h>
#include <TFT_eSPI.h>      // Hardware-specific library

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
String tftCalDataPortraitString = "Portrait: ";
String tftCalDataLandscapeString = "Landscape: ";
uint16_t calDataPortrait[5];
uint16_t calDataLandscape[5];

//------------------------------------------------------------------------------------------

void setup() {
  // Use serial port
  Serial.begin(115200);
  Serial.println("Initialized");

  // Initialise the TFT screen
  tft.init();

  // Calibrate the touch screen and retrieve the scaling factors
  touch_calibrate_portrait();
  touch_calibrate_landscape();

/*
  // Replace above line with the code sent to Serial Monitor
  // once calibration is complete, e.g.:
  uint16_t calData[5] = { 286, 3534, 283, 3600, 6 };
  tft.setTouch(calData);
*/

  // Clear the screen
  tft.setTouch(calDataPortrait);
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.drawCentreString("Touch screen to test!",tft.width()/2, tft.height()/3, 2);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawCentreString("Calibration data:",tft.width()/2, tft.height()/2, 2);
  tft.drawCentreString(tftCalDataPortraitString,tft.width()/2, tft.height()/1.7, 2);
  tft.drawCentreString(tftCalDataLandscapeString,tft.width()/2, tft.height()/1.5, 2);
}

//------------------------------------------------------------------------------------------

void loop(void) {
  uint16_t x = 0, y = 0; // To store the touch coordinates

  // Pressed will be set true is there is a valid touch on the screen
  bool pressed = tft.getTouch(&x, &y);

  // Draw a white spot at the detected coordinates
  if (pressed) {
    tft.fillCircle(x, y, 1, TFT_YELLOW);
    //Serial.print("x,y = ");
    //Serial.print(x);
    //Serial.print(",");
    //Serial.println(y);
  }
}

//------------------------------------------------------------------------------------------

// Code to run a screen calibration, not needed when calibration values set in setup()
void touch_calibrate_portrait()
{
  // Set the rotation to the orientation you wish to use in your project before calibration
  // (the touch coordinates returned then correspond to that rotation only)
  tft.setRotation(0);
  uint8_t calDataOK = 0;
  

  // Calibrate
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.println("Touch corners as indicated");

  tft.setTextFont(1);
  tft.println();

  tft.calibrateTouch(calDataPortrait, TFT_MAGENTA, TFT_BLACK, 15);

  Serial.println(); Serial.println();
  Serial.println("// Use this calibration code in setup() for portrait rotation (tft.setRotation(0)):");
  Serial.print("  uint16_t calData[5] = ");
  Serial.print("{ ");

  for (uint8_t i = 0; i < 5; i++)
  {
    Serial.print(calDataPortrait[i]);
    tftCalDataPortraitString += calDataPortrait[i];
    if (i < 4) {
      Serial.print(", ");
      tftCalDataPortraitString += ", ";
    }
  }


  Serial.println(" };");
  Serial.print("  tft.setTouch(calDataPortrait);");
  Serial.println(); Serial.println();

  tft.fillScreen(TFT_BLACK);
  // tft.setTextSize(1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("next: landscape calibration");
  tft.println("Calibration code sent to Serial port.");

  delay(2000);
}

void touch_calibrate_landscape()
{
  // Set the rotation to the orientation you wish to use in your project before calibration
  // (the touch coordinates returned then correspond to that rotation only)
  tft.setRotation(1);
  uint8_t calDataOK = 0;
  

  // Calibrate
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.println("Touch corners as indicated");

  tft.setTextFont(1);
  tft.println();

  tft.calibrateTouch(calDataLandscape, TFT_MAGENTA, TFT_BLACK, 15);

  Serial.println(); Serial.println();
  Serial.println("// Use this calibration code in setup() for landscape rotation (tft.setRotation(1)):");
  Serial.print("  uint16_t calData[5] = ");
  Serial.print("{ ");

  for (uint8_t i = 0; i < 5; i++)
  {
    Serial.print(calDataLandscape[i]);
    tftCalDataLandscapeString += calDataLandscape[i];
    if (i < 4) {
      Serial.print(", ");
      tftCalDataLandscapeString += ", ";
    }
  }


  Serial.println(" };");
  Serial.print("  tft.setTouch(calData);");
  Serial.println(); Serial.println();

  tft.fillScreen(TFT_BLACK);
  // tft.setTextSize(1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Calibration complete!");
  tft.println("Calibration code sent to Serial port.");

  delay(2000);
}
