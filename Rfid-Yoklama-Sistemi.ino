 //460419063 Elif Nur KANAT Elektronik Haberleşme Teknolojisi(İ.Ö) Bitirme Projesi

//Gerekli kütüphaneleri tanımladım.
#include <LiquidCrystal_I2C_AvrI2C.h>
#include <SPI.h>
#include <MFRC522.h> 

#define SDA_PIN 10 //SDA pinini Arduino'da 10.pine atadım.
#define RST_PIN 9  //RST pinini Arduino'da 9.pine atadım.
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2); //Kullandığım LCD Ekranın modelini(0x27) ve kaça kaçlık(16x2) olduğunu tanımladım.
MFRC522 mfrc522(SDA_PIN, RST_PIN); // Kart okuyucu için Arduino üzerinden SDA ve RST pinlerini tanımladım.

byte card_ID[4]; //Kullandığım kartların boyutunu (4 byte) bir dizi ile tanımladım, card_ID değişkeni okutulan kartın IDsini tutmak için var.
//Kullanacağım kartların IDlerini sisteme kaydettim.
byte Student1[4]={0xE4,0xD5,0xD9,0x2A};
byte Student2[4]={0x69,0x18,0x8D,0x9D};
byte Student4[4]={0xE3,0x44,0x1C,0x07};
byte Student5[4]={0x33,0xD0,0x97,0x06};
byte Student6[4]={0x8A,0x7B,0xB1,0x1A};

int NumbCard[6];//Toplam kayıtlı kart sayısını NumCard isimli bir değişken ile kaydettim.
int j=0;        

//Ledlerin ve Buzzerın Arduino üzerinde gideceği pinleri tanımladım. 
int const RedLed=6;
int const GreenLed=5;
int const Buzzer=8;

String Name;//öğrenci adını tutacak bir değişken tanımladım.
long Number;//öğrenci numarasını tutacak bir değişken tanımladım.


void setup() {
  lcd.begin(); //LCD ekran başlatıldı.
  Serial.begin(9600); //Seri iletişim 9600 bit ile başlatıldı.
  SPI.begin();  // Haberleşme başlatıldı.
  mfrc522.PCD_Init(); // Kart okuyucu başlatıldı.

  //Ana mesaj ekrana gönderildi
  lcd.setCursor(3,0);
  lcd.print("KARTINIZI");
  lcd.setCursor(3,1); 
  lcd.print("OKUTUNUZ");
  
  Serial.println("LABEL,Tarih,Zaman,Ad SOYAD,Numara");// 4 sütun oluşturuldu ve isimlendirildi.

  //Ledler ve buzzer çıkış olarak tanımlandı.
  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(Buzzer,OUTPUT);

   }

//KayitliOgrenci adında bir void fonsiyon oluşturuldu.
void KayitliOgrenci(){
       lcd.setCursor(0,0);
       lcd.print("IYI DERSLER");
       lcd.setCursor(0,1);
       lcd.print(Name);
       digitalWrite(GreenLed,HIGH);
       delay(500);
}

//KayitsizOgrenci adında bir void fonsiyon oluşturuldu.
void KayitsizOgrenci(){
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
  //Kart okuyucuya okutulacak yeni kartlar için:
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//Bir kart okutuluncaya dek bu döngü döner.
 }
 // Kart tespit edildiğinde:
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//Herhangi bir kart (tanımlı ya da tanımsız) okutulduğunda okuma-yazma amacıyla seçilir ve aşağıdaki döngüye geçer.
 }  
for (byte i = 0; i < mfrc522.uid.size; i++) {
       card_ID[i]=mfrc522.uid.uidByte[i]; //Kart okunduktan sonra 4 baytlık UID'yi bir dizeye dönüştürür.
       lcd.clear(); //LCD ekranı temizler.

       // Okutulan ID ile Öğrenci listesindeki IDlerin karşılaştırıldığı if-else döngüsü:
       //Öğrenci bilgilerinin sisteme işlenmesi
       if(card_ID[i]==Student1[i]){ 
       Name="Elif Nur KANAT";
       Number=460419063;
       KayitliOgrenci();
       j=0;//Kart sayısını tutan NumCard[j] değişkenine gönderilecek ilk sayı.
      }
      else if(card_ID[i]==Student2[i]){
        Name="Ecenaz ATBAS";
        Number=460419025;
        KayitliOgrenci();
        j=1;
      }
      else if(card_ID[i]==Student4[i]){
        Name="Hasan KUSE";
        Number=460419029;
        KayitliOgrenci();
        j=3;
      }
      else if(card_ID[i]==Student5[i]){
         Name="Ugur HATIM";
         Number=460419021;
         KayitliOgrenci();
         j=4;
        
      }
      else if(card_ID[i]==Student6[i]){
         Name="Tugba MEMISOGLU";
         Number=460419033;
         KayitliOgrenci();
         j=5;
        
      }
      else{// yukarıda bilgileri verilen öğrenciler dışında giriş yapılmaya çalışılırsa KayitsizOgrenci() fonksiyonu aktif hale gelir.
        KayitsizOgrenci();
        goto cont;//direkt olarak cont: komutuna gider.
     }
     lcd.clear();
     lcd.setCursor(3,0);
     lcd.print("KARTINIZI");// Sistem başlatıldığında görünecek mesaj
     lcd.setCursor(3,1); 
     lcd.print("OKUTUNUZ");
     

}
      if(NumbCard[j] == 6){ //Bir kartın daha önce okutulup okutulmadığını anlamak için:
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("YOKLAMADA");
        lcd.setCursor(3,1); 
        lcd.print("KAYITLISINIZ");
        digitalWrite(RedLed,HIGH);
        digitalWrite(Buzzer,HIGH);
        delay(500);
        digitalWrite(Buzzer,LOW);
        digitalWrite(RedLed,LOW);
      }
      else{
      NumbCard[j] = 6;
      //Excele kayıt işlemi ve Seriportta gösterimi
      Serial.print("DATA,DATE,TIME," + Name);//Öğrenci adını, tarih ve zamanı Excel listesine ve seriporta gönderir.
      Serial.print(",");
      Serial.println(Number); //Öğrenci numarasını Excel listesine ve seriporta gönderir.
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
delay(1000); //LCD temizlenerek tekrar kart okutma işlemine hazır hale getirildi.

}
