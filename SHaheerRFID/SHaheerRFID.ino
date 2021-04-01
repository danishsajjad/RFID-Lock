//#include <IRremote.h>
#include <EEPROM.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define RST_PIN         9
#define SS_PIN          10

MFRC522 mfrc522(SS_PIN, RST_PIN);

//int RECV_PIN = 18;

//IRrecv irrecv(RECV_PIN);

//decode_results results;

String read_rfid;
String ok_rfid_1 = "2aea1410";
String ok_rfid_2 = "7e389385";

int a = 0;



int buzzerpin = 16;
int doorsensor = 15;
int doorstate = 0;
Servo lockservo;
int button = 8;
int buttonstate = 0;


void setup()
{
	lcd.begin(16, 2);

	pinMode(buzzerpin, OUTPUT);
	pinMode(button, INPUT);
	pinMode(doorsensor, INPUT);
	lcd.write("Hello!!");
	doorstate = digitalRead(doorsensor);



	lockservo.attach(14);
	delay(1000);
	if (doorstate == HIGH)
	{
		lockservo.write(70);
	}
	if (doorstate == LOW)
	{
		lockservo.write(160);
	}

	Serial.begin(9600);
	//irrecv.enableIRIn();
	SPI.begin();
	mfrc522.PCD_Init();





}
void dump_byte_array(byte *buffer, byte bufferSize) {
	read_rfid = "";
	for (byte i = 0; i < bufferSize; i++) {
		read_rfid = read_rfid + String(buffer[i], HEX);
	}
}

void loop()
{
	doorstate = digitalRead(doorsensor);
	/*
	if (irrecv.decode(&results)) {
	a = results.value;
	Serial.println(a);
	irrecv.resume(); // Receive the next value
	}*/
	override();
	if (doorstate == LOW)
	{
		delay(200);
		lockservo.write(160);
		lcd.clear();
		lcd.print("Scan Card");
		delay(50);
		if (!mfrc522.PICC_IsNewCardPresent())
			return;
		// Select one of the cards
		if (!mfrc522.PICC_ReadCardSerial())
			return;

		dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
		if (read_rfid == ok_rfid_1 || read_rfid == ok_rfid_2 || read_rfid == "053960b6" || read_rfid == "e53f68b6" || read_rfid == "d50d59d6" || read_rfid == "43c5d98b" || read_rfid == "a3f4cd8b" || read_rfid == "d30fb68b" || read_rfid == "c5f061b6" || read_rfid == "b3a7bd8b" || read_rfid == "f5ce65b6" || read_rfid == "a59a66b6" || read_rfid == "a344cb8b" || read_rfid == "54754430" || read_rfid == "63a5eb8b" || read_rfid == "d390c78b" || read_rfid == "e5e75eb6" || read_rfid == "8388c18b" || read_rfid == "9306cb8b" || read_rfid == "35a75eb6" || read_rfid == "c329c18b" || read_rfid == "6363cc8b" || read_rfid == "839bc68b" || read_rfid == "2aea1410" || read_rfid == "7e389385" || read_rfid == "556863b6" || read_rfid == "a58380b5" || read_rfid == "24be2dc9" || read_rfid == "95a051d6")
		{
			Serial.println(read_rfid);
			lockservo.write(70);
			digitalWrite(buzzerpin, HIGH);
			delay(200);
			digitalWrite(buzzerpin, LOW);
			lcd.clear();
			Serial.println(read_rfid);
			if (read_rfid == ok_rfid_1) {
				lcd.print("Danish Sajjad");
			}
			if (read_rfid == ok_rfid_2) {
				lcd.print("Mohsin Iftikhar");


			}
			if (read_rfid == "053960b6") {
				lcd.print("0000");
			}
			if (read_rfid == "e53f68b6") {
				lcd.print("M.Mahad");
			}
			if (read_rfid == "d50d59d6") {
				lcd.print("0000");
			}
			if (read_rfid == "43c5d98b") {
				lcd.print("Shehryar");
			}
			if (read_rfid == "a3f4cd8b") {
				lcd.print("Aizaz Ansari");
			}
			if (read_rfid == "d30fb68b") {
				lcd.print("0000");
			}
			if (read_rfid == "c5f061b6") {
				lcd.print("Saim-ul-Hassan");
			}
			if (read_rfid == "b3a7bd8b") {
				lcd.print("Saad Ejaz");
			}
			if (read_rfid == "f5ce65b6") {
				lcd.print("M.Bin Amir");
			}
			if (read_rfid == "a59a66b6") {
				lcd.print("Hamis Haider");
			}
			if (read_rfid == "a344cb8b") {
				lcd.print("Ms. Faiqa");
			}
			if (read_rfid == "54754430") {
				lcd.print("Mujtaba");
			}
			if (read_rfid == "63a5eb8b") {
				lcd.print("Usama Raheel");
			}
			if (read_rfid == "d390c78b") {
				lcd.print("Rohan Latif");
			}
			if (read_rfid == "e5e75eb6") {
				lcd.print("Hassan Mahad");
			}
			if (read_rfid == "8388c18b") {
				lcd.print("M.Waleed Anwar");
			}
			if (read_rfid == "556863b6") {
				lcd.print("Ms. Fareeha");
			}
			if (read_rfid == "839bc68b") {
				lcd.print("Shaheer Sajid");
				lcd.setCursor(0, 1);
				lcd.print("President");
			}
			if (read_rfid == "6363cc8b") {
				lcd.print("Abdullah Irfan");
				lcd.setCursor(0, 1);
				lcd.print("Vice President");
			}
			if (read_rfid == "35a75eb6") {
				lcd.print("Bilal Azhar");
			}
			if (read_rfid == "9306cb8b") {
				lcd.print("00000");
			}
			if (read_rfid == "c329c18b") {
				lcd.print("Hamza Murad");
			}
			if (read_rfid == "95a051d6") {
				lcd.print("M.Atta");
			}
			if (read_rfid == "24be2dc9") {
				lcd.print("Hamza Ahmed");
			}
			if (read_rfid == "a58380b5") {
				lcd.print("Ibrahim Mansoor");
			}

			delay(3000);
		}



		doorstate = digitalRead(doorsensor);
		while (doorstate == HIGH)
		{
			doorstate = digitalRead(doorsensor);
			lcd.clear();
			lcd.print("Door Open");
			delay(300);
		}
		delay(2000);
		lockservo.write(160);
	}

	else

	{
		delay(2000);
		lockservo.write(70);
		delay(1000);
		doorstate = digitalRead(doorsensor);
		while (doorstate == HIGH)
		{
			doorstate = digitalRead(doorsensor);
			lcd.clear();
			lcd.print("Door Open");
			delay(300);
		}
		delay(2000);
		lockservo.write(160);
	}


















}
void override()
{
	buttonstate = digitalRead(button);
	if (buttonstate == HIGH /*|| a == -23971*/)
	{
		delay(1000);
		lockservo.write(70);
		lcd.clear();
		lcd.print("Override");
		delay(5000);
		doorstate = digitalRead(doorsensor);
		while (doorstate == HIGH)
		{
			doorstate = digitalRead(doorsensor);
			lcd.clear();
			lcd.print("Door Open");
			delay(300);
		}
		delay(2000);
		lockservo.write(160);
		//    irrecv.resume();


	}
	else
	{
		lockservo.write(160);
	}
}





