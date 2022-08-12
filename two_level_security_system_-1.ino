#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <Servo.h>
Servo myservo; // create servo object to control a servo
int val; 
int pos = 0;
//const int rs = 14, en = 15, d4 = 16, d5 = 17, d6 = 18, d7 = 19;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

#define trigPin 12    // trigger pin of ultrasonic sensor  
#define echoPin 13   // echo pin of ultrasonic sensor.
#define MaxDist 15  // Max distance (cm)
#define buz 11
#define SS_PIN 6
#define RST_PIN 2
MFRC522 mfrc522(SS_PIN, RST_PIN); 
void setup() {
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  myservo.attach(10); 
  Serial.begin(9600); 
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522  
  lcd.setCursor(0,1);
lcd.print("Visitor alert!!");
delay(1000);
}

void loop() {
  //Serial.println("beeping");
  //buzzer_tone();
long duration, distance;
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); 
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;        // get distance in cm
float p= (MaxDist - distance);
float p1= (p/MaxDist);                 // converting into percentage
int percent= p1 *100;
Serial.println(percent);
 if (percent >= 80){
        //Serial.println("Entered");
        lcd.setCursor(0,1);
        lcd.print("Visitor alert!!");
        delay(1000);
        RFID_scan();        
}
else{
  lcd.print("****");
}
}
void RFID_scan(){
 if ( ! mfrc522.PICC_IsNewCardPresent())
{
return;
}
// Select one of the cards
if ( ! mfrc522.PICC_ReadCardSerial())
{
return;
}
//Show UID on serial monitor
Serial.println("");
Serial.print("UID tag :");
String content= "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++)
{
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
Serial.println();
//Serial.print("Message : ");
//Serial.print("RELAY: ");
content.toUpperCase();
if (content.substring(1) == "FC 11 A4 32") //change here the UID of the card/cards that you want to give access
{
Serial.println("Authorized access to doreamon");
Serial.println();
Serial.println("ON");
lcd.print("Access: FC 11 A4 32");
servo_rotation();
delay(1000);
}
else if (content.substring(1) == "5A 51 22 3F") //change here the UID of the card/cards that you want to give access
{
Serial.println("Authorized access to nobita");
Serial.println();
Serial.println("ON");
lcd.print("Access:5A 51 22 3F");
servo_rotation();
delay(1000);
}
else if (content.substring(1) == "DC 36 9A 32") //change here the UID of the card/cards that you want to give access
{
Serial.println("Authorized access to gian");
Serial.println();
Serial.println("ON");
lcd.print("Access: DC 36 9A 32");
servo_rotation();
delay(1000);
}
else if (content.substring(1) == "5A 3A FB 3F") //change here the UID of the card/cards that you want to give access
{
Serial.println("Authorized access to suniyo");
Serial.println();
Serial.println("ON");
lcd.print("Access: 5A 3A FB 3F");
servo_rotation();
delay(1000);
}
else{
  buzzer_tone();
  Serial.println("Access denied");
  lcd.noDisplay();
}

     
}
void servo_rotation(){

 // myservo.attach(6);  // attaches the servo on pin 9 to the servo object
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(5000);
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void buzzer_tone(){
  tone(buz,4000);
  delay(1000);
  noTone(buz);
 delay(100);
  tone(buz,4000);
  delay(500);
  noTone(buz);
  delay(50);
  tone(buz,4000);
  delay(100);
  noTone(buz);
  delay(50);
  
}
