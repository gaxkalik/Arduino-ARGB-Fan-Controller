#include <FastLED.h>

#define LED_PIN     6        // Data pin for ARGB on arduino (you can change for any digital pin)
#define NUM_LEDS    16       // Number of LEDs (resolution of effects)
#define BRIGHTNESS  100      // Any value form 0 to 255
#define LED_TYPE    WS2812   // Usually this stays the fame for all ARGB fans
#define COLOR_ORDER GRB      // If your colors are incorrect you can change to RGB ot BRG 
#define BUTTON_PIN  2        // Button pin to GND when pressed (you can change to any digital bun on your arduino)

CRGB leds[NUM_LEDS];

int mode = 0;
const int numModes = 5;      // Total number of modes (OFF + colors + effects)
unsigned long lastPress = 0;

void setup() 
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button active LOW (ON PRESS)
}

void loop() 
{
  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastPress > 300) 
  {
    mode++;
    if (mode >= numModes) 
      mode = 0;
      
    lastPress = millis();
    FastLED.clear(); 
    FastLED.show();
  }

  switch (mode) 
  {
    case 0:                     // OFF
      offMode(); 
      break;                     
    case 1:                    // Solid Red
      solidColor(CRGB::Red); 
      break;        
    case 2:                    // Solid Green
      solidColor(CRGB::Green);
      break;
    case 3:                   // Solid Blue
      solidColor(CRGB::Blue); 
      break;       
    case 4:                   // Rainbow
      rainbowCycle(20);  
      break;             
     }
     //you can add more modes (If you add them,also change numModes)
}

// Modes
void offMode() 
{
  FastLED.clear();
  FastLED.show();
}

void solidColor(CRGB color) 
{
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(50);
}

void rainbowCycle(int wait)       // wait is the speed
{
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) 
  {
    leds[i] = CHSV((hue + (i * 256 / NUM_LEDS)) & 255, 255, 255);
  }
  
  FastLED.show();
  hue++;
  delay(wait);
}



