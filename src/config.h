// config.h
#pragma once
#include <Arduino.h>
#include <driver/rmt.h>

// Pin Definitions
#define RED_PIN 15
#define GREEN_PIN 13
#define BLUE_PIN 12
#define BUTTON_PIN 4
#define LED_PIN 14
#define BRIGHTNESS_PIN 5

// LED Configuration
#define LED_COUNT 120
#define RMT_CHANNEL RMT_CHANNEL_0
#define WS2812_T1H 64
#define WS2812_T1L 36
#define WS2812_T0H 32
#define WS2812_T0L 68

// Button Configuration
const unsigned long LONG_PRESS_TIME = 1000;
const unsigned long DOUBLE_CLICK_TIME = 300;
const int NUM_STATES = 8;

// Animation Configuration
const int ANIMATION_SPEED = 50;
const int RAINBOW_STEP = 5;
const int BREATH_SPEED = 20;
const int WAVE_LENGTH = 20;

// Mathematische Konstanten
#ifndef PI
#define PI 3.14159265359
#endif

// Brightness levels (0-255)
const uint8_t BRIGHTNESS_LEVELS[] = {25, 128, 255, 64};
const int NUM_BRIGHTNESS_LEVELS = sizeof(BRIGHTNESS_LEVELS) / sizeof(BRIGHTNESS_LEVELS[0]);