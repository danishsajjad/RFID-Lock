#include <Servo.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

/*Peripheral Definitions*/
#define RST_PIN  9
#define SS_PIN   10

MFRC522 idReader(SS_PIN, RST_PIN);

long unsigned int abc[] = {
	0x567890cd,
	0xff63dc67
};

int buzzer = 16;
int doorsensor = 15;
int button = 8;
bool input = false;
String memberName;
String read_rfid;

void setup()
{
	Serial.begin(9600);
	Serial.println("Initializing");
	//lcd.begin(16, 2);
	//lcd.write("PLease wait.");
	pinMode(buzzer, OUTPUT);
	pinMode(button, INPUT);
	pinMode(doorsensor, INPUT);
	SPI.begin();
	idReader.PCD_Init();
	//idReader.PCD_DumpVersionToSerial();
}

byte rfid[4];

void loop() {
	Serial.println("Looping");
	if (idReader.PICC_IsNewCardPresent()) {
		Serial.println("Card Detected");
		if (idReader.PICC_ReadCardSerial()) {
			Serial.println("Card Read");
			for (int x; x < idReader.uid.size; x++) {
				rfid[x] = idReader.uid.uidByte[x];
				Serial.print(rfid[x], HEX);
			}
			Serial.println("");
		}
	}
}
