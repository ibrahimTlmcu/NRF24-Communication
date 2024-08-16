#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

int xPozisyonA;
int yPozisyonA;

int xPozisyonB;
int yPozisyonB;
int butonDurumA;
int butonDurumB;

int butonPinA = 5; 
int butonPinB = 4; 


int xPinA = A7;
int yPinA = A3;

int xPinB = A0; 
int yPinB = A1; 

struct Data {
  int joystickX1;
  int joystickY1;
  int joystickX2;
  int joystickY2;
  int buttonStateA;
  int buttonStateB;
};

Data dataToSend;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//NRF24L01 
RF24 radio(9, 8);  // CE, CSN

// Haberleşme kanalı (herhangi bir "string" olabilir)
const byte address[8] = "robolink";

void setup()
{
  Serial.begin(9600);  // Seri haberleşmeyi başlat
  Serial.println("Deneme");
  pinMode(butonPinA, INPUT_PULLUP);
  pinMode(butonPinB, INPUT_PULLUP);

  pinMode(xPinA, INPUT);
  pinMode(yPinA, INPUT);
  pinMode(xPinB, INPUT);
  pinMode(yPinB, INPUT);


  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();

  display.clearDisplay();
  radio.begin();
  
  // Haberleşme adresini tanımla 
  radio.openWritingPipe(address);
  // Verici olarak ayarla
  radio.stopListening();
}

void loop()
{
  dataToSend.joystickX1 = map(analogRead(A7), 0, 1023, -5, 5);
  dataToSend.joystickY1 = map(analogRead(A3), 0, 1023, -5, 5);
  dataToSend.joystickX1 = map(analogRead(A0), 0, 1023, -5, 5);
  dataToSend.joystickY1 = map(analogRead(A1), 0, 1023, -5, 5);
  butonDurumA = digitalRead(butonPinA);
  butonDurumB = digitalRead(butonPinB);
 
  
  xPozisyonA = analogRead(xPinA);
  yPozisyonA = analogRead(yPinA);
  xPozisyonB = analogRead(xPinB);
  yPozisyonB = analogRead(yPinB);

  Serial.print(" | Buton Durum: ");
  Serial.println(butonDurumA);

  Serial.print(" | Buton Durum: ");
  Serial.println(butonDurumB);
 
  char mesajXA[20];
  char mesajYA[20];

  char mesajXB[20];
  char mesajYB[20];

  // X ve Y pozisyonlarını formatlı şekilde hazırlama
  sprintf(mesajXA, "x: %d", xPozisyonA);
  sprintf(mesajYA, "y: %d", yPozisyonA);
    sprintf(mesajXB, "x: %d", xPozisyonB);
  sprintf(mesajYB, "y: %d", yPozisyonB);

  Serial.println(mesajXA);
  Serial.println(mesajYA);
  Serial.println(mesajXB);
  Serial.println(mesajYB);

  display.clearDisplay();
  display.setTextSize(1,3); // 2X ölçekli metin
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println(mesajXA); // X pozisyonunu ekranda göster
  display.display();
  display.setCursor(10, 25); // Y pozisyonunu ikinci satırda göster
  display.println(mesajYA);
  display.display();
  display.setCursor(65, 0); // Y pozisyonunu ikinci satırda göster
  display.println(mesajXB);
  display.display();
  display.setCursor(65, 25); // Y pozisyonunu ikinci satırda göster
  display.println(mesajYB);
  display.display();

  radio.write(&dataToSend, sizeof(dataToSend));
}
