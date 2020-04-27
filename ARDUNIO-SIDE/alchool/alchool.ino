int vibration=7;//titresim sensor pini tanimlandi
int led=13; //mavi led pini tanimlandi

int dokunmatik = 8; // Dokunmatik Sensör Pini
int kirmiziLed = 9; // Kırmızı Led Pini
int yesilLed = 10; // Yeşil Led Pini

#include <LiquidCrystal.h> //lcd nin hazir kutuphanesi
LiquidCrystal lcd (12,11,5,4,3,2); //kutuphaneye pin baglanti girislerini tanimliyoruz
int mq3_analogPin = A0; // MQ3 alkol gaz sensorunu baglanacak port tanimlanmasi

unsigned long ilkZaman;//islemin baslandigi zaman tanimlanmasi
unsigned long sonZaman; // islemin bittigi zaman tanimlanmasi
 
void setup() {
   pinMode(vibration,INPUT); //titresim sensorunu giris olarak ayarladik
   pinMode(led,OUTPUT); // led cikis olarak olarak atadik
   Serial.begin(9600); // serial monitoru kullanmak icin 
   pinMode(kirmiziLed, OUTPUT); // kirmizi ledicikis atadik
   pinMode(yesilLed, OUTPUT); //yesil ledi cikis olsrsk atadik
   pinMode(dokunmatik, INPUT); // dokunmatik sensoru giris olarak olarak atadik
   delay(500);
   lcd.begin(16,2); //lcd tanimlamasini baslattik
   lcd.setCursor(0,0); //alt satira yazi yazdirma
 
}
 
void loop() {
   digitalWrite(kirmiziLed,LOW); // kirmizi ledi sondurme
   Serial.println("kirmizi led yandi"); //ekrana yazdirma
   digitalWrite(yesilLed,HIGH); // yesil ledi yaktik
   Serial.println("yesil led sondu");  //ekrana yazdirma
  int val = digitalRead(vibration);//titrsim sensorunu val degiskenine atadik
  
  if(val==1) //eger vall degiskeni 1 e esit ise
  {
    Serial.println("titresim gerceklesti");// ekrana yazdirma
    digitalWrite(led,LOW); //mavi ledi yaktik.
    delay(500);
    digitalWrite(led,HIGH);// mavi ledi sondurduk
    delay(100);
         int dokunmatikDeger = digitalRead(dokunmatik);// dokunmatik sensoru dokunmatikdeger degiskenine atadik
         while(dokunmatikDeger == LOW){ // dokunmatik sensore basilmadi ise
          Serial.println("dokunmatige basilmadi");//ekrana yazdirma
         dokunmatikDeger = digitalRead(dokunmatik);
          digitalWrite(kirmiziLed,LOW);
          delay(500);
          if(dokunmatikDeger==HIGH) // eger dokunmatik sensore basildi ise
          {
            Serial.println("dokunmatige basildi");//ekrana yazdirma
            digitalWrite(kirmiziLed,HIGH);
            digitalWrite(yesilLed,LOW);
            delay(1000);
            digitalWrite(yesilLed,HIGH);
              ilkZaman=millis();// islemin ne kadar surede tamamlandigini gormek icin ilk zamani baslattik
             while(true) //sonsuz dongu olusturuldu
             {
              int mq3_value = analogRead(mq3_analogPin); //alkol gaz sensorunu mq3_value degiskenine atadik
              Serial.println("alkol seviyesi:" );//ekrana yazdirma
              Serial.println(mq3_value); //olculen alkol seviyesi
              lcd.print(mq3_value);//lcd ekranina yazdirma
              lcd.noDisplay(); //ekrandan gelip gitme komutu
              delay(1000);
              lcd.display(); //lcd ekranini kapatir.
              delay(5000);
             lcd.clear();//lcd ekrani temizler
                sonZaman=millis();// toplam sureyi hesaplamak icin son zamani baslattik
                Serial.println(sonZaman-ilkZaman); //ekranda toplam gecen sureyi gosterme
                if(sonZaman-ilkZaman>5000) // 5 saniye sonunda donguden cikilir.
                {
                  break; //donguden cikis.
                 }
                
             }
            
            break; // ilk donguden cikis
            }
         }
         digitalWrite(led,HIGH); //islem sonunda mavi led soner.
     
   }
   else
   digitalWrite(led,HIGH); //  titresim gerceklesmez ise mavi led soner.
}
