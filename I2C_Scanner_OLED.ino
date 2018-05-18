/*********************************************************************
Imsaiguy

I2C scanner
displays using OLED 128x64

*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup()   {                
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

}

void loop() {
  
  
byte error, address;
  int nDevices; 
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("I2C devices found:");
  display.setTextSize(2);
  display.display();
  
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      if (address<16) 
        display.display();  // needed to clear 0x3c probe
        display.print("0x"); display.println(address, HEX);
        display.display();
      nDevices++;
    }
    else if (error==4) 
    {
      display.print("error@ 0x");
      if (address<16) 
        display.print("0x");
      display.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    display.println("None");
  else
  delay(2000);           // wait 2 seconds for next scan  

}



