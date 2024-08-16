#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

int xPozisyon;
int yPozisyon;
int butonDurum;

int xPin = A1; 
int yPin = A2; 


struct Data {
  int joystickX1;
  int joystickY1;
  int joystickX2;
  int joystickY2;
  int buttonState;
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
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

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
  
  dataToSend.joystickX1 = map(analogRead(A0), 0, 1023, -5, 5);
  dataToSend.joystickY1 = map(analogRead(A1), 0, 1023, -5, 5);
  
  //dataToSend.joystickX1 = map(analogRead(A0), 0, 1023, -5, 5);

  xPozisyon = analogRead(xPin);
  yPozisyon = analogRead(yPin);

  char mesajX[20];
  char mesajY[20];

  // X ve Y pozisyonlarını formatlı şekilde hazırlama
  sprintf(mesajX, "x: %d", xPozisyon);
  sprintf(mesajY, "y: %d", yPozisyon);

  Serial.println(mesajX);
  Serial.println(mesajY);

  display.clearDisplay();
  display.setTextSize(2); // 2X ölçekli metin
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println(mesajX); // X pozisyonunu ekranda göster
  display.display();
  display.setCursor(10, 30); // Y pozisyonunu ikinci satırda göster
  display.println(mesajY);
  display.display();
  const char text[] = "Deneme ! "; // Mesaj en fazla 32 karakter olabilir

  radio.write(&dataToSend, sizeof(dataToSend));
 

  
}
