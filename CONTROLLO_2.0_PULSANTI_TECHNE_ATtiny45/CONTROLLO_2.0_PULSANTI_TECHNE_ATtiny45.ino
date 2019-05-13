/****************************************************/
/**************** CONTROLLO PULSANTI ****************/
/****************************************************/

#define button_U  0
#define button_E  1
#define button_D  2
#define rx 3
#define tx 4

#include <SoftwareSerial.h>
SoftwareSerial myserial(rx, tx);
/*****************VARIABILI*****************/

int time1 = 1200;      //tempo cambio velocità pulsanti Up e Down
int speed1 = 600;      //velocità 1
int speed2 = 200;     // velocità 2
int millisStore;
int millisHeld;
int DIOCANE = 0;

void setup()
{
  pinMode(button_U, INPUT);
  pinMode(button_E, INPUT);
  pinMode(button_D, INPUT);
  myserial.begin(9600);
}

void loop()
{


  /*****************RESET CONTATORE*****************/

  while (digitalRead(button_U) == LOW && digitalRead(button_E) == LOW && digitalRead(button_D) == LOW)
  {
    millisStore = millis();
    millisHeld = 0;
    DIOCANE = 1;
  }

  /*****************PULSANTE UP*****************/



  if (digitalRead(button_U) == HIGH)
  {

    while (digitalRead(button_U) == HIGH)
    {
      millisHeld = millis() - millisStore;

      if (millisHeld > 600 && millisHeld <= time1)
      {
        myserial.write('U');
        delay(speed1);
      }

      if (millisHeld > time1)
      {
        myserial.write('U');
        delay(speed2);
      }

    }
    myserial.write('U');
  }


  /*****************PULSANTE ENTER*****************/


  if (digitalRead(button_E) == HIGH && DIOCANE == 1)
  {

    while (digitalRead(button_E) == HIGH)
    {
      millisHeld = millis() - millisStore;
      if (millisHeld >= 1000 && DIOCANE == 1)
      {
        myserial.write('X');
        DIOCANE = 0;
        break;
      }
    }
    if (millisHeld < 1000)
    {
      myserial.write('E');
    }
  }

  /*****************PULSANTE DOWN*****************/

  if (digitalRead(button_D) == HIGH)
  {

    while (digitalRead(button_D) == HIGH)
    {
      millisHeld = millis() - millisStore;

      if (millisHeld > 600 && millisHeld <= time1)
      {
        myserial.write('D');
        delay(speed1);
      }

      if (millisHeld > time1)
      {
        myserial.write('D');
        delay(speed2);
      }
    }


    myserial.write('D');

  }
}
