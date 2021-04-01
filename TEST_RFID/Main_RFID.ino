#include <Servo.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

/*Peripheral Definitions*/
#define RST_PIN  9
#define SS_PIN   10

MFRC522 idReader(SS_PIN, RST_PIN);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
Servo lckServo;

/*Stored data*/


unsigned long int members[] = {
	0x053960b6,
	0xe53f68b6,
	0xd50d59d6,
	0x43c5D98b,
	0xa3f4cd8b,
	0x030fb68b,
	0xc5f061b6,
	0xb3a7bd8b,
	0xf5ce65b6,
	0xa59a66b6,
	0xa344cb8b,
	0x556863B6,
	0x54754430,
	0x63a5eb8b,
	0xd390c78b,
	0xe5e75eb6,
	0x8388c18b,
	0x7e389385};
unsigned long int premiummembers[] = {
	0x9306cb8b,
	0x35a75eb6,
	0xc329c18b,
	0x43c5d98b,
	0x6363cc8b,
	0x839bc68b,
	0x2aea1410,
	0x7e389385,
	0x01020304,
};
String membnames[] = {
	"M.Atta",
	"M.Mahad",
	"Ibrahim",
	"Shehryar",
	"Aizaz Ansari",
	"Hamza Ahmed",
	"Saim",
	"Saad Ejaz",
	"M.Bin Amir",
	"Hamis Haider",
	"Ms. Faiqa",
	"Ms. Fareha",
	"Mujtaba",
	"Usama Raheel",
	"Rohan Latif",
	"Hassan Mahad",
	"M.Waleed",
    "Sir Mohsin"};
String premnames[] = {
	"Danish Sajjad",
	"Bilal Azhar",
	"Unknown",
	"Unknown",
	"Unknown",
	"Hamza Murad",
	"Abdullah Irfan",
	"Shaheer Sajid",
	"Danish Sajjad"
};

/*Variable Declaration*/

int buzzer = 16;
int doorsensor = 15;
int button = 8;
bool input = false;
String memberName;
int rfid[4];
unsigned long int RFID;
unsigned long int EXP;

//The real fun begins here
/*
void dump_byte_array(byte *buffer, byte bufferSize) {
	read_rfid = "";
	for (byte i = 0; i < bufferSize; i++) {
		read_rfid = read_rfid + String(buffer[i], HEX);
		Serial.println(i);
	}
	idReader.PICC_HaltA();
}*/

void setup()
{
	Serial.begin(9600);
	Serial.println("Initializing");
	lcd.begin(16, 2);
	lcd.write("PLease wait.");
	pinMode(buzzer, OUTPUT);
	pinMode(button, INPUT);
	pinMode(doorsensor, INPUT);
	lckServo.attach(14);
	SPI.begin();
	idReader.PCD_Init();
	//idReader.PCD_DumpVersionToSerial();
	if (digitalRead(doorsensor) == LOW) {
		lockdoor();
	}
	else if (digitalRead(doorsensor) == HIGH) {
		unlockdoor();
	}
	idReader.PCD_AntennaOff();
	idReader.PCD_SetAntennaGain(B01110000);
	idReader.PCD_AntennaOn();
}

//Test wala loop is commented.
/*
void loop() {
	defaultDisplay();
	unlockdoor();
	greetMember("shaheer");
	delay(500);
	rejectMember();
	lockdoor();
	delay(500);
	override();
	ReadRFID();
}*/
//Sai Wala loop is meant to run.
void loop() {
	start:
	memberName = "";
	defaultDisplay();
	input = false;

	while (digitalRead(doorsensor) == LOW) {
		if (digitalRead(button) == HIGH) {
			// When override button is pressed
			memberName="Guest";
			input = true;
		}
		else if (ReadRFID() == true && identifyMember() == true) {
			//When an authorised RFID card is detected
			input = true;
		}
		else if (ReadRFID() == true && identifyMember() == false) {
			//When an unauthorised RFID card is detected
			rejectMember();
			input = false;
			goto start;
			//loop();
		}
		
		switch (input)
		{
		case true:
			greetMember(memberName);
			unlockdoor();
			unsigned long int previousmillis;
			previousmillis = millis();
			Serial.println(previousmillis);
			while (digitalRead(doorsensor) == LOW) {
				if (millis() - previousmillis >= 5000) {
					lockdoor();
					loop();
				}
				Serial.println(millis());
				
			};
			//Serial.println("Door Opened");
			break;
		default:
			break;
		}
		
	}
	Serial.flush();
	if (digitalRead(doorsensor) == HIGH) {
		unlockdoor();
		//Serial.println("I'm Running");
		lcdprint("Close Door");
		//lcd.blink();
		while (digitalRead(doorsensor) == HIGH) {  }
		lockdoor();
	}

}

//Required Proceedures

//Basic Proceedures/Functions
void unlockdoor() {
	//Serial.println("Door Unlocked");
	lckServo.write(50);
	digitalWrite(buzzer, HIGH);
	delay(500);
	digitalWrite(buzzer, LOW);
}
void lockdoor() {
	//Serial.println("Door Locked");
	digitalWrite(buzzer, HIGH);
	delay(500);
	digitalWrite(buzzer, LOW);
	lckServo.write(160);
}
void rejectMember() {
	//Serial.println("Rejected a stranger... :D");
	lcd.clear();
	lcd.print("Unauthorized");
	//lcd.setCursor(0, 1);
	//lcd.print("Card");
	digitalWrite(buzzer, HIGH);
	delay(25);
	digitalWrite(buzzer, LOW);
	delay(25);
	digitalWrite(buzzer, HIGH);
	delay(25);
	digitalWrite(buzzer, LOW);
	delay(25);
	digitalWrite(buzzer, HIGH);
	delay(25);
	digitalWrite(buzzer, LOW);
	delay(4000);
}
void defaultDisplay() {
	lcd.clear();
	lcd.noBlink();
	lcd.noAutoscroll();
	lcd.print("Scan Card Below");
	//lcd.println("Below");
}
void lcdprint(String abc) {
	lcd.clear();
	lcd.print(abc);
}
void exponent(int i) {
	EXP = 0;
	if (i == 0) {
		EXP = 1;
	}
	else if (i == 1) {
		EXP = 256;
	}
	else if (i == 2) {
		EXP = 65536;
	}
	else if (i == 3) {
		EXP = 16777216;
	}
}
//RFID Proceedures/Functions
bool ReadRFID() {
	// Look for new cards
	if (idReader.PICC_IsNewCardPresent()) {
		//Serial.println("Card Detected");
		//Reset Array
		for (int i; i < sizeof(rfid) / sizeof(rfid[1]) - 1; i++) {
			rfid[i] = 0;
		}
		if (idReader.PICC_ReadCardSerial()) {
			//Take input
			for (int x = 0; x <= idReader.uid.size; x++) {
				rfid[x] = idReader.uid.uidByte[3-x];
				//Serial.print(rfid[x], HEX); //Serial.println("");
				//Serial.print(x);
			}
			//Serial.println("");
			//Convert to decimal system
			RFID = 0;
			//Serial.println(sizeof(rfid) / sizeof(rfid[1]));
			for (int i=0; i <= sizeof(rfid)/sizeof(rfid[1]) - 1; i++) {
				exponent(i);
				//Serial.println(rfid[i]);
				RFID += rfid[i]* EXP;
				//Serial.println(i);
				//Serial.println(EXP);
				//Serial.println(RFID);
			}
			//Serial.println(RFID, HEX);
			//Serial.println(RFID);
			return true;
		}
	}
	return false;
}
bool identifyMember() {
	memberName = "";
	//Serial.println(rfid, HEX);
	for (int i = 0; i <= sizeof(members)/sizeof(members[1]) - 1; i++) {

		if (RFID == members[i]) {
			memberName = membnames[i];
			//Serial.println(memberName);
			//Serial.println(i);
			//Serial.println(i);
			input = true;
			return true;
			break;
		}
		//Serial.println("Serched Members");
	}
	//Serial.println(sizeof(premiummembers) / sizeof(premiummembers[1]) - 1);
	for (int i = 0; i <= sizeof(premiummembers) / sizeof(premiummembers[1]) - 1; i++) {
		if (RFID == premiummembers[i]) {
			memberName = premnames[i];
			//Serial.println(memberName);
			//Serial.println(i);
			input = true;
			return true;
			break;
		}
		//Serial.println(premnames[i]);
		//Serial.println("Searched PremiumMembers");
	}
	Serial.println("Member not Found");
	input = false;
	return false;
}
void greetMember(String member) {
	//Serial.println("Greeting member");
	lcd.clear();
	lcd.print("Welcome ");
	lcd.setCursor(0, 1);
	lcd.print(member);
	//lcd.autoscroll();
	//Serial.println(member);
}