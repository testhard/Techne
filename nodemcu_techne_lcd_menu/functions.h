#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "HX711.h"
#define TFT_DC D4
#define TFT_CS D8
#define select 0x8981
#define back 0x2144
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
HX711 scale(D3, D2);
File myFile;
File receipt;



String recipeSelect() {
  int page = 0;
  String main = "main.lt";
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
  String Ricette[N];
  for (int i = 0; i < N; i++) {
    char letter;
    while (1) {//riempio l'array
      if (myFile.available()) {
        letter = myFile.read();
        if (letter != ';') {
          ricette[i] += letter;
          Ricette[i] += letter;
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
    if (ricette[i].length() > 25) ricette[i].remove(25, ricette[i].length() - 25);
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
      case'X':
        myFile.close();
        return ("main");
      case'E':
        myFile.close();
        String selected = Ricette[counter];
        return (selected);
        break;

    }
    if (N > 10) {
      if (counter - 10 * page > 10) {
        page++;
        tft.setCursor(5, 40);
        tft.fillRect(0, 40, 320, 240, back);
        for (int i = page * 10; i < N; i++) {
          tft.print(ricette[i]);
          tft.setCursor(5, 40 + 18 * (i - 9));
        }
      }
    }
    if (counter - 10 * page < 0) {
      page--;
      tft.setCursor(5, 40);
      tft.fillRect(0, 40, 320, 240, back);
      for (int i = page * 10; i < N; i++) {
        tft.print(ricette[i]);
        tft.setCursor(5, 40 + 18 * (i + 1 - 10 * page));
      }
    }
    //cancello la selezione sopra
    if (counter - 10 * page > 0) {
      tft.fillRect(0, 40 + 18 * (counter - 10 * page - 1), 320, 14, back);
      tft.setCursor(5, 40 + 18 * (counter - 10 * page - 1));
      tft.println(ricette[counter - 1]);
    }
    //cancello la selezione sotto
    if (counter < N - 1) {
      tft.fillRect(0, 40 + 18 * (counter - 10 * page + 1), 320, 14, back);
      tft.setCursor(5, 40 + 18 * (counter - 10 * page + 1));
      tft.println(ricette[counter + 1]);
    }
    //scrivo la selezione selezionata
    tft.fillRect(0, 40 + 18 * (counter - 10 * page), 320, 14, select);
    tft.setCursor(5, 40 + 18 * (counter - 10 * page));
    tft.println(ricette[counter]);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  }
}

bool ingredientList(String receiptName) {
  char lect1;
  String number1;
  int N1;
  int counter = 0;
  int page=0;  
  
  //apro il file main dalla sd
  receipt = SD.open(receiptName + ".txt");
  
  tft.fillScreen(back);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.setCursor(10, 5);
  tft.fillRect(0, 0, 320, 33, select);
  if (receiptName.length() > 17) receiptName.remove(17, receiptName.length() - 17);
  tft.println(receiptName);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(5, 40);
  tft.setTextSize(2);
  myFile.close();

  //leggo il numero di elementi (la prima riga del file contiene tale numero)
  while (1) {
    lect1 = receipt.read();
    if (lect1 == ';') {
      break;
    }
    number1 += lect1;
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
    if (ingredienti[i].length() > 25) ingredienti[i].remove(25, ingredienti[i].length() - 25);
    tft.print(ingredienti[i]);
    tft.setCursor(5, 40 + 18 * (i + 1));
  }
  //conferma della ricetta
  while (1) {
    while (!Serial.available()) {
      //aspettiamo
    }
    char var = Serial.read();
    if (var == 'E') {
      //va avanti
      return (true);
    }
    if (var == 'X') {
      //torna indietro
      return (false);
      break;
    }
    if ((var == 'D') && (page < int(N1 / 12))) page++;
    if ((var == 'U') && (page >0)) page--;
    tft.fillRect(0, 40, 320, 240, back);
    tft.setCursor(5, 40);
    for (int i = 11 * page; i < N1 ; i++) {
      tft.print(ingredienti[i]);
      tft.setCursor(5, 40 + 18 * (i + 1-11*page));
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
  if (receiptName.length() > 17) receiptName.remove(17, receiptName.length() - 17);
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

bool initQuantity(int quantity, String receiptName) {

  char lect1;
  String number1;
  int N1;
  int counter = 0;
  int sum = 0;
  int page = 0;
  
  //apro il file main dalla sd
  receipt = SD.open(receiptName + ".txt");
  
  tft.fillScreen(back);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.setCursor(10, 5);
  tft.fillRect(0, 0, 320, 33, select);
  if (receiptName.length() > 17) receiptName.remove(17, receiptName.length() - 17);
  tft.println(receiptName);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(5, 40);
  tft.setTextSize(2);
  tft.print("per ");
  tft.print(quantity);
  tft.print("g di");
  tft.setCursor(5, 57);
  tft.print(receiptName + ":");
  
  //leggo il numero di elementi (la prima riga del file contiene tale numero)
  while (1) {
    lect1 = receipt.read();
    if (lect1 == ';') {
      break;
    }
    number1 += lect1;
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
    if (ingredienti[i].length() > 18) ingredienti[i].remove(18, ingredienti[i].length() - 18);
  }
  //lettura quantità
  String quantitiesS[N1];
  float quantities[N1];
  for (int i = 0; i < N1; i++) {
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
  for (int i = 0; i < N1; i++) {
    quantities[i] = quantitiesS[i].toFloat();
  }
  //trasformo le quantità teoriche in reali
  String Total[N1];
  for (int i = 0; i < N1; i++) {
    float total = quantities[i] * quantity;
    Total[i] = String(total,0);
  }
  tft.setCursor(5, 56 + 18);
  for (int i = 0; i < N1; i++) {
    tft.print(ingredienti[i]);
    tft.print(":");
    tft.setCursor(5, 56 + 18 * (i + 2));
  }
  tft.setCursor(245, 56 + 18);
  for (int i = 0; i < N1; i++) {
    tft.print(Total[i]);
    tft.print("g");
    tft.setCursor(245, 56 + 18 * (i + 2));
  }
  while (1) {
    while (!Serial.available()) {
    }
    char var = Serial.read();
    if (var == 'E') return (true);
    if (var == 'X') return (false);
    if ((var == 'D') && (page < int(N1 / 10))) page++;
    if ((var == 'U') && (page >0)) page--;
    tft.fillRect(0, 56 + 18, 320, 240, back);
    tft.setCursor(5, 56 + 18);
    for (int i = 9 * page; i < N1 ; i++) {
      tft.print(ingredienti[i]);
      tft.print(":");
      tft.setCursor(5, 56 + 18 * (i + 2-9*page));
    }
    tft.setCursor(245, 56 + 18);
    for (int i = 9 * page; i < N1 ; i++) {
      tft.print(Total[i]);
      tft.print("g");
      tft.setCursor(245, 56 + 18 * (i + 2-9*page));
    }
  }
}


void cook(String receiptName, int quantity) {

  char lect;
  String number;
  int N;
  float sum = 0;
  int value = 0;
  int oldValue = 99999999;
  
  //apro la ricetta
  receipt = SD.open(receiptName + ".txt");
  
  tft.fillScreen(back);
  tft.setTextColor(0x0000);
  tft.setTextSize(3);
  tft.setCursor(10, 5);
  tft.fillRect(0, 0, 320, 33, select);
  if (receiptName.length() > 18) receiptName.remove(18, receiptName.length() - 18);
  tft.println(receiptName);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(5, 40);
  tft.setTextSize(2);

  //leggo il numero di elementi (la prima riga del file contiene tale numero)
  while (1) {
    lect = receipt.read();
    if (lect == ';') {
      break;
    }
    number += lect;
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
    if (ingredienti[i].length() > 24) ingredienti[i].remove(24, ingredienti[i].length() - 24);
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
    quantities[i] = quantitiesS[i].toFloat();
  }
  for (int i = 0; i < N; i++) {
    scale.tare();
    float total = quantities[i] * quantity;
    String Total = String(total,0);
    tft.setTextSize(2);
    tft.print(ingredienti[i]);
    tft.print(": ");
    tft.setCursor(5, 57);
    tft.print(Total);
    tft.print("g");
    while (1) {
      if (Serial.available()) {
        if (Serial.read() == 'E') {
          break;
        }
      }


      //da testare appena HX711 sostituitivo arriva
      int peso = scale.get_units(5);

      int pos;
      //posizionamento della scritta del peso
      if (peso < 10) pos = 60;
      else {
        if (peso < 100) pos = 90;
        else {
          if (peso < 1000) pos = 120;
          else {
            if (peso < 10000) pos = 150;
            else {
              pos = 180;
            }
          }
        }
      }
      if (peso != oldValue) {
        tft.fillRect(0, 180, int(peso * 320 / total), 60, select);
        tft.fillRect(int(peso * 320 / total), 180, 320 - int(peso * 320 / total), 60, back);
        tft.setTextSize(5);
        tft.setCursor(160 - pos / 2, 190);
        tft.print(peso);
        oldValue = peso;
        tft.print("g");
      }
      if (((peso > total - total * 0.05) && (peso < total + total * 0.05 )) || ((peso > total - 2) && (peso < total + 2)&&(peso>5)) ) break;



    }
    tft.fillRect(0, 40, 320, 40, back);
    tft.setCursor(5, 40);
  }
  tft.fillRect(0,0,320,240, select);
  tft.setTextSize(6);
  tft.setCursor(88,99);
  tft.print("FINE");
  delay(2000);

}
void Main() {
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
    if (Serial.available()) {
      char var = Serial.read();
      if (var == 'E') break;
      if (var == 'D') scale.tare();
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
