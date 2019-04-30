#include <SPI.h>
#include <SD.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#define TFT_DC D4
#define TFT_CS D8
#define arduinoLblue 0x44f4
#define arduinoblue 0x030C
#define arduinoDblue 0x0249

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
File myFile;

char lect;
String number;
int N;
int counter = 1;

void setup() {
  
    Serial.begin(9600);
    SD.begin(D1);
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(arduinoLblue);
    tft.setTextColor(0x0000);
    tft.setTextSize(3);
    tft.setCursor(10, 5);
    tft.fillRect(0, 31, 320, 2, arduinoblue);
    tft.println("MENU RICETTE");
    while (1) {
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(5, 40);
    tft.setTextSize(2);
    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>lettura nomi ricette
       i nomi che corrispondono anche ai file txt delle ricette
       sono contenuti allinterno dell'array "ricette"
       NB ricette è un array (variabile) privato
    */
    myFile = SD.open("main.txt");
    while (1) {
      lect = myFile.read();
      if (lect == '\n') {
        break;
      }
      number += lect;
    }
    N = number.toInt();
    String ricette[N];
    for (int i = 0; i < N; i++) {
      char letter;
      while (1) {
        if (myFile.available()) {
          letter = myFile.read();
          if (letter != '\n') {
            ricette[i] += letter;
          }
          else {
            break;
          }
        }
        else {
          myFile.close();
          break;
        }
      }
      tft.print(ricette[i]);
      tft.setCursor(5, 40 + 18 * (i + 1));
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>selezione ricetta per via di seriale
     * ancora in stadio di sviluppo richiede una buona attenzione 
     * a come viene posizionata nel programma
     */
    while (!Serial.available()) {
    }
    switch (Serial.read()) {
      case 'D':
        if (counter < N) {
          counter++;
        }
        break;
      case 'U':
        if (counter > 1) {
          counter--;
        }
        break;
    }
    tft.fillRect(0,40,320,18*N,arduinoLblue);
    tft.fillRect(0, 40 + 18 * (counter - 1), 320, 14, arduinoDblue);
    for (int i=0; i<N; i++){
      tft.setCursor(5, 40 + 18 * (i));
      tft.print(ricette[i]);
      
    }
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  }

}


void loop() {


}
