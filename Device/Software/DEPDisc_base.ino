/*  Rui Santos & Sara Santos - Random Nerd Tutorials
    THIS EXAMPLE WAS TESTED WITH THE FOLLOWING HARDWARE:
    1) ESP32-2432S028R 2.8 inch 240×320 also known as the Cheap Yellow Display (CYD): https://makeradvisor.com/tools/cyd-cheap-yellow-display-esp32-2432s028r/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/cyd/
    2) REGULAR ESP32 Dev Board + 2.8 inch 240x320 TFT Display: https://makeradvisor.com/tools/2-8-inch-ili9341-tft-240x320/ and https://makeradvisor.com/tools/esp32-dev-board-wi-fi-bluetooth/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/esp32-tft/
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

#include <SPI.h>

/*  Install the "TFT_eSPI" library by Bodmer to interface with the TFT Display - https://github.com/Bodmer/TFT_eSPI
    *** IMPORTANT: User_Setup.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE User_Setup.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd/ or https://RandomNerdTutorials.com/esp32-tft/   */
#include <TFT_eSPI.h>

// Install the "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen - https://github.com/PaulStoffregen/XPT2046_Touchscreen
// Note: this library doesn't require further configuration
#include <XPT2046_Touchscreen.h>

TFT_eSPI tft = TFT_eSPI();

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

const int DEP_PIN = 4;
const int MOTOR_PIN1 = 26;
const int MOTOR_PIN2 = 27;

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FONT_SIZE 4

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

// Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
void printTouchToSerial(int touchX, int touchY, int touchZ) {
  Serial.print("X = ");
  Serial.print(touchX);
  Serial.print(" | Y = ");
  Serial.print(touchY);
  Serial.print(" | Pressure = ");
  Serial.print(touchZ);
  Serial.println();
}

// Print Touchscreen info about X, Y and Pressure (Z) on the TFT Display
void printTouchToDisplay(int touchX, int touchY, int touchZ) {
  // Clear TFT screen
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  int centerX = SCREEN_WIDTH / 2;
  int textY = 80;
 
  String tempText = "X = " + String(touchX);
  tft.drawCentreString(tempText, centerX, textY, FONT_SIZE);

  textY += 20;
  tempText = "Y = " + String(touchY);
  tft.drawCentreString(tempText, centerX, textY, FONT_SIZE);

  textY += 20;
  tempText = "Pressure = " + String(touchZ);
  tft.drawCentreString(tempText, centerX, textY, FONT_SIZE);
}

void setup() {
  Serial.begin(115200);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);

  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
  touchscreen.setRotation(1);

  // Start the tft display
  tft.init();
  // Set the TFT display rotation in landscape mode (flipped for assembly in housing)
  tft.setRotation(3);

  // Clear the screen before writing to it
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  
  // Set X and Y coordinates for center of display
  int centerX = SCREEN_WIDTH / 2;
  int centerY = SCREEN_HEIGHT / 2;
  int onethirdY = SCREEN_HEIGHT / 3;
  int twothirdsY = 2 * SCREEN_HEIGHT / 3;

  tft.fillRoundRect((centerX - 140), (onethirdY - 25), 280, 50, 10, TFT_WHITE);
  tft.drawCentreString("Experimental mode", centerX, (onethirdY - 10), FONT_SIZE);
  tft.fillRoundRect((centerX - 140), (twothirdsY - 25), 280, 50, 10, TFT_WHITE);
  tft.drawCentreString("Run from SD card", centerX, (twothirdsY - 10), FONT_SIZE);
  tft.drawCentreString("Experimental mode currently always active", centerX, (twothirdsY + 80), 2);
}

void loop() {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z) info on the TFT display and Serial Monitor
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    // Calibrate Touchscreen points with map function to the correct width and height
    x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
    z = p.z;

    printTouchToSerial(x, y, z);
    //printTouchToDisplay(x, y, z);

    delay(100);
  }
  if(Serial.available()){
    String input = Serial.readStringUntil('\n');
    input.trim();  // Remove any leading or trailing whitespace

    // Check if the input starts with "freq"
    if (input.startsWith("freq")) {
      // Extract the value after "freq"
      int spaceIndex = input.indexOf(' ');
      if (spaceIndex != -1) {
        String valueString = input.substring(spaceIndex + 1);
        int value = valueString.toInt();

        // Perform analogWrite on pin 1 with the extracted value
        ledcDetach(DEP_PIN);
        if (value > 0) {
          ledcAttach(DEP_PIN, value, 1);
          ledcWrite(DEP_PIN, 1);
          Serial.print("Set freq to ");
          Serial.println(value);
        } else if (value == 0) {
          Serial.println("Stop DEP");
        }
      }
    }
    // Check if the input starts with "spin"
    else if (input.startsWith("spin")) {
      // Extract the value after "spin"
      int spaceIndex = input.indexOf(' ');
      if (spaceIndex != -1) {
        String valueString = input.substring(spaceIndex + 1);
        int value = valueString.toInt();

        // Perform analogWrite on pin 2 or 3 based on the value's sign
        if (value > 0) {
          analogWrite(MOTOR_PIN1, value);
          analogWrite(MOTOR_PIN2, 0);
          Serial.print("Spin forward with value ");
          Serial.println(value);
        } else if (value < 0) {
          analogWrite(MOTOR_PIN1, 0);
          analogWrite(MOTOR_PIN2, -value);  // Use the positive of the negative value
          Serial.print("Spin backward with value ");
          Serial.println(-value);
        } else if (value == 0) {
          analogWrite(MOTOR_PIN1, 0);
          analogWrite(MOTOR_PIN2, 0);
          Serial.println("Stop motor");
        }
      }
    }
  }
}