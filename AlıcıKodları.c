#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//NRF24L01 
RF24 radio(9, 8);  // CE, CSN
//haberleşme kanalı (herhangi bir "string" olabilir)
const byte address[8] = "robolink";
void setup()
{
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();

  display.clearDisplay();
  radio.begin();
  
  //haberleşme adresini tanımla 
  radio.openWritingPipe(address);
  
  //verici olarak ayarla
  radio.stopListening();
}

void loop()
{
  //sürekli mesaj gönder
  
  const char text[] = "CONNECTED ! "; //mesaj en fazla 32 karakter olabilir
  radio.write(&text, sizeof(text)); 
   // OLED ekranı temizle ve yazdır
  display.clearDisplay();
  display.setTextSize(2); // 2X ölçekli metin
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println("Gonderim Basladi"); // X pozisyonunu ekranda göster

  display.setCursor(10, 30); // Y pozisyonunu ikinci satırda göster
  delay(1000); //1 saniye bekle
}



