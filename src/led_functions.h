// led_functions.h
#pragma once
#include "config.h"
#include <Arduino.h>  // Für millis() und random()
#include <math.h>    // Für sin() und PI

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t w;
  
  Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t white = 0) 
    : r(red), g(green), b(blue), w(white) {}
};

// Grundlegende LED-Funktionen
void setupRMT();
void setColor(int red, int green, int blue);
void setPixel(uint16_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
void show();
void setBrightness(uint8_t brightness);

// Basis Farbmodi
void colorMode1();
void colorMode2();
void colorMode3();
void colorMode4();
void colorModeOff();

// Animationen
void rainbowMode();
void breathingMode();
void wavesMode();
void sparkleMode();

// Steuerungsfunktionen
void handleButtonPress();
void handleBrightnessControl();
void updateColor();
Color getHSVColor(uint16_t hue, uint8_t sat, uint8_t val);