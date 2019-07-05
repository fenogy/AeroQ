#include <Wire.h>
#include <LGPRS.h>
#include <LGPRSClient.h>
#include <LGPRSServer.h>
#include <LGPS.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <SeeedGrayOLED.h>
#include <avr/pgmspace.h>


static unsigned char AeroQLogo[] PROGMEM = 
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFC, 0x00, 
0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0x00, 
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xC0, 
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xE0, 
0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x8F, 0xF0, 
0x01, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x03, 0xF0, 
0x01, 0xEF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x01, 0xF8, 
0x01, 0xE7, 0x80, 0x1F, 0xE0, 0x7C, 0xF0, 0x7F, 0xC0, 0xFC, 0x00, 0xF8, 
0x03, 0xE7, 0xC0, 0x3F, 0xF8, 0x7D, 0xF1, 0xFF, 0xE0, 0xF8, 0x00, 0xF8, 
0x03, 0xC7, 0xC0, 0x7F, 0xF8, 0x7F, 0xF3, 0xFF, 0xF0, 0xF8, 0x00, 0xF8, 
0x07, 0xC3, 0xC0, 0xF8, 0x7C, 0x7F, 0xF3, 0xF1, 0xF8, 0xF8, 0x00, 0xF8, 
0x07, 0xC3, 0xE0, 0xF8, 0x3C, 0x7F, 0x07, 0xC0, 0xF8, 0xF8, 0x00, 0xF8, 
0x07, 0xC3, 0xE0, 0xF0, 0x3C, 0x7E, 0x07, 0xC0, 0xF8, 0xF8, 0x00, 0xF8, 
0x0F, 0x83, 0xE1, 0xFF, 0xFC, 0x7C, 0x07, 0xC0, 0x7C, 0xF8, 0x00, 0xF8, 
0x0F, 0xFF, 0xF1, 0xFF, 0xFC, 0x7C, 0x07, 0x80, 0x7C, 0xF8, 0x00, 0xF8, 
0x0F, 0xFF, 0xF1, 0xFF, 0xFC, 0x7C, 0x07, 0x80, 0x7C, 0xFC, 0x00, 0xF8, 
0x1F, 0xFF, 0xF1, 0xF0, 0x00, 0x7C, 0x07, 0xC0, 0x7C, 0xFC, 0x01, 0xF8, 
0x1F, 0xFF, 0xF8, 0xF0, 0x00, 0x7C, 0x07, 0xC0, 0xF8, 0x7E, 0x01, 0xF0, 
0x1F, 0x00, 0xF8, 0xF8, 0x00, 0x7C, 0x07, 0xC0, 0xF8, 0x7F, 0x07, 0xF0, 
0x3E, 0x00, 0xFC, 0xFC, 0x18, 0x7C, 0x03, 0xF1, 0xF8, 0x3F, 0xFF, 0xE0, 
0x3E, 0x00, 0x7C, 0x7F, 0xF8, 0x7C, 0x03, 0xFF, 0xF0, 0x1F, 0xFF, 0xC0, 
0x3E, 0x00, 0x7C, 0x3F, 0xF8, 0x7C, 0x01, 0xFF, 0xE0, 0x0F, 0xFF, 0x80, 
0x7E, 0x00, 0x7E, 0x1F, 0xF8, 0x7C, 0x00, 0x7F, 0x80, 0x03, 0xFE, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF2, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFE, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFE, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFE, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/**************************************************************************/
/*
   State Machine Specific definitions
*/
/**************************************************************************/
int state = -1;
unsigned long currentTimeMs = 0;
unsigned long prevTimeMs = 0;
unsigned long aquireStartTimeMs = 0;

const int UPLOAD_TIME = 289000;
const int ONE_SECOND = 1000;
const int ONE_MIN = 60000;
const int GPS_TIMEOUT = ONE_MIN;
const int INIT = 1;
const int GPS_TRACK = 3;
const int GPRS_ACTIVATION = 2;
const int DATA_AQUIRE = 4;
const int DATA_UPLOAD = 5;
const int GPS_ACCURACY = 7;
bool gpsStatus = false;
bool gprsStatus = false;
bool dataAquireStatus = false;
bool dataUploadStatus = false;

double Lon = 0;
double Lat = 0;
double Alt = 0;
float  Temp = 0;
float  Humdty = 0;
long   Pressure = 0;
long   CoAccumulation = 0;
int    CoSamples = 0;
float  CoStatus = 0;
long   AirQAccumulation = 0;
int    AirQSamples = 0;
float  AirQStatus = 0;
int    NoOfSatelites = 0;
int    devID = 1;
int    sampleNo = 0;

String UrlEncodedData = "";
String strDevID = "";
String strLon = "";
String strLat = "";
String strAlt = "";
String strPressure = "";
String strTmp = "";
String strHumdty = "";
String strCo = "";
String strAirq = "";
String strDust = "";
String strCo2 = "";

bool humidityAquired = false;
bool pressureAquired = false;
bool tempAquired = false;
bool coAquired = false;
bool airqAquired = false;

/**************************************************************************/
/*
   GPRS Specific Definitions
*/
/**************************************************************************/

char server[] = "airq.sltidc.lk";
char path[] = "/index.php";
int port = 80; // HTTP

LGPRSClient client;

/**************************************************************************/
/*
   AirQuality  sensor Specific Definitions
*/
/**************************************************************************/
const int analogAirQPin = A0;
int AirQSensorValue = 0;
int AirQValue = 0;

/**************************************************************************/
/*
   Carbon Monoxide  sensor Specific Definitions
*/
/**************************************************************************/
const int analogCOPin = A1;
int COSensorValue = 0;
int COValue = 0;

/**************************************************************************/
/*
   Humidity sensor Specific Definitions
*/
/**************************************************************************/

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

/**************************************************************************/
/*
   Pressure sensor Specific Function subset
*/
/**************************************************************************/

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void displaySensorDetails(void)
{
  sensor_t sensor;
  bmp.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" hPa");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" hPa");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" hPa");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}


/**************************************************************************/
/*
    GPS Module Specific Function subset
*/
/**************************************************************************/

gpsSentenceInfoStruct info;
char buff[256];

/////////////////////
void RunSystem(void)
{

  int waitTime = 0;
  
  switch (state) {

    case INIT:

      Serial.println("Initialization Started..");
      if (Init())
      {
        state = GPRS_ACTIVATION;
      }
      else
      {
        state = -1;
        Serial.println("Initialization Error..");
      }
      break;

    case GPRS_ACTIVATION:
      Serial.println("Establishing GPRS Connectivity..");
      state = GPS_TRACK;
      Serial.println("GPRS Connectivity Estabilished..");
      break;

    case GPS_TRACK:

      Serial.println("Searching for Satellites..");
      LGPS.getData(&info);
      GpsReader((const char*)info.GPGGA);
      //Serial.print(NoOfSatelites);
      currentTimeMs = millis();
      //Serial.print(currentTimeMs - prevTimeMs);

      if (NoOfSatelites < GPS_ACCURACY && ((currentTimeMs - prevTimeMs) < 300000))
      {
        //previousTimeMs = currentTimeMs;
        delay(1000);
        gpsStatus = false;
        Serial.print(NoOfSatelites);
        Serial.println(" Satellites available, not enough for accuracy..");
        displayData(NoOfSatelites);

      }
      else if (NoOfSatelites < GPS_ACCURACY && ((currentTimeMs - prevTimeMs) > 300000))
      {
        prevTimeMs = currentTimeMs;
        gpsStatus = false;
        Serial.print(NoOfSatelites);
        Serial.println(" No of satellites not enough..GPS Timeout ..");
        Serial.println("System will continue without GPS data..");
        state = DATA_AQUIRE;
        aquireStartTimeMs = millis();
        displayData(1500);
        break;
      }
      else
      {
        gpsStatus = true;
        state = DATA_AQUIRE;
        aquireStartTimeMs = millis();
        Serial.println("Satellite signals aquired...");
        Serial.print(NoOfSatelites);
        Serial.println(" Satellites found.. Position Locked..");
        displayData(2000);
      }
      break;

    case DATA_AQUIRE:

      //Serial.println("Reading Sensor Data..");
      //delay(5000);
      currentTimeMs = millis();

      if ((currentTimeMs - prevTimeMs) > ONE_SECOND)
      {
        prevTimeMs = currentTimeMs;

        if (!pressureAquired)
          pressureAquired = tempAquired = getTempAndPressure();

        if (!humidityAquired)
          humidityAquired = getHumidity();

        //if(!coAquired)
        coAquired = getCO();

        airqAquired = getAirQ();
        
        sampleNo++;
        Serial.print('.');
        
        if(sampleNo%80 == 0)
        { 
          Serial.println("");
        }
        
        if(sampleNo%10 == 0)
        {  
          waitTime = 300 - ((currentTimeMs - aquireStartTimeMs)/1000) -1;
          displayData(waitTime);
        }
        
      }

      if ((currentTimeMs - aquireStartTimeMs) > UPLOAD_TIME)
      {
        aquireStartTimeMs = currentTimeMs;
        state = DATA_UPLOAD;
        displayData(500);
        Serial.println("");
        Serial.println("Data Will be uploaded..");
      }
      break;

    case DATA_UPLOAD:
      
      sampleNo = 0;
      
      
      Serial.println("Longitude:");
      Serial.print(Lon); Serial.println("");
      Serial.println("Latitiude:");
      Serial.print(Lat); Serial.println("");
      Serial.println("Altitude:");
      Serial.print(Alt); Serial.println("");
      Serial.println("Pressure:");
      Serial.print(Pressure); Serial.println("");
      Serial.println("Temperature:");
      Serial.print(Temp); Serial.println("");
      Serial.println("Humidity:");
      Serial.print(Humdty); Serial.println("");
      Serial.println("Carbon Monoxide:");
      Serial.print(CoStatus); Serial.println("");
      Serial.println("Air Quality:");
      Serial.print(AirQStatus); Serial.println("");

      UrlEncodedData = getUrlEncodedData();
      Serial.println(UrlEncodedData);

      sendHttpRequest(UrlEncodedData);


      tempAquired = pressureAquired = false;
      humidityAquired = false;
      coAquired = false;
      airqAquired = false;

      AirQAccumulation = 0;
      AirQSamples = 0;
      AirQStatus = 0.0;
      CoAccumulation = 0;
      CoSamples = 0;
      CoStatus = 0.0;
      displayData(1000);
      aquireStartTimeMs = millis();
      state = DATA_AQUIRE;
      break;


    default:

      break;
  }




}

bool sendHttpRequest(String object) {

  int objSize  = object.length();
  String objLength = String(objSize);
  int timeOut  = 0;
  int index = 0;
  String response  = "";

  Serial.println("Check GPRS connectivity by auto-detect APN setting");

  while (!LGPRS.attachGPRS("mobitel", "", ""))
  {
    delay(500);
    Serial.print('>');
    timeOut++;
    if (timeOut > 60)
    {
      Serial.println("");
      Serial.println("GPRS Attach failure..");
      break;
    }
  }
  if (client.connect(server, port)) {

    Serial.println(F("Server Connected..Data uploaded.."));

    client.println(F("POST /save_data.php HTTP/1.1"));
    client.print(F("Host: "));
    client.println(server);
    client.println(F("Content-Type: application/x-www-form-urlencoded"));
    client.print(F("Content-Length: "));
    client.println(objLength);
    client.println();
    client.println(object);
    client.println();

    Serial.print("Server Response:");
  }
  else
  {
    Serial.println("Connection to the Server airq.sltidc.lk failed..");
    return false;
  }

  while (client.connected()) {

    if (client.available() > 0) {
      char value = client.read();
      Serial.print(value);
    }

    if (!client.connected() || timeOut == 25000) {
      client.stop();
    }
    timeOut++;
  }

  return true;
}


String getUrlEncodedData()
{
  strDevID = String(devID);

  if (gpsStatus)
  {
    strLon = String(Lon);
    strLat = String(Lat);
  }
  else
  {
    strLon = "N/A";
    strLat = "N/A";
  }

  if (pressureAquired)
  {
    strAlt = String(Alt);
    strPressure = String(Pressure);
    strTmp = String(Temp);
  }
  else
  {
    strAlt = "N/A";
    strPressure = "N/A";
    strTmp = "N/A";
  }

  if (humidityAquired)
  {
    strHumdty = String(Humdty);
  }
  else
  {
    strHumdty = "N/A";
  }

  if (coAquired)
  {
    strCo = String(CoStatus);
  }
  else
  {
    strCo = "N/A";
  }

  if (airqAquired)
  {
    strAirq = String(AirQStatus);
  }
  else
  {
    strAirq = "N/A";
  }

  strDust = "N/A";
  strCo2 = "N/A";

  return "devID=" + strDevID + "&lon=" + strLon + "&lat=" + strLat
         + "&alt=" + strAlt + "&pres=" + strPressure + "&tmp=" + strTmp
         + "&hum=" + strHumdty + "&airq=" + strAirq + "&co=" + strCo
         + "&dust=" + strDust + "&co2=" + strCo2;

}

bool getTempAndPressure(void)
{
  float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
  float temperature;
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure)
  {
    Pressure = event.pressure;
    bmp.getTemperature(&temperature);
    Temp = temperature;
    Alt = bmp.pressureToAltitude(seaLevelPressure, Pressure);

    if (Temp != 0 &&  Pressure != 0)
    {
      return true;
    }
  }
}

bool getHumidity(void)
{
  float t = 0.0;
  float h = 0.0;

  if (dht.readHT(&t, &h))
  {
    Humdty = h;
    if (Humdty > 0)
    {
      return true;
    }
  }
  else
  {
    return false;
  }
}

bool getCO(void)
{
  COSensorValue = analogRead(analogCOPin);
  //CoStatus = map(COSensorValue, 0, 1023, 0, 255);
  CoAccumulation += COSensorValue;
  if (COSensorValue > 0)
  {
    CoSamples++;
    if (CoSamples > 0)
    {
      CoStatus = CoAccumulation / CoSamples;
    }
    return true;
  }
  else
  {
    return false;
  }


}

bool getAirQ(void)
{
  AirQSensorValue = analogRead(analogAirQPin);
  //AirQStatus = map(AirQSensorValue, 0, 1023, 0, 255);
  AirQAccumulation += AirQSensorValue;
  if (AirQSensorValue > 10 && AirQSensorValue < 800)
  {
    AirQSamples++;
    if (AirQSamples > 0)
    {
      AirQStatus = AirQAccumulation / AirQSamples;
    }
    return true;
  }
  else
  {
    return false;
  }

}
void Debug(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
  bmp.getEvent(&event);

  /* Display the results (barometric pressure is measure in hPa) */
  if (event.pressure)
  {
    /* Display atmospheric pressue in hPa */
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");


    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    /* Then convert the atmospheric pressure, and SLP to altitude         */
    /* Update this next line with the current SLP for better results      */
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:    ");
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure));
    Serial.println(" m");
    Serial.println("");

    Serial.println("LGPS loop");
    LGPS.getData(&info);
    Serial.println((char*)info.GPGGA);
    parseGPGGA((const char*)info.GPGGA);

    float t = 0.0;
    float h = 0.0;

    if (dht.readHT(&t, &h))
    {
      Serial.println("Humidity Loop");
      Serial.print("temperature = ");
      Serial.println(t);

      Serial.print("humidity = ");
      Serial.println(h);
    }
    else
    {
      Serial.println("DHT Not ready");
    }

    AirQSensorValue = analogRead(analogAirQPin);
    COSensorValue = analogRead(analogCOPin);
    // map it to the range of the analog out:
    AirQValue = map(AirQSensorValue, 0, 1023, 0, 255);
    COValue = map(COSensorValue, 0, 1023, 0, 255);

    Serial.print("AirQsensor = " );
    Serial.print(AirQSensorValue);
    Serial.print("\t output = ");
    Serial.println(AirQValue);
    Serial.print("COsensor = " );
    Serial.print(COSensorValue);
    Serial.print("\t output = ");
    Serial.println(COValue);
  }
  else
  {
    Serial.println("Sensor error");
  }
  delay(3000);


}

bool GpsReader(const char* GPGGAstr)
{
  double latitude;
  double longitude;
  int tmp, hour, minute, second, num ;
  if (GPGGAstr[0] == '$')
  {
    tmp = getComma(1, GPGGAstr);
    hour     = (GPGGAstr[tmp + 0] - '0') * 10 + (GPGGAstr[tmp + 1] - '0');
    minute   = (GPGGAstr[tmp + 2] - '0') * 10 + (GPGGAstr[tmp + 3] - '0');
    second    = (GPGGAstr[tmp + 4] - '0') * 10 + (GPGGAstr[tmp + 5] - '0');

    tmp = getComma(7, GPGGAstr);
    num = getIntNumber(&GPGGAstr[tmp]);
    NoOfSatelites = num;

    if (NoOfSatelites > 5)
    {
      tmp = getComma(2, GPGGAstr);
      latitude = getDoubleNumber(&GPGGAstr[tmp]);
      Lat = latitude;
      tmp = getComma(4, GPGGAstr);
      longitude = getDoubleNumber(&GPGGAstr[tmp]);
      Lon = longitude;
    }
    return true;
  }
  else
  {
    return false;
  }






}
bool Init(void)
{
  currentTimeMs = 0;
  prevTimeMs = 0;

  gpsStatus = false;
  gprsStatus = false;
  dataAquireStatus = false;
  dataUploadStatus = false;

  Lon = 0;
  Lat = 0;
  Alt = 0;
  Temp = 0;
  Humdty = 0;
  Pressure = 0;
  CoStatus = 0;
  AirQStatus = 0;

  NoOfSatelites = 0;

  humidityAquired = false;
  pressureAquired = false;
  tempAquired = false;
  coAquired = false;
  airqAquired = false;

  return true;

}
///////////////////////
static unsigned char getComma(unsigned char num, const char *str)
{
  unsigned char i, j = 0;
  int len = strlen(str);
  for (i = 0; i < len; i ++)
  {
    if (str[i] == ',')
      j++;
    if (j == num)
      return i + 1;
  }
  return 0;
}

static double getDoubleNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;

  i = getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev = atof(buf);
  return rev;
}

static double getIntNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;

  i = getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev = atoi(buf);
  return rev;
}

void parseGPGGA(const char* GPGGAstr)
{
  /* Refer to http://www.gpsinformation.org/dale/nmea.htm#GGA
   * Sample data: $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
   * Where:
   *  GGA          Global Positioning System Fix Data
   *  123519       Fix taken at 12:35:19 UTC
   *  4807.038,N   Latitude 48 deg 07.038' N
   *  01131.000,E  Longitude 11 deg 31.000' E
   *  1            Fix quality: 0 = invalid
   *                            1 = GPS fix (SPS)
   *                            2 = DGPS fix
   *                            3 = PPS fix
   *                            4 = Real Time Kinematic
   *                            5 = Float RTK
   *                            6 = estimated (dead reckoning) (2.3 feature)
   *                            7 = Manual input mode
   *                            8 = Simulation mode
   *  08           Number of satellites being tracked
   *  0.9          Horizontal dilution of position
   *  545.4,M      Altitude, Meters, above mean sea level
   *  46.9,M       Height of geoid (mean sea level) above WGS84
   *                   ellipsoid
   *  (empty field) time in seconds since last DGPS update
   *  (empty field) DGPS station ID number
   *  *47          the checksum data, always begins with *
   */
  double latitude;
  double longitude;
  int tmp, hour, minute, second, num ;
  if (GPGGAstr[0] == '$')
  {
    tmp = getComma(1, GPGGAstr);
    hour     = (GPGGAstr[tmp + 0] - '0') * 10 + (GPGGAstr[tmp + 1] - '0');
    minute   = (GPGGAstr[tmp + 2] - '0') * 10 + (GPGGAstr[tmp + 3] - '0');
    second    = (GPGGAstr[tmp + 4] - '0') * 10 + (GPGGAstr[tmp + 5] - '0');

    sprintf(buff, "UTC timer %2d-%2d-%2d", hour, minute, second);
    Serial.println(buff);

    tmp = getComma(2, GPGGAstr);
    latitude = getDoubleNumber(&GPGGAstr[tmp]);
    tmp = getComma(4, GPGGAstr);
    longitude = getDoubleNumber(&GPGGAstr[tmp]);
    sprintf(buff, "latitude = %10.4f, longitude = %10.4f", latitude, longitude);
    Serial.println(buff);

    tmp = getComma(7, GPGGAstr);
    num = getIntNumber(&GPGGAstr[tmp]);
    sprintf(buff, "satellites number = %d", num);
    Serial.println(buff);
  }
  else
  {
    Serial.println("Not get data");
  }
}






/**************************************************************************/
/*
    Setup
*/
/**************************************************************************/
void setup(void)
{
  Wire.begin();	
  SeeedGrayOled.init();  		         
  SeeedGrayOled.clearDisplay();                  
  SeeedGrayOled.drawBitmap(AeroQLogo,96*96/8); 
  delay(300);
  SeeedGrayOled.setNormalDisplay(); //Set Normal Display Mode
  SeeedGrayOled.setVerticalMode();
  SeeedGrayOled.setGrayLevel(13);
  
  SeeedGrayOled.setTextXY(5,0);
  SeeedGrayOled.putString("Status:"); 
  SeeedGrayOled.setTextXY(6,0);
  SeeedGrayOled.putString("DevID :1"); 
  SeeedGrayOled.setTextXY(7,0);
  SeeedGrayOled.putString("Temp  :");
  SeeedGrayOled.setTextXY(8,0);
  SeeedGrayOled.putString("AirQ  :");
  SeeedGrayOled.setTextXY(9,0);
  SeeedGrayOled.putString("Humdty:");
  SeeedGrayOled.setTextXY(10,0);
  SeeedGrayOled.putString("CO    :");
  SeeedGrayOled.setTextXY(11,0);
  SeeedGrayOled.putString("Dust  :N/A");
  
  Serial.begin(115200);

  //GPS Initialization
  LGPS.powerOn();
  Serial.println("LGPS Power on, and waiting ...");
  delay(5000);

  //DHT Sensor Initialization
  dht.begin();

  //BMP180 Initialization
  Serial.println("Pressure Sensor Test"); Serial.println("");

  /* Initialise the sensor */
  if (!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  /* Display some basic information on this sensor */
  displaySensorDetails();


  delay(5000);
  state = INIT;

}

void displayData(int sta)
{
  String strStatus;
  char caStatus[6];
  char caTmp[6];
  char caAirq[6];
  char caHumdty[6];
  char caCo[6];
  
  getUrlEncodedData();
  
  if(sta >= 0 && sta <= 300)
  {
    strStatus = String(sta);
    
  }else if (sta == 500)
  {
    strStatus = "Upldn";
    
  }else if(sta == 1000)
  {
    strStatus = "OK";
    
  }else if(sta == 1500)
  {
    strStatus = "GPSERR";
    
  }else if(sta == 2000)
  {
    strStatus = "GPSOK";
    
  }else if(sta <= 20)
  {
    strStatus = "GPS" + String(sta); 
  }
  
  strStatus.toCharArray(caStatus,6);
  strTmp.toCharArray(caTmp,6);
  strAirq.toCharArray(caAirq,6);
  strHumdty.toCharArray(caHumdty,6);
  strCo.toCharArray(caCo,6);
  
  SeeedGrayOled.setTextXY(5,7);
  SeeedGrayOled.putString("      ");
  SeeedGrayOled.setTextXY(5,7);
  SeeedGrayOled.putString(caStatus);
  
  SeeedGrayOled.setTextXY(7,7);
  SeeedGrayOled.putString(caTmp);
  SeeedGrayOled.setTextXY(8,7);
  SeeedGrayOled.putString(caAirq);
  SeeedGrayOled.setTextXY(9,7);
  SeeedGrayOled.putString(caHumdty);
  SeeedGrayOled.setTextXY(10,7);
  SeeedGrayOled.putString(caCo);
}  

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{

  RunSystem();

  //  /* Get a new sensor event */
  //  sensors_event_t event;
  //  bmp.getEvent(&event);
  //
  //  /* Display the results (barometric pressure is measure in hPa) */
  //  if (event.pressure)
  //  {
  //    /* Display atmospheric pressue in hPa */
  //    Serial.print("Pressure:    ");
  //    Serial.print(event.pressure);
  //    Serial.println(" hPa");
  //
  //
  //    float temperature;
  //    bmp.getTemperature(&temperature);
  //    Serial.print("Temperature: ");
  //    Serial.print(temperature);
  //    Serial.println(" C");
  //
  //    /* Then convert the atmospheric pressure, and SLP to altitude         */
  //    /* Update this next line with the current SLP for better results      */
  //    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
  //    Serial.print("Altitude:    ");
  //    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
  //                                        event.pressure));
  //    Serial.println(" m");
  //    Serial.println("");
  //
  //    Serial.println("LGPS loop");
  //    LGPS.getData(&info);
  //    Serial.println((char*)info.GPGGA);
  //    parseGPGGA((const char*)info.GPGGA);
  //
  //    float t = 0.0;
  //    float h = 0.0;
  //
  //    if(dht.readHT(&t, &h))
  //    {
  //        Serial.println("Humidity Loop");
  //        Serial.print("temperature = ");
  //        Serial.println(t);
  //
  //        Serial.print("humidity = ");
  //        Serial.println(h);
  //    }
  //    else
  //    {
  //        Serial.println("DHT Not ready");
  //    }
  //
  //      AirQSensorValue = analogRead(analogAirQPin);
  //    COSensorValue = analogRead(analogCOPin);
  //  // map it to the range of the analog out:
  //  AirQValue = map(AirQSensorValue, 0, 1023, 0, 255);
  //    COValue = map(COSensorValue, 0, 1023, 0, 255);
  //
  //    Serial.print("AirQsensor = " );
  //  Serial.print(AirQSensorValue);
  //  Serial.print("\t output = ");
  //  Serial.println(AirQValue);
  //    Serial.print("COsensor = " );
  //  Serial.print(COSensorValue);
  //  Serial.print("\t output = ");
  //  Serial.println(COValue);
  //  }
  //  else
  //  {
  //    Serial.println("Sensor error");
  //  }
  //  delay(3000);
}
