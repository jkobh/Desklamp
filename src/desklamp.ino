// desklamp.ino
#include "config.h"
#include "led_functions.h"

// Definition aller globalen Variablen
rmt_item32_t pixels[LED_COUNT * 32];
int currentState = 0;
unsigned long buttonPressTime = 0;
bool lastButtonState = HIGH;
bool isLongPress = false;
uint8_t currentBrightness = BRIGHTNESS_LEVELS[NUM_BRIGHTNESS_LEVELS-1];
unsigned long lastAnimationUpdate = 0;
int currentBrightnessIndex = NUM_BRIGHTNESS_LEVELS-1;

void setup() {
  // Pin Konfiguration
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BRIGHTNESS_PIN, INPUT_PULLUP);
  
  // RMT Setup
  setupRMT();
  
  // Optional: Serial für Debugging
  Serial.begin(115200);
}

void loop() {
  handleButtonPress();
  updateColor();
  // handleBrightnessControl();
}