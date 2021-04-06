#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
float reqhum = 0;
float reqtemp = 0;
float ActiveTime = 0;
float InActiveTime = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  while( reqhum == 0 || reqtemp == 0 || ActiveTime == 0 || InActiveTime == 0){
    if(reqhum == 0){
      while(Serial.available() == 0){}
      reqhum = Serial.parseFloat();
    }else if(reqtemp == 0){
      while(Serial.available() == 0){}
      reqtemp = Serial.parseFloat();
    }else if(ActiveTime == 0){
      while(Serial.available() == 0){}
      ActiveTime = Serial.parseFloat()*1000;
    }else if(InActiveTime == 0){
      while(Serial.available() == 0){}
      InActiveTime = Serial.parseFloat()*1000;
    }
  }
  //confirm user choices
  Serial.print("Required Humidity: ");
  Serial.print(reqhum);
  Serial.print("%"); 
  Serial.print("  |  ");
  Serial.print("Required Temperature: ");
  Serial.print(reqtemp);
  Serial.print(" °C");

  Serial.print("\nSpraying time: ");
  Serial.print(ActiveTime/1000);
  Serial.print(" s"); 
  Serial.print("  |  ");
  Serial.print("Spraying Pause: ");
  Serial.print(InActiveTime/1000); 
  Serial.print(" s");
  
  //initialize
  Serial.print("\nInitializing");
  for(int i = 0; i < 3; i++){
    Serial.print(".");
    delay(1000);
    }
  Serial.print("\n");
  
  //main body
  while(1==1){
    float hum = dht.readHumidity();
    float temp = dht.readTemperature();
    
    //verify integrity
    if (isnan(hum) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
    
      //print situation
      Serial.print("Humidity: ");
      Serial.print(hum);
      Serial.print("%");
  
      Serial.print("  |  "); 
  
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print("°C\n");

      //water
      if(temp > reqtemp || hum < reqhum){
        Serial.print("watering\n");
        float initTime = millis();
        while(millis()-initTime < ActiveTime){}
        Serial.print("done\n");
        initTime = millis();
        while(millis()-initTime < InActiveTime){}
      }
    }
  }
}
