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
  String main = "main.txt";
  char lect;
  String number;
  int N;
  int counter = 0;
  tft.fillScreen(back);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.setCursor(10, 5);
  tft.fillRect(0, 0, 320, 33, select);
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
    if (lect == ';') {
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
        if (letter != ';') {
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
        String selected = ricette[counter];
        return (selected);
    }
    //cancello la selezione sopra
    if (counter > 0) {
      tft.fillRect(0, 40 + 18 * (counter - 1), 320, 14, back);
      tft.setCursor(5, 40 + 18 * (counter - 1));
      tft.println(ricette[counter - 1]);
    }
    //cancello la selezione sotto
    if (counter < N - 1) {
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
bool ingredientList(String receiptName) {
  char lect1;
  String number1;
  int N1;
  int counter = 0;
  tft.fillScreen(back);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.setCursor(10, 5);
  tft.fillRect(0, 0, 320, 33, select);
  tft.println(receiptName);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(5, 40);
  tft.setTextSize(2);
  myFile.close();
  //apro il file main dalla sd
  receipt = SD.open(receiptName + ".txt");
  if (receipt) Serial.print("apre");
  //leggo il numero di elementi (la prima riga del file contiene tale numero)
  while (1) {
    lect1 = receipt.read();
    Serial.println(lect1);
    if (lect1 == ';') {
      break;
    }
    number1 += lect1;
    Serial.println(number1);
  }
  N1 = number1.toInt();
  //creao l'array per i nomi delle ricette
  String ingredienti[N1];
  for (int i = 0; i < N1; i++) {
    char letter1;
    while (1) {//riempio l'array
      if (receipt.available()) {
        letter1 = receipt.read();
        if (letter1 != ';') {
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
    //stampo sul tft gli ingredienti
    tft.print(ingredienti[i]);
    tft.setCursor(5, 40 + 18 * (i + 1));
  }
  //conferma della ricetta
  while (1) {
    while (!Serial.available()) {
      //aspettiamo
    }
    if (Serial.read() == 'E') {
      //va avanti
      return (true);
    }
    if (Serial.read() == 'X') {
      //torna indietro
      return (false);
      break;
    }
  }
}

int initRecipe(String receiptName) {
  int counter = 0;

  tft.fillScreen(back);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.setCursor(10, 5);
  tft.fillRect(0, 0, 320, 33, select);
  tft.println(receiptName);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(5, 40);
  tft.setTextSize(2);
  tft.print("Selezionare la");
  tft.setCursor(5, 56);
  tft.print("quantita desiderata:");
  tft.setTextSize(5);
  tft.setCursor(10, 112);
  tft.print(counter);
  tft.print("g");
  while (1) {
    if (Serial.available()) {
      switch (Serial.read()) {
        case 'U':
          if ((counter >= 2000) && (counter < 5000))counter += 500;
          if ((counter >= 500) && (counter < 2000))counter += 100;
          if (counter < 500)counter += 20;
          break;
        case 'D':
          if ((counter <= 500 && counter > 0))counter -= 20;
          if ((counter > 500) && (counter <= 2000))counter -= 100;
          if (counter > 2000)counter -= 500;
          break;
        case 'E':
          return (counter);
          break;
        case 'X':
          return (0);
      }
      tft.fillRect(10, 112, 180, 40, back);
      tft.setCursor(10, 112);
      tft.print(counter);
      tft.print("g");
    }
  }
}
void cook(String receiptName, int quantity) {

  char lect;
  String number;
  int N;
  float sum = 0;

  tft.fillScreen(back);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.setCursor(10, 5);
  tft.fillRect(0, 0, 320, 33, select);
  tft.println(receiptName);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(5, 40);
  tft.setTextSize(3);

  //apro la ricetta
  receipt = SD.open(receiptName + ".txt");
  if (receipt) Serial.print("apre");
  //leggo il numero di elementi (la prima riga del file contiene tale numero)
  while (1) {
    lect = receipt.read();
    Serial.println(lect);
    if (lect == ';') {
      break;
    }
    number += lect;
    Serial.println(number);
  }
  N = number.toInt();
  //creao l'array per i nomi delle ricette
  String ingredienti[N];
  for (int i = 0; i < N; i++) {
    char letter;
    //riempio l'array
    while (1) {
      if (receipt.available()) {
        letter = receipt.read();
        if (letter != ';') {
          ingredienti[i] += letter;
        }
        else {
          break;
        }
      }
      else {
        break;
      }
    }
  }
  //leggo le quantità
  String quantitiesS[N];
  float quantities[N];
  for (int i = 0; i < N; i++) {
    char letter;
    //riempio l'array
    while (1) {
      if (receipt.available()) {
        letter = receipt.read();
        if (letter != ';') {
          quantitiesS[i] += letter;
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
  }
  //trasformo le stringhe ascii delle quantità in numeri int e ne calcolo la somma
  for (int i = 0; i < N; i++) {
    quantities[i] = quantitiesS[i].toInt();
    sum += quantities[i];
  }
  for (int i = 0; i < N; i++) {
    int total = int(quantities[i] * (quantity / sum));
    tft.print(ingredienti[i]);
    tft.print(": ");
    tft.print(total);
    tft.print("g");
    while (1) {
      if (Serial.available()) {
        if (Serial.read() == 'E') {
          break;
        }
      }
      /*da testare appena HX711 sostituitivo arriva
       int peso=scale.get_units(5);
       tft.fillRect(0,180,int(peso*320/total),60,select);
       tft.fillRect(int(peso*320/total),180,320-int(peso*320/total),60,back);
       tft.setTextSize(5);
       tft.setCursor(10,190);
       tft.print(peso);
       tft.print("g");
       int pos;
       //posizionamento della scritta del peso
       if (value < 10) pos = 60;
       else {
          if (value < 100) pos = 90;
          else {
           if (value < 1000) pos = 120;
           else {
            if (value < 10000) pos = 150;
            else {
              pos = 180;
          }
        }
      }
    }
    if (value != oldValue) {
      tft.setCursor(160 - pos / 2, 190);
      tft.fillRect(0, 200, 320, 240, select);
      tft.print(value);
      oldValue = value;
      tft.print("g");
    }
       if (peso==total) break;
       */
    }
    tft.fillRect(0, 40, 320, 24, back);
    tft.setCursor(5, 40);
  }


}
void main() {
  int oldValue = 99999999999;
  tft.fillScreen(back);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.setCursor(10, 5);
  tft.fillRect(0, 0, 320, 33, select);
  tft.println("TECHNE");
  tft.setTextSize(4);
  tft.setTextColor(0xffff);
  //init bilancia
  scale.set_scale(400.f);
  scale.tare();
  while (1) {
    if(Serial.available()){
      if(Serial.read()=='E') break;
      if(Serial.read()=='D') scale.tare();
    }
    //lettura peso
    int value = scale.get_units(5);
    int pos;
    //posizionamento della scritta del peso
    if (value < 10) pos = 48;
    else {
      if (value < 100) pos = 72;
      else {
        if (value < 1000) pos = 96;
        else {
          if (value < 10000) pos = 120;
          else {
            pos = 124;
          }
        }
      }
    }
    if (value != oldValue) {
      tft.setCursor(160 - pos / 2, 204);
      tft.fillRect(0, 200, 320, 240, select);
      tft.print(value);
      oldValue = value;
      tft.print("g");
    }
  }
}
