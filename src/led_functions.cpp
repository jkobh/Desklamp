// led_functions.cpp
#include "led_functions.h"

// Externe Variablen
extern rmt_item32_t pixels[LED_COUNT * 32];
extern int currentState;
extern unsigned long buttonPressTime;
extern bool lastButtonState;
extern bool isLongPress;
extern uint8_t currentBrightness;
extern unsigned long lastAnimationUpdate;
extern int currentBrightnessIndex;

// RMT Setup Implementation
void setupRMT() {
  rmt_config_t config;
  config.rmt_mode = RMT_MODE_TX;
  config.channel = RMT_CHANNEL;
  config.gpio_num = (gpio_num_t)LED_PIN;
  config.mem_block_num = 3;
  config.tx_config.loop_en = false;
  config.tx_config.carrier_en = false;
  config.tx_config.idle_output_en = true;
  config.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;
  config.clk_div = 1;
  
  rmt_config(&config);
  rmt_driver_install(config.channel, 0, 0);
}

// Button Handler Implementation
void handleButtonPress() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH) {
    buttonPressTime = millis();
    isLongPress = false;
  }
  else if (buttonState == LOW && !isLongPress) {
    if (millis() - buttonPressTime >= LONG_PRESS_TIME) {
      currentState = NUM_STATES;  // Ausschalt-Zustand
      isLongPress = true;
      Serial.println(currentState);
    }
  }
  else if (buttonState == HIGH && lastButtonState == LOW) {
    if (!isLongPress && (millis() - buttonPressTime < LONG_PRESS_TIME)) {
      currentState = (currentState + 1) % NUM_STATES;
      Serial.println(currentState);
    }
  }

  lastButtonState = buttonState;
}

// Brightness Control Implementation
void handleBrightnessControl() {
  static bool lastBrightnessButtonState = HIGH;
  bool brightnessButtonState = digitalRead(BRIGHTNESS_PIN);
  
  if (brightnessButtonState == LOW && lastBrightnessButtonState == HIGH) {
    currentBrightnessIndex = (currentBrightnessIndex + 1) % NUM_BRIGHTNESS_LEVELS;
    currentBrightness = BRIGHTNESS_LEVELS[currentBrightnessIndex];
    updateColor();
  }
  
  lastBrightnessButtonState = brightnessButtonState;
}

// LED Control Functions
void setColorButton(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

void setPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  uint32_t color = (g << 24) | (r << 16) | (b << 8) | w;  // GRBW Format
  for (int bit = 31; bit >= 0; bit--) {
    uint32_t bit_is_set = color & (1 << bit);
    pixels[index * 32 + (31 - bit)].level0 = 1;
    pixels[index * 32 + (31 - bit)].level1 = 0;
    if (bit_is_set) {
      pixels[index * 32 + (31 - bit)].duration0 = WS2812_T1H;
      pixels[index * 32 + (31 - bit)].duration1 = WS2812_T1L;
    } else {
      pixels[index * 32 + (31 - bit)].duration0 = WS2812_T0H;
      pixels[index * 32 + (31 - bit)].duration1 = WS2812_T0L;
    }
  }
}

void show() {
  rmt_write_items(RMT_CHANNEL, pixels, LED_COUNT * 32, true);
  rmt_wait_tx_done(RMT_CHANNEL, pdMS_TO_TICKS(100));
}

// Color Mode Implementations
void colorMode1() {
  for(int i = 0; i < LED_COUNT; i++) {
    setPixel(i, currentBrightness, currentBrightness, currentBrightness, 0);
  }
  show();
}

void colorMode2() {
  for(int i = 0; i < LED_COUNT; i++) {
    setPixel(i, 0, 0, 0, currentBrightness);
  }
  show();
}

void colorMode3() {
  for(int i = 0; i < LED_COUNT; i++) {
    setPixel(i, 10, 10, 10, 10);
  }
  show();
}

void colorMode4() {
  for(int i = 0; i < LED_COUNT; i++) {
    setPixel(i, 20, 20, 20, 20);
  }
  show();
}

void colorModeOff() {
  for(int j = 0; j < LED_COUNT; j++) {
    for(int i = 0; i < j; i++) {
      setPixel(i, 0, 0, 0, 0);
    }
    show();
  }
  for(int i = 0; i < LED_COUNT; i++) {
    setPixel(i, 0, 0, 0, 0);
  }
  show();
}

// Animation Mode Implementations
void rainbowMode() {
  static uint16_t hue = 0;
  
  if (millis() - lastAnimationUpdate >= ANIMATION_SPEED) {
    for (int i = 0; i < LED_COUNT; i++) {
      Color color = getHSVColor((hue + (i * RAINBOW_STEP)) % 360, 255, currentBrightness);
      setPixel(i, color.r, color.g, color.b, 0);
    }
    show();
    hue = (hue + 1) % 360;
    lastAnimationUpdate = millis();
  }
}

void breathingMode() {
  static uint8_t breathValue = 0;
  static bool increasing = true;
  
  if (millis() - lastAnimationUpdate >= BREATH_SPEED) {
    if (increasing) {
      breathValue++;
      if (breathValue >= currentBrightness) increasing = false;
    } else {
      breathValue--;
      if (breathValue == 0) increasing = true;
    }
    
    for (int i = 0; i < LED_COUNT; i++) {
      setPixel(i, breathValue, breathValue, breathValue, 0);
    }
    show();
    lastAnimationUpdate = millis();
  }
}

void wavesMode() {
  static uint8_t offset = 0;
  
  if (millis() - lastAnimationUpdate >= ANIMATION_SPEED) {
    for (int i = 0; i < LED_COUNT; i++) {
      uint8_t sinVal = (sin(((i + offset) * 2 * PI) / WAVE_LENGTH) + 1) * 127;
      uint8_t brightness = (sinVal * currentBrightness) / 255;
      setPixel(i, brightness, 0, brightness, 0);
    }
    show();
    offset = (offset + 1) % WAVE_LENGTH;
    lastAnimationUpdate = millis();
  }
}

void sparkleMode() {
  if (millis() - lastAnimationUpdate >= ANIMATION_SPEED) {
    for (int i = 0; i < LED_COUNT; i++) {
      setPixel(i, 0, 0, 0, 0);
    }
    
    for (int i = 0; i < LED_COUNT / 10; i++) {
      int pos = random(LED_COUNT);
      setPixel(pos, currentBrightness, currentBrightness, currentBrightness, 0);
    }
    show();
    lastAnimationUpdate = millis();
  }
}

// Color Conversion Helper
Color getHSVColor(uint16_t hue, uint8_t sat, uint8_t val) {
  uint8_t r, g, b;
  
  uint8_t hi = (hue / 60) % 6;
  uint16_t f = hue % 60;
  uint8_t p = (val * (255 - sat)) / 255;
  uint8_t q = (val * (255 - (sat * f) / 60)) / 255;
  uint8_t t = (val * (255 - (sat * (60 - f)) / 60)) / 255;

  switch (hi) {
    case 0: r = val; g = t; b = p; break;
    case 1: r = q; g = val; b = p; break;
    case 2: r = p; g = val; b = t; break;
    case 3: r = p; g = q; b = val; break;
    case 4: r = t; g = p; b = val; break;
    default: r = val; g = p; b = q; break;
  }

  return Color(r, g, b);
}

// Update Color State
void updateColor() {
  switch (currentState) {
    case 0:
      setColorButton(255 * currentBrightness / 255, 0, 0);
      colorMode1();
      break;
    case 1:
      setColorButton(0, 255 * currentBrightness / 255, 0);
      colorMode2();
      break;
    case 2:
      setColorButton(0, 0, 255 * currentBrightness / 255);
      colorMode3();
      break;
    case 3:
      setColorButton(100 * currentBrightness / 255, 100 * currentBrightness / 255, 100 * currentBrightness / 255);
      colorMode4();
      break;
    case 4:
      rainbowMode();
      break;
    case 5:
      breathingMode();
      break;
    case 6:
      wavesMode();
      break;
    case 7:
      sparkleMode();
      break;
    default:
      setColorButton(0, 0, 0);
      colorModeOff();
      break;
  }
}