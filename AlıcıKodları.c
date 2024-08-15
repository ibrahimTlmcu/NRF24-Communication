


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

//verici ile alıcının kanal isimleri aynı olmalıdır
const byte address[8] = "robolink";

void setup()
{
  while (!Serial);
    Serial.begin(9600);
  
  radio.begin();
    // Initialize the OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();

  //iletişim adresi tanımla
  radio.openReadingPipe(0, address);                                                                                                                                                                                                                                                                                        
  
  //modülü alıcı olarak ayarla
  radio.startListening();
}

void loop()
{
  //eğer data geldiyse okumaya başla
  if (radio.available())
  {
    char text[32] = {0}; //en fazla 32 karakter bir veri alabileceğinden dolayı, 32 karakterlik 0 lar kümesi oluşturduk. 
    //Gelen tüm karakterleri buraya sırayla geçirmiş olacağız 
    
    radio.read(&text, sizeof(text));                                                                                                                                          
    display.clearDisplay();
    display.setTextSize(2); // 2X scaled text
    display.setTextColor(WHITE);
    display.setCursor(10, 0);
    display.println(text); // Display received text
    display.display(); // Update the display
    Serial.println(text); //Seri ekrana alınan veriyi yazdır
    delay(10);
  }
  else{
delay(10);
    display.clearDisplay();
    display.setTextSize(2); // 2X scaled text
    display.setTextColor(WHITE);
    display.setCursor(10, 0);
   
    display.display(); // Update the display
    display.println("Basarisiz !! "); //Seri ekrana alınan veriyi yazdır                                                                                                                                    
    
  }
  
}
