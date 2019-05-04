#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#define TFT_DC D4
#define TFT_CS D8
#define select 0x8981
#define back 0x2144
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
File myFile;
File receipt;



String recipeSelect() {
  String main="main.txt";
  char lect;
  String number;
int N;
int counter = 0;
  tft.fillScreen(back);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.setCursor(10, 5);
  tft.fillRect(0, 31, 320, 2, select);
  tft.println("MENU RICETTE");
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(5, 40);
  tft.setTextSize(2);
  /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>lettura nomi ricette
     i nomi che corrispondono anche ai file txt delle ricette
     sono contenuti allinterno dell'array "ricette"
     NB ricette è un array (variabile) privato
  */
  myFile = SD.open(main);//apro il file main dalla sd
  while (1) {//leggo il numero di elementi (la prima riga del file contiene tale numero)
    lect = myFile.read();
    if (lect == '\n') {
      break;
    }
    number += lect;
  }
  N = number.toInt();
  String ricette[N];//creao l'array per i nomi delle ricette
  for (int i = 0; i < N; i++) {
    char letter;
    while (1) {//riempio l'array
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
    tft.print(ricette[i]);//stampo sul tft le ricette
    tft.setCursor(5, 40 + 18 * (i + 1));
  }
  if (N > 0) {
    tft.fillRect(0, 40 + 18 * (counter), 320, 14, select);//creo la selezione sul primo elemento
    tft.setCursor(5, 40 + 18 * (counter));
    tft.println(ricette[counter]);
  }
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  /*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>selezione ricetta per via di seriale
     ancora in stadio di sviluppo richiede una buona attenzione
     a come viene posizionata nel programma
  */
  while (1) {
    while (!Serial.available()) {//attendo input
    }
    switch (Serial.read()) {//convalido l'input
      case 'D':
        if (counter < N - 1) {
          counter++;
        }
        break;
      case 'U':
        if (counter > 0) {
          counter--;
        }
        break;
      case'E':
        myFile.close();
        String selected=ricette[counter];
        return (selected);
    }
    //cancello la selezione sopra
    if(counter>0){
    tft.fillRect(0, 40 + 18 * (counter - 1), 320, 14, back);
    tft.setCursor(5, 40 + 18 * (counter - 1));
    tft.println(ricette[counter - 1]);
    }
    //cancello la selezione sotto
    if(counter<N-1){
    tft.fillRect(0, 40 + 18 * (counter + 1), 320, 14, back);
    tft.setCursor(5, 40 + 18 * (counter + 1));
    tft.println(ricette[counter + 1]);
    }
    //scrivo la selezione selezionata
    tft.fillRect(0, 40 + 18 * (counter), 320, 14, select);
    tft.setCursor(5, 40 + 18 * (counter));
    tft.println(ricette[counter]);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  }
}
void ingredientList(String receiptName){
  char lect1;
  String number1;
  int N1;
  int counter = 0;
  tft.fillScreen(back);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.setCursor(10, 5);
  tft.fillRect(0, 31, 320, 2, select);
  tft.println(receiptName);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(5, 40);
  tft.setTextSize(2);
  myFile.close();
  receipt = SD.open(receiptName);//apro il file main dalla sd
  if(receipt) Serial.print("apre");
  while (1) {//leggo il numero di elementi (la prima riga del file contiene tale numero)
    lect1 = receipt.read();
    Serial.println(lect1);
    if (lect1 == '\n') {
      break;
    }
    number1 += lect1;
    Serial.println(number1);
  }
  N1 = number1.toInt();
  String ingredienti[N1];//creao l'array per i nomi delle ricette
  for (int i = 0; i < N1; i++) {
    char letter1;
    while (1) {//riempio l'array
      if (receipt.available()) {
        letter1 = receipt.read();
        if (letter1 != '\n') {
          ingredienti[i] += letter1;
        }
        else {
          break;
        }
      }
      else {
        receipt.close();
        break;
      }
    }
    tft.print(ingredienti[i]);//stampo sul tft gli ingredienti
    tft.setCursor(5, 40 + 18 * (i + 1));
  }
}
