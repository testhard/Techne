/**********************************************************************************
 * PROJECT TECHNE THERMAL RADIO MODULE
 * 5EI
 * Testa Mattia e Gentile Michael
 * Created:19/01/15
 * Version:0
 * Functional:NO
 * LOG:
 *    -19/01/15:
 *        -programma creato
 *        -funzioni readTemp e readBatt scritte
 *        -steso un primo programma ancora da provare
 *        -funzione RFsend vuota
 *        -impostato alcuni define
 *        -calcolato con excell tempResistor a 1M
 *    -19/01/20:
 *        -definiti pin per batt e therm
 *        -corretto readTemp()
 *        -corretto readBatt()
 *    -19/01/21:
 *        -aggiustato RFsend
 *        -da sistemare readTemp()
 *        -da sistemare il programma per inviare i byte via radio
 *    -19/01/28:
 *        -sistemato sleepmode
 *        -sitemato invio codici RF
 *    -19/02/06:
 *        -Vin 2.5v
 *        -modificato RFsend
 *        -tolto Serial
 *        -primo test 100% funzionante
 *********************************************************************************/

#include <VirtualWire.h>
#include <LowPower.h>

#define RF 13
#define batt A1                                           //pin sonda batteria
#define therm A0                                          //pin sonda termistore
#define tempResistor 1000000.0                             //in Ohms     resistenza in serie al thermistore 1M dovrebbe andare bene per un range da -50 a +50 °C
#define Rtherm 100000.0                                   //in Ohms     resistenza del thermistore a 25°C
#define B 3950.0                                          //valore B (o beta) del termistore NTC
#define Vin 2.5                                           //in Volts    valore di alimentazione del MCU, usato per stabilire le tensioni lette dall'ADC
#define Vmin 5.5                                           //in Volts    valore minimo della batteria, una volta raggiunto viene mandato il segnale di batteria scarica

char ID[4]={'0','0','0','1'};

void RFsend(byte *mex, int lenght){                                //funzione per inviare stringhe col modulo radio
  digitalWrite(RF, HIGH);
  vw_send((byte *)mex, lenght);
  vw_wait_tx(); 
  digitalWrite(RF,LOW);
}

float readTemp(int therm){                                  //funzione che restituisce la temperatura leggendo la resistenza del termistore attraverso la caduta di tensione di una resistenza in serie al termistore
  float Vr=analogRead(therm)*Vin/1024.0;                 //conversione valori ADC in tensione
  float Rt=tempResistor/Vr*Vin-tempResistor;           //ricavo la resistenza del termistore con un partitore di tensione inverso
  float temp=1.0/((log(Rt/Rtherm)/B)+1.0/298.15)-275.15;    //ricavo la temperatura in °C con l'equazione utilizzante il parametro B, derivata dall'equazione di Steinhart-Hart
  //Serial.println(temp);
  if(temp<0){
    return(temp+255);
  }
  else{
    return(temp);                                         //ritorno la temperatura appena ricavata
  }
  

}

bool readBatt(int battPin){                             //funzione per la lettura della tensione della batteria, restituisce 1 se è scarica (minore o uguale alla tensione minima)
  float V=(analogRead(battPin)*Vin/1024)*5.7;                //questa funzione funziona solo se per leggere la tensione usiamo un partitore di 2 resistenze, di cui una è 100k e l'altra 470k (se fossero uguali sarebbe 
  if(V<=Vmin){                                          //impossibile leggere la batteria carica sicchè 4,2V/2=2,1V e l'alimentazione dovrebbe essere intorno ai 2V
    return(1);                                          //la lettura deve avvenire sulla resistenza più piccola, che dunque misurerà 1/3 della tensione (4,2V/3=1,4V)
  }
  else{
    return(0);
  }
}

void setup() {
  //Serial.begin(9600);
  vw_set_tx_pin(12);
  vw_setup(2000); 
  pinMode(RF,OUTPUT);
  pinMode(batt,INPUT);
  pinMode(therm,INPUT);
  byte sign[7];
  sign[0]='a';
  sign[1]='c';
  sign[2]='c';
  sign[3]=ID[0];
  sign[4]=ID[1];
  sign[5]=ID[2];
  sign[6]=ID[3];
  RFsend(sign,7);                                          //quando viene resettato il modulo (si utilizza un pulsantino) viene inviato il segale per l'accoppiamento con l'ID

}

void loop() {
  float temp=readTemp(therm);                                 //legge la temperatura
  //char batteryStatus=readBatt(batt);                    //controlla lo stato della batteria
  //char Mex="0001"+char(temp)+batteryStatus;           //compone la stringa di codice da inviare con la radio
  byte TxBuffer[6];
  TxBuffer[0]=byte(ID[0]);
  TxBuffer[1]=byte(ID[1]);
  TxBuffer[2]=byte(ID[2]);
  TxBuffer[3]=byte(ID[3]);
  TxBuffer[4]=byte(temp);
  TxBuffer[5]=readBatt(batt);                          //inserisco i dati in un array di byte per il moulo RF
  /*
  Serial.println(TxBuffer[0]);
  Serial.println(TxBuffer[1]);
  Serial.println(TxBuffer[2]);
  Serial.println(TxBuffer[3]);
  Serial.println(TxBuffer[4]);
  Serial.println(TxBuffer[5]);
  */
  RFsend(TxBuffer,6);                                      //invia la stringa di codice
  //delay(100);                                            //serve solo per il serial print
  for(int x=0;x<6;x++){                                 //questo annestamento di for serve per mandare in sleep l'MCU per 1 ora, controllando la temperatura ogni 10 minuti, uscendo e rientrando in sleep
    for(int i=0; i<75;i++){                             //ogni 8 secondi perchè è il massimo che può stare in sleep per poi risvegliarsi a tempo con l'RTC interno
      LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
    }
    if((readTemp(therm)>temp+1)||(readTemp(therm)<temp-1)){   //se la temperatura (controllata ogni 10 min) è aumentata o diminuita di più di 1°C manda l'aggiornamento via radio uscendo dal loog dell'ora di sleep
      break;
    }
  }
}
