#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define aqi_sensor A0
#define touch_sensor 3

float aqi_value, heartrate, spo2, temperature;
int patientID;

#define SS_PIN 10  //D10
#define RST_PIN 9 //D9
#include <SPI.h>
#include <MFRC522.h>
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

namespace
{
const char * USER_AGENT = "UbidotsESP8266"; // Assgin the user agent
const char * VERSION =  "1.0"; // Assign the version
const char * METHOD = "POST"; // Set the method
const char * TOKEN = "BBUS-JprTUzNeRtGegCdcmNn3YZ5fQPwavO"; // Assign your Ubidots TOKEN
const char * DEVICE_LABEL = "Nursing robot"; // Assign the device label
const char * VARIABLE_LABEL1 = "Temperature"; // Assign the variable label
const char * VARIABLE_LABEL2 = "AQI"; // Assign the variable label
const char * VARIABLE_LABEL3 = "Heartrate"; // Assign the variable label
const char * VARIABLE_LABEL4 = "SpO2"; // Assign the variable label
const char * VARIABLE_LABEL5 = "PatientID"; // Assign the variable label

}

char str_sensor1[10];
char str_sensor2[10];
char str_sensor3[10];
char str_sensor4[10];
char str_sensor5[10];
void setup(void)
{
  Serial.begin(9600);
  pinMode(aqi_sensor, INPUT);
  pinMode(touch_sensor, INPUT);
  dht.begin();
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Nursing Health");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Monitoring Robot");
  delay(500);
}

void loop(void)
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println(content);
  if (content.substring(1) == "C3 72 06 A6")
  {
    patientID = 1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Patient: Ramesh");
    lcd.setCursor(0, 1);
    lcd.print("Have a Nice day");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pls Hold Temperature");
    lcd.setCursor(0, 1);
    lcd.print("sensors Tightly");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reading Sensors");
    lcd.setCursor(0, 1);
    lcd.print("       9        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       8        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       7        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       6        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       5        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       4        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       3        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       2        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       1        ");
    delay(500);
    float  humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(temperature);
    lcd.print(" *C");
    delay(500);
    //*******************************************************************************
    aqi_value = analogRead(aqi_sensor);
    aqi_value = map(aqi_value, 0, 100, 0, 255);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Air Quality Index");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(aqi_value);
    lcd.print(" %");
    delay(500);
    //*******************************************************************************

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pls place finger   ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("Pulseoximeter Sensor");
    delay(500);
    while (digitalRead(touch_sensor) == LOW)
    {
      heartrate = read.pulse( );
      spo2 = read.spo2( );
    }
    heartrate = read.pulse( );
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reading Sensors");
    lcd.setCursor(0, 1);
    lcd.print("       9        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       8        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       7        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       6        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       5        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       4        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       3        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       2        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       1        ");
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heartrate");
    lcd.setCursor(0, 1);
    lcd.print(heartrate);
    lcd.print(" BPM");
    delay(1000);
    spo2 = read.spo2( );
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SpO2");
    lcd.setCursor(0, 1);
    lcd.print(spo2);
    lcd.print(" %");
    delay(1000);
    //******************************************************************************
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sending data IOT");
    //****************************************************************************************************
    char* command5 = (char *) malloc(sizeof(char) * 128);
    float sensor5 = patientID;
    dtostrf(sensor5, 4, 2, str_sensor5);
    sprintf(command5, "init#");
    sprintf(command5, "%s%s/%s|%s|%s|", command5, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command5, "%s%s=>", command5, DEVICE_LABEL);
    sprintf(command5, "%s%s:%s", command5, VARIABLE_LABEL5, str_sensor5);
    sprintf(command5, "%s|end#final", command5);
    Serial.print(command5);
    free(command5);
    delay(2000);
    //***************************************************************************************************
    char* command1 = (char *) malloc(sizeof(char) * 128);
    float sensor1 = temperature;
    dtostrf(sensor1, 4, 2, str_sensor1);
    sprintf(command1, "init#");
    sprintf(command1, "%s%s/%s|%s|%s|", command1, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command1, "%s%s=>", command1, DEVICE_LABEL);
    sprintf(command1, "%s%s:%s", command1, VARIABLE_LABEL1, str_sensor1);
    sprintf(command1, "%s|end#final", command1);
    Serial.print(command1);// uncomment this line to print the command
    free(command1);
    delay(2000);
    //*********************************************************
    char* command2 = (char *) malloc(sizeof(char) * 128);
    float sensor2 = aqi_value;
    dtostrf(sensor2, 4, 2, str_sensor2);
    sprintf(command2, "init#");
    sprintf(command2, "%s%s/%s|%s|%s|", command2, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command2, "%s%s=>", command2, DEVICE_LABEL);
    sprintf(command2, "%s%s:%s", command2, VARIABLE_LABEL2, str_sensor2);
    sprintf(command2, "%s|end#final", command2);
    Serial.print(command2);// uncomment this line to print the command
    free(command2);
    delay(2000);
    //**********************************************************
    char* command3 = (char *) malloc(sizeof(char) * 128);
    float sensor3 = heartrate;
    dtostrf(sensor3, 4, 2, str_sensor3);
    sprintf(command3, "init#");
    sprintf(command3, "%s%s/%s|%s|%s|", command3, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command3, "%s%s=>", command3, DEVICE_LABEL);
    sprintf(command3, "%s%s:%s", command3, VARIABLE_LABEL3, str_sensor3);
    sprintf(command3, "%s|end#final", command3);
    Serial.print(command3);// uncomment this line to print the command
    free(command3);
    delay(2000);
    //****************************************************************************************************
    char* command4 = (char *) malloc(sizeof(char) * 128);
    float sensor4 = spo2;
    dtostrf(sensor4, 4, 2, str_sensor4);
    sprintf(command4, "init#");
    sprintf(command4, "%s%s/%s|%s|%s|", command4, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command4, "%s%s=>", command4, DEVICE_LABEL);
    sprintf(command4, "%s%s:%s", command4, VARIABLE_LABEL4, str_sensor4);
    sprintf(command4, "%s|end#final", command4);
    Serial.print(command4);
    free(command4);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Data Sent ");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Place the RFID Reader");
    delay(500);
  }
  else if (content.substring(1) == "73 CF 63 A6")
  {
    patientID = 2;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Patient: Suresh");
    lcd.setCursor(0, 1);
    lcd.print("Have a Nice day");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pls Hold Temperature");
    lcd.setCursor(0, 1);
    lcd.print("sensors Tightly");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reading Sensors");
    lcd.setCursor(0, 1);
    lcd.print("       9        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       8        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       7        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       6        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       5        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       4        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       3        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       2        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       1        ");
    delay(500);
    float  humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(temperature);
    lcd.print(" *C");
    delay(500);
    //*******************************************************************************
    aqi_value = analogRead(aqi_sensor);
    aqi_value = map(aqi_value, 0, 100, 0, 255);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Air Quality Index");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(aqi_value);
    lcd.print(" %");
    delay(500);
    //*******************************************************************************

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pls place finger   ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("Pulseoximeter Sensor");
    delay(500);
    while (digitalRead(touch_sensor) == LOW)
    {
      heartrate = read.pulse( );
      spo2 = read.spo2( );
    }
    heartrate = read.pulse( );
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reading Sensors");
    lcd.setCursor(0, 1);
    lcd.print("       9        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       8        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       7        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       6        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       5        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       4        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       3        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       2        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       1        ");
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heartrate");
    lcd.setCursor(0, 1);
    lcd.print(heartrate);
    lcd.print(" BPM");
    delay(1000);
    spo2 = read.spo2( );
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SpO2");
    lcd.setCursor(0, 1);
    lcd.print(spo2);
    lcd.print(" %");
    delay(1000);
    //******************************************************************************
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sending data IOT");
    char* command5 = (char *) malloc(sizeof(char) * 128);
    float sensor5 = patientID;
    dtostrf(sensor5, 4, 2, str_sensor5);
    sprintf(command5, "init#");
    sprintf(command5, "%s%s/%s|%s|%s|", command5, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command5, "%s%s=>", command5, DEVICE_LABEL);
    sprintf(command5, "%s%s:%s", command5, VARIABLE_LABEL5, str_sensor5);
    sprintf(command5, "%s|end#final", command5);
    Serial.print(command5);
    free(command5);
    delay(2000);

    char* command1 = (char *) malloc(sizeof(char) * 128);
    float sensor1 = temperature;
    dtostrf(sensor1, 4, 2, str_sensor1);
    sprintf(command1, "init#");
    sprintf(command1, "%s%s/%s|%s|%s|", command1, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command1, "%s%s=>", command1, DEVICE_LABEL);
    sprintf(command1, "%s%s:%s", command1, VARIABLE_LABEL1, str_sensor1);
    sprintf(command1, "%s|end#final", command1);
    Serial.print(command1);// uncomment this line to print the command
    free(command1);
    delay(2000);
    //*********************************************************
    char* command2 = (char *) malloc(sizeof(char) * 128);
    float sensor2 = aqi_value;
    dtostrf(sensor2, 4, 2, str_sensor2);
    sprintf(command2, "init#");
    sprintf(command2, "%s%s/%s|%s|%s|", command2, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command2, "%s%s=>", command2, DEVICE_LABEL);
    sprintf(command2, "%s%s:%s", command2, VARIABLE_LABEL2, str_sensor2);
    sprintf(command2, "%s|end#final", command2);
    Serial.print(command2);// uncomment this line to print the command
    free(command2);
    delay(2000);
    //**********************************************************
    char* command3 = (char *) malloc(sizeof(char) * 128);
    float sensor3 = heartrate;
    dtostrf(sensor3, 4, 2, str_sensor3);
    sprintf(command3, "init#");
    sprintf(command3, "%s%s/%s|%s|%s|", command3, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command3, "%s%s=>", command3, DEVICE_LABEL);
    sprintf(command3, "%s%s:%s", command3, VARIABLE_LABEL3, str_sensor3);
    sprintf(command3, "%s|end#final", command3);
    Serial.print(command3);// uncomment this line to print the command
    free(command3);
    delay(2000);
    //****************************************************************************************************
    char* command4 = (char *) malloc(sizeof(char) * 128);
    float sensor4 = spo2;
    dtostrf(sensor4, 4, 2, str_sensor4);
    sprintf(command4, "init#");
    sprintf(command4, "%s%s/%s|%s|%s|", command4, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command4, "%s%s=>", command4, DEVICE_LABEL);
    sprintf(command4, "%s%s:%s", command4, VARIABLE_LABEL4, str_sensor4);
    sprintf(command4, "%s|end#final", command4);
    Serial.print(command4);
    free(command4);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Data Sent ");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Place the RFID Reader");
    delay(500);
  }
  else if (content.substring(1) == "F3 D0 D4 A5")
  {
    patientID = 3;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Patient: Mahesh");
    lcd.setCursor(0, 1);
    lcd.print("Have a Nice day");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pls Hold Temperature");
    lcd.setCursor(0, 1);
    lcd.print("sensors Tightly");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reading Sensors");
    lcd.setCursor(0, 1);
    lcd.print("       9        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       8        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       7        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       6        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       5        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       4        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       3        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       2        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       1        ");
    delay(500);
    float  humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(temperature);
    lcd.print(" *C");
    delay(500);
    //*******************************************************************************
    aqi_value = analogRead(aqi_sensor);
    aqi_value = map(aqi_value, 0, 100, 0, 255);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Air Quality Index");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print(aqi_value);
    lcd.print(" %");
    delay(500);
    //*******************************************************************************

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pls place finger   ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("Pulseoximeter Sensor");
    delay(500);
    while (digitalRead(touch_sensor) == LOW)
    {
      heartrate = read.pulse( );
      spo2 = read.spo2( );
    }
    heartrate = read.pulse( );
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reading Sensors");
    lcd.setCursor(0, 1);
    lcd.print("       9        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       8        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       7        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       6        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       5        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       4        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       3        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       2        ");
    delay(500);
    lcd.setCursor(0, 1);
    lcd.print("       1        ");
    delay(500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heartrate");
    lcd.setCursor(0, 1);
    lcd.print(heartrate);
    lcd.print(" BPM");
    delay(1000);
    spo2 = read.spo2( );
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SpO2");
    lcd.setCursor(0, 1);
    lcd.print(spo2);
    lcd.print(" %");
    delay(1000);
    //******************************************************************************
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sending data IOT");
    char* command5 = (char *) malloc(sizeof(char) * 128);
    float sensor5 = patientID;
    dtostrf(sensor5, 4, 2, str_sensor5);
    sprintf(command5, "init#");
    sprintf(command5, "%s%s/%s|%s|%s|", command5, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command5, "%s%s=>", command5, DEVICE_LABEL);
    sprintf(command5, "%s%s:%s", command5, VARIABLE_LABEL5, str_sensor5);
    sprintf(command5, "%s|end#final", command5);
    Serial.print(command5);
    free(command5);
    delay(2000);
    //*********************************************************
    char* command1 = (char *) malloc(sizeof(char) * 128);
    float sensor1 = temperature;
    dtostrf(sensor1, 4, 2, str_sensor1);
    sprintf(command1, "init#");
    sprintf(command1, "%s%s/%s|%s|%s|", command1, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command1, "%s%s=>", command1, DEVICE_LABEL);
    sprintf(command1, "%s%s:%s", command1, VARIABLE_LABEL1, str_sensor1);
    sprintf(command1, "%s|end#final", command1);
    Serial.print(command1);// uncomment this line to print the command
    free(command1);
    delay(2000);
    //*********************************************************
    char* command2 = (char *) malloc(sizeof(char) * 128);
    float sensor2 = aqi_value;
    dtostrf(sensor2, 4, 2, str_sensor2);
    sprintf(command2, "init#");
    sprintf(command2, "%s%s/%s|%s|%s|", command2, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command2, "%s%s=>", command2, DEVICE_LABEL);
    sprintf(command2, "%s%s:%s", command2, VARIABLE_LABEL2, str_sensor2);
    sprintf(command2, "%s|end#final", command2);
    Serial.print(command2);// uncomment this line to print the command
    free(command2);
    delay(2000);
    //**********************************************************
    char* command3 = (char *) malloc(sizeof(char) * 128);
    float sensor3 = heartrate;
    dtostrf(sensor3, 4, 2, str_sensor3);
    sprintf(command3, "init#");
    sprintf(command3, "%s%s/%s|%s|%s|", command3, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command3, "%s%s=>", command3, DEVICE_LABEL);
    sprintf(command3, "%s%s:%s", command3, VARIABLE_LABEL3, str_sensor3);
    sprintf(command3, "%s|end#final", command3);
    Serial.print(command3);// uncomment this line to print the command
    free(command3);
    delay(2000);
    //****************************************************************************************************
    char* command4 = (char *) malloc(sizeof(char) * 128);
    float sensor4 = spo2;
    dtostrf(sensor4, 4, 2, str_sensor4);
    sprintf(command4, "init#");
    sprintf(command4, "%s%s/%s|%s|%s|", command4, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command4, "%s%s=>", command4, DEVICE_LABEL);
    sprintf(command4, "%s%s:%s", command4, VARIABLE_LABEL4, str_sensor4);
    sprintf(command4, "%s|end#final", command4);
    Serial.print(command4);
    free(command4);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Data Sent ");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Place the RFID Reader");
    delay(500);
  }
}
