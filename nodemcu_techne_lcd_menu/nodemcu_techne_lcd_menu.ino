#include <SPI.h>
#include <SD.h>
#include "functions.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "HX711.h"
#define TFT_DC D4
#define TFT_CS D8
#define select 0x8981
#define back 0x2144


void setup() {
  Serial.begin(9600);
  SD.begin(D1);
  tft.begin();
  tft.setRotation(1);
}


void loop() {
  while(1){
  Main();
  String selected = recipeSelect();
  if(selected=="main") break;
  if (ingredientList(selected)) {
    int quantity = initRecipe(selected);
    if (quantity > 0) {
      if(initQuantity(quantity, selected)){
         cook(selected, quantity);
      }
    }
  }
  }
}
