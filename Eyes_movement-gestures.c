//including LedControl library from C++ to display eyes on the mini LED Display which is connected to the arduino
//including LedControl library from C++ to display eyes on the mini LED Display which is connected to the arduino
#include <LedControl.h>

// Initialize LedControl for the MAX7219
// Parameters: DIN pin, CLK pin, CS pin, number of displays
LedControl lc = LedControl(12, 11, 10, 1);

// Define simple eye patterns (8x8 bitmaps)
byte eyeCenter[8] = {
  B00111100,
  B01000010,
  B10011001,
  B10111101,
  B10111101,
  B10011001,
  B01000010,
  B00111100
};

byte eyeLeft[8] = {
  B00111100,
  B01000010,
  B10011001,
  B10111101,
  B10011101,
  B10001101,
  B01000110,
  B00111000
};

byte eyeRight[8] = {
  B00111100,
  B01000010,
  B10011001,
  B10111101,
  B10111100,
  B10110010,
  B01100010,
  B00111100
};

byte eyeUp[8] = {
  B00111100,
  B01111110,
  B10000001,
  B10111101,
  B10111101,
  B10111101,
  B10000001,
  B01111110
};

byte eyeDown[8] = {
  B00111100,
  B01000010,
  B10111101,
  B10111101,
  B10111101,
  B10000001,
  B01111110,
  B00111100
};

void setup() {
  // Initialize the LED display
  lc.shutdown(0, false);       // Wake up display
  lc.setIntensity(0, 8);       // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);          // Clear display register
}

void loop() {
  // Display eye centered
  displayEye(eyeCenter);
  delay(1000);

  // Eye looking left
  displayEye(eyeLeft);
  delay(1000);

  // Eye looking right
  displayEye(eyeRight);
  delay(1000);

  // Eye looking up
  displayEye(eyeUp);
  delay(1000);

  // Eye looking down
  displayEye(eyeDown);
  delay(1000);
}

// Function to display an 8x8 pattern on the LED matrix
void displayEye(byte eyePattern[8]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, eyePattern[row]);
  }
}
