#include <Arduino.h>
#include "SparkFun_u-blox_GNSS_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_u-blox_GNSS
#include <DFRobot_GDL.h>
#include <SD.h>

#define TFT_DC  25 
#define TFT_CS  14
#define TFT_RST 26
#define TFT_BL  D13

SFE_UBLOX_GNSS myGNSS;
DFRobot_ILI9341_240x320_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);

void fermion_print(){

  	screen.fillScreen(COLOR_RGB565_WHITE);
	screen.invertDisplay(false);
	// 0x00FF is the color data in the format of RGB565
	int16_t color = 0x00FF;
	// Set text wrapping mode
	// true = Text word wrap, false = No word wrap
	screen.setTextWrap(false);
	//Fill color, RGB color with 565 structure
	//screen.fillScreen(COLOR_RGB565_BLACK);

	//Set the coordinate position x = 0, y = 50
	screen.setCursor(0, 0);
	//Set the text color; this is a changeable value
	screen.setTextColor(COLOR_RGB565_BLACK);
	//Set text size to 0
	screen.setTextSize(2);
	//Output text
	double longitude = (double)myGNSS.getLongitude()/10000000;
	double latitude = (double)myGNSS.getLatitude()/10000000; 
	Serial.println("-------------------------");
	Serial.print("\tLATITUDE: ");
	Serial.print(latitude);
	Serial.print("\tLONGITUDE: ");
	Serial.println(longitude);
	Serial.println("-------------------------");

	screen.println("Longitude(deg): ");
	screen.println(longitude, 8);
	screen.println("Latitude(deg): ");
	screen.println(latitude, 8);

	screen.println("Alt(ft above ellip):");
	screen.println((double)myGNSS.getAltitude()/304.8);
	screen.println("Alt(ft above MSL):");
	screen.println((double)myGNSS.getAltitudeMSL()/304.8);
}

void setup(){
	Serial.begin(115200);
	screen.begin();
	Wire.begin();

	if (myGNSS.begin() == false)
  	{
	    Serial.println(F("u-blox GNSS module not detected at default I2C address. Please check wiring. Freezing."));
	    while (1);
  	}

	//This will pipe all NMEA sentences to the serial port so we can see them
	myGNSS.enableDebugging();
	myGNSS.setNMEAOutputPort(Serial);
}

void loop(){
	myGNSS.checkUblox();

	fermion_print();

	delay(5000);
}
