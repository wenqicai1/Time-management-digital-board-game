#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Debug.h>
#include <MFRC522Extended.h>
#include <MFRC522Hack.h>
#include <require_cpp11.h>

/**
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read data from more than one PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 *
 * Example sketch/program showing how to read data from more than one PICC (that is: a RFID Tag or Card) using a
 * MFRC522 based RFID Reader on the Arduino SPI interface.
 *
 * Warning: This may not work! Multiple devices at one SPI are difficult and cause many trouble!! Engineering skill
 *          and knowledge are required!
 *
 * @license Released into the public domain.
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS 1    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI SS 2    SDA(SS)      ** custom, take a unused pin, only HIGH/LOW required **
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 */

#include <SPI.h>
#include <MFRC522.h>
#include "FastLED.h" // Include of the FastLED library

#define led_pin 5 // Pin 5 connected to DIN of RGB Stick
#define NUM_LEDS 30 // # of WS2812 LEDs on stick
CRGB leds[NUM_LEDS]; // FastLED Library Init
#define MAX_LEN 30

constexpr uint8_t RST_PIN = 9;     // Configurable, see typical pin layout above
constexpr uint8_t SS_1_PIN = 8;   // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2
constexpr uint8_t SS_2_PIN = 10;    // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 1
constexpr uint8_t SS_3_PIN = 7;
constexpr uint8_t NR_OF_READERS = 3;

const int buttonPin_1 = 3;
int buttonState_1 = 0;
const int buttonPin_2 = 4;
int buttonState_2 = 0;
const int buttonPin_3 = 2;
int buttonState_3 = 0;

byte ssPins[] = {SS_1_PIN, SS_2_PIN,SS_3_PIN};

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

//byte FoundTag; // Variable used to check if Tag was found
//byte ReadTag; // Variable used to store anti-collision value to read Tag information
//byte TagData[MAX_LEN]; // Variable used to store Full Tag Data
//byte Tarserial[10]; // Variable used to store only Tag Serial Number
//byte GoodTagSerialNumber[4] = {43, 22, 16, 41}; // The Tag Serial number we are looking for
int Inled = 10;
byte Card1[4]={129,239,164,69};
byte Card2[4]={161,139,210,69};
byte Card3[4]={129,133,143,69};
byte Card4[4]={49,82,193,46};
byte Card5[4]={17,19,156,69};
byte Card6[4]={115,25,93,46};
byte Card7[4]={113,223,156,69};
byte Card8[4]={49,150,55,46};
byte Card9[4]={115,238,163,46};
byte Card10[4]={161,160,170,69};
byte Card11[4]={209,99,172,69};
byte Card12[4]={193,01,171,69};
byte Card13[4]={81,88,204,69};
byte Card14[4]={161,91,211,69};
byte Card15[4]={199,177,232,43};
byte Card16[4]={97,20,102,69};
byte Card17[4]={193,133,126,69};
byte Card18[4]={209,128,152,69};
//MFRC522 nfc(SDAPIN, RESETPIN); // Init of the library using the UNO pins declared above

/**
 * Initialize.
 */
void setup() {

  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();        // Init SPI bus
  FastLED.addLeds<NEOPIXEL,led_pin>(leds, NUM_LEDS); // Setup FastLED Library
  FastLED.clear();
  for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 

pinMode(buttonPin_1,INPUT);
pinMode(buttonPin_2,INPUT);
pinMode(buttonPin_3,INPUT);
  
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

/**
 * Main loop.
 */
void loop() {

  buttonState_1=digitalRead(buttonPin_1);
        if(buttonState_1 == HIGH)
        {
          Serial.println("LED ON");
          FastLED.clear();
           Inled+=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
          }
buttonState_2=digitalRead(buttonPin_2);
        if(buttonState_2 == HIGH)
        {
          Serial.println("LED ON");
          FastLED.clear();
           Inled-=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
          }
buttonState_3=digitalRead(buttonPin_3);
        if(buttonState_3 == HIGH)
        {
          Serial.println("LED ON");
          FastLED.clear();
         Inled=10;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        
          }


  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);
      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.println();
      Serial.print(F("PICC type: "));
      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
     
if(memcmp(Card1, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled+=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled+=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    } //if (mfrc522[reader].PICC_IsNewC
if(memcmp(Card2, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled+=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
    if(memcmp(Card3, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
        Inled+=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled+=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
    if(memcmp(Card4, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled+=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled-=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
  if(memcmp(Card5, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled+=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled+=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
 if(memcmp(Card6, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled+=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled+=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
 if(memcmp(Card7, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled+=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled+=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled+=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
 if(memcmp(Card8, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled-=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled+=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
            
    }
 if(memcmp(Card9, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled+=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
 if(memcmp(Card10, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled+=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled+=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
 if(memcmp(Card11, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled-=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled+=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled+=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
 if(memcmp(Card12, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled-=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled+=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
 if(memcmp(Card13, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled+=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled-=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
   if(memcmp(Card14, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled-=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled+=2;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled+=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }  
     if(memcmp(Card15, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled-=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled+=2;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
        if (reader==2)
      {
        FastLED.clear();
        Inled-=2;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
         FastLED.setBrightness(50);
         FastLED.show(); 
        }     
    }
 if(memcmp(Card16, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled-=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled+=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
           
    }
 if(memcmp(Card17, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled+=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled-=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
       
    }
 if(memcmp(Card18, mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size) == 0)
 {
     if (reader==0)
      {
        FastLED.clear();
        Inled+=1;
        for (int x = 0; x < Inled; x++) {
        leds[x] = CRGB::Blue;
        }
        FastLED.setBrightness(50);
        FastLED.show(); 
        }

       if (reader==1)
      {
        FastLED.clear();
       Inled-=1;
        for (int x = 0; x < Inled; x++) {
            leds[x] = CRGB::Blue;
           }
            FastLED.setBrightness(50);
            FastLED.show(); 
        }
       
    }

    
  } //for(uint8_t reader
  }
  
  
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

