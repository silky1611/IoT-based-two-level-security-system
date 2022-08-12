#include <MFRC522.h>
#include <Keypad.h> 
#include <SPI.h>
#include <Servo.h>
Servo myservo; // create servo object to control a servo
 int val;
//#define led A5
#define buz A2
#define SS_PIN 10
#define RST_PIN 9
//#define trigPin A4    // trigger pin of ultrasonic sensor  
//#define echoPin A3    // echo pin of ultrasonic sensor.
//#define MaxDist 15  // Max distance (cm)
int pos = 0;
MFRC522 mfrc522(SS_PIN, RST_PIN); 
char initial_password[4] = {'1', '2', '3', '4'};  // Variable to store initial password
char password[4];   // Variable to store users password
char key_pressed = 0; // Variable to store incoming keys
uint8_t i = 0;  // Variable used for counter
// defining how many rows and columns our keypad have
const byte rows = 4;
const byte columns = 4;
int j;
// Keypad pin map
char hexaKeys[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Initializing pins for keypad
byte row_pins[rows] = {2,3,4,5};
//byte row_pins[rows] = {5,6,7,8};
//byte column_pins[columns] = {4,3,2,A0};
byte column_pins[columns] = {A5,A4,A3,A2};
// Create instance for keypad
Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

void setup() {
  //pinMode(led, OUTPUT);
  myservo.attach(A0); 
 // pinMode(echoPin, INPUT);
  Serial.begin(9600); 
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  //Serial.println("Enter the pincode...");
  // Serial.println();
  Serial.println("Enter the Passcode..");
  Serial.println();
  
}

void loop() {
      key_pressed = keypad_key.getKey(); // Storing keys
      if (key_pressed)
      {
        password[i++] = key_pressed; // Storing in password variable
        delay(1000);
        Serial.print("*");
      }
      if (i == 4) // If 4 keys are completed
      {
        Serial.println(password);
        delay(100);  
      if (!(strncmp(password, initial_password, 4))) // If password is matched
        {
        // Serial.print("2"); 
         RFID_scan();  
}else{
  Serial.print("0");
}
  
     // delay(10000);
}

}
      



void RFID_scan(){
  //Serial.print("2");
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
//if (content.substring(1) == "FC 11 A4 32") //change here the UID of the card/cards that you want to give access
//{
//Serial.println("Authorized access to doreamon");
//Serial.println();
//Serial.println("ON");
//servo_rotation();
//delay(1000);
//}
if (content.substring(1) == "5A 51 22 3F") //change here the UID of the card/cards that you want to give access
{
Serial.println("Authorized access to nobita");
Serial.println();
Serial.println("ON");
servo_rotation();
delay(1000);
}
else if (content.substring(1) == "DC 36 9A 32") //change here the UID of the card/cards that you want to give access
{
Serial.println("Authorized access to gian");
Serial.println();
Serial.println("ON");
servo_rotation();
delay(1000);
}
else if (content.substring(1) == "5A 3A FB 3F") //change here the UID of the card/cards that you want to give access
{
Serial.println("Authorized access to suniyo");
Serial.println();
Serial.println("ON");
servo_rotation();
delay(1000);
}
else{
 buzzer_tone();
  Serial.println("Access denied");
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
