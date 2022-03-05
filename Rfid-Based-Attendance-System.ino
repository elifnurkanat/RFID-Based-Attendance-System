 //460419063 Elif Nur KANAT

#include <LiquidCrystal_I2C_AvrI2C.h>
#include <SPI.h>
#include <MFRC522.h> 

#define SDA_PIN 10 
#define RST_PIN 9  
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2); 
MFRC522 mfrc522(SDA_PIN, RST_PIN); 

byte card_ID[4]; //I have defined the size (4 bytes) of the cards I use with an array

byte Student1[4]={0xE4,0xD5,0xD9,0x2A};
byte Student2[4]={0x69,0x18,0x8D,0x9D};
byte Student4[4]={0xE3,0x44,0x1C,0x07};
byte Student5[4]={0x33,0xD0,0x97,0x06};
byte Student6[4]={0x8A,0x7B,0xB1,0x1A};

int NumbCard[6];//I saved the total number of registered cards with a variable called NumCard.
int j=0;        

int const RedLed=6;
int const GreenLed=5;
int const Buzzer=8;

String Name;
long Number;


void setup() {
  lcd.begin(); 
  Serial.begin(9600); 
  SPI.begin();  
  mfrc522.PCD_Init(); 

 
  lcd.setCursor(3,0);
  lcd.print("KARTINIZI");
  lcd.setCursor(3,1); 
  lcd.print("OKUTUNUZ");
  
  Serial.println("LABEL,Tarih,Zaman,Ad SOYAD,Numara");// 4 columns have been created and named (Date, Time, Name-Surname, Number).


  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(Buzzer,OUTPUT);

   }


void SignedStudent(){
       lcd.setCursor(0,0);
       lcd.print("IYI DERSLER");
       lcd.setCursor(0,1);
       lcd.print(Name);
       digitalWrite(GreenLed,HIGH);
       delay(500);
}

void UnsignedStudent(){
          digitalWrite(GreenLed,LOW);
          digitalWrite(RedLed,HIGH);
          lcd.setCursor(0,0);
          lcd.print("DERSE KAYITLI");
          lcd.setCursor(0,1);
          lcd.print("DEGILSINIZ");
          digitalWrite(Buzzer,HIGH);
          delay(750);
          digitalWrite(Buzzer,LOW);
}
void loop() {
  //For new cards that will be read to the card reader:
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;
 }
 // When the card is detected:
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//When any card (defined or undefined) is read, it is selected for read-write purposes and passes to the following loop.
 }  
for (byte i = 0; i < mfrc522.uid.size; i++) {
       card_ID[i]=mfrc522.uid.uidByte[i]; //Converts the 4-byte UID to a string after the card is read.
       lcd.clear(); 

       // The if-else cycle where the id of the student list is compared with the id of the student being studied:
       
       if(card_ID[i]==Student1[i]){ 
       Name="Elif Nur KANAT";
       Number=460419063;
       SignedStudent();
       j=0;//This number will be sent to the NumCard[j] variable that holds the number of cards.
      }
      else if(card_ID[i]==Student2[i]){
        Name="Ecenaz ATBAS";
        Number=460419025;
        SignedStudent();
        j=1;
      }
      else if(card_ID[i]==Student4[i]){
        Name="Hasan KUSE";
        Number=460419029;
        SignedStudent();
        j=3;
      }
      else if(card_ID[i]==Student5[i]){
         Name="Ugur HATIM";
         Number=460419021;
         SignedStudent();
         j=4;
        
      }
      else if(card_ID[i]==Student6[i]){
         Name="Tugba MEMISOGLU";
         Number=460419033;
         SignedStudent();
         j=5;
        
      }
      else{
        UnsignedStudent();
        goto cont;
     }
     lcd.clear();
     lcd.setCursor(3,0);
     lcd.print("KARTINIZI");//This message will appear in the beginning (first line)
     lcd.setCursor(3,1); 
     lcd.print("OKUTUNUZ");//This message will appear in the beginning (second line)
     

}
      if(NumbCard[j] == 6){ //To find out if a card has been read before:
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("YOKLAMADA"); //first line of the LCD
        lcd.setCursor(3,1); 
        lcd.print("KAYITLISINIZ"); //second line of the LCD
        digitalWrite(RedLed,HIGH);
        digitalWrite(Buzzer,HIGH);
        delay(500);
        digitalWrite(Buzzer,LOW);
        digitalWrite(RedLed,LOW);
      }
      else{
      NumbCard[j] = 6;
      //Registration process to the excel and Seriport representation
      Serial.print("DATA,DATE,TIME," + Name);
      Serial.print(",");
      Serial.println(Number); //Sends the student number to the Excel list and seriport.
      digitalWrite(RedLed,LOW);
      digitalWrite(Buzzer,HIGH);
      delay(30);
      digitalWrite(Buzzer,LOW);
      }
      
cont:
lcd.clear();
digitalWrite(GreenLed,LOW);
digitalWrite(RedLed,LOW);
lcd.setCursor(3,0);
lcd.print("KARTINIZI");
lcd.setCursor(3,1); 
lcd.print("OKUTUNUZ");
delay(1000);

}
