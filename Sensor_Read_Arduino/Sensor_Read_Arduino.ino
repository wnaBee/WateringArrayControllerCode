#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
float reqAhum = 0;
float reqtemp = 0;
float reqShum = 0;
float ActiveTime = 0;
float InActiveTime = 0;
String locale[] = {"meny","temperature","Soil humidity","Air humidity","Active time","Inactive time"};
int clocale = 0;
int Mpos = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.print("Input in order, deliniate with \\n: top Air humidity, top Soil humidity, minimum temperature \nactive time, inactive time \n");
  while( reqAhum == 0 || reqShum == 0 || reqtemp == 0 || ActiveTime == 0 || InActiveTime == 0){
    if(reqAhum == 0){
      while(Serial.available() == 0){}
      reqAhum = Serial.parseFloat();
    }else if(reqShum == 0){
      while(Serial.available() == 0){}
      reqShum = Serial.parseFloat();
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
  Serial.print("Required Air Humidity: ");
  Serial.print(reqAhum); 
  Serial.print("%  |  Required Soil Humidity: ");
  Serial.print(reqShum);
  Serial.print("%  |  Required Temperature: ");
  Serial.print(reqtemp);
  Serial.print(" °C");

  Serial.print("\nSpraying time: ");
  Serial.print(ActiveTime/1000); 
  Serial.print(" s  |  Spraying Pause: ");
  Serial.print(InActiveTime/1000); 
  Serial.print(" s");
  
  //initialize
  Serial.print("\nInitializing");
  for(int i = 0; i < 3; i++){
    Serial.print(".");
    delay(1000);
    }
  Serial.print("\n");
}

int menu(){
    //down
    if(digitalRead(4) == HIGH){
      //Serial.print(digitalRead(4));
      switch(clocale){
        case 0:
          //menu
          Mpos--;
          if(Mpos < 0){Mpos = 5;}
          Serial.print(locale[Mpos]);
          break;
        case 1:
          //temperature
          reqtemp--;
          Serial.print(reqtemp);
          break;
        case 2:
          //soil humidity
          reqShum--;
          Serial.print(reqShum);
          break;
        case 3:
          //Air humidity
          reqAhum--;
          Serial.print(reqAhum);
          break;
        case 4:
          //active time
          ActiveTime -= 1000;
          Serial.print(ActiveTime/1000);
          break;
        case 5:
          //inactive time
          InActiveTime -= 1000;
          Serial.print(InActiveTime/1000);
          break;
        }
        Serial.print("\n");
        delay(1000);
    }
    //confirm
    if(digitalRead(5) == HIGH){
      Serial.print("entered\n");
      //Serial.print(digitalRead(5));
      switch(clocale){
        case 0:
          //menu
          clocale = Mpos;
          break;
        case 1:
          //temperature
          clocale = 0;
          break;
        case 2:
          //Soil humidity
          clocale = 0;
          break;
        case 3:
          //Air humidity
          clocale = 0;
          break;
        case 4:
          //Active time
          clocale = 0;
          break;
        case 5:
          //Inactive time
          clocale = 0;
          break;
        }
        Serial.print(locale[Mpos]);
        Serial.print("\n");
        delay(1000);
      }
    //up
    if(digitalRead(6) == HIGH){
      //Serial.print(digitalRead(6));
      switch(clocale){
        case 0:
          //menu
          Mpos++;
          if(Mpos > 5){Mpos = 0;}
          Serial.print(locale[Mpos]);
          break;
        case 1:
          //temperature
          reqtemp++;
          Serial.print(reqtemp);
          break;
        case 2:
          //soil humidity
          reqShum++;
          Serial.print(reqShum);
          break;
        case 3:
          //air humidity
          reqAhum++;
          Serial.print(reqAhum);
          break;
        case 4:
          //active time
          ActiveTime += 1000;
          Serial.print(ActiveTime/1000);
          break;
        case 5:
          //inactive time
          InActiveTime += 1000;
          Serial.print(InActiveTime/1000);
          break;
        }
        Serial.print("\n");
        delay(1000);
    }
    return 0;
  }

void loop() {
  //main body
    menu();
    float hum = dht.readHumidity();
    float Shum = dht.readHumidity();
    float temp = dht.readTemperature();
    
    
    //verify integrity
    if (isnan(hum) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor");
    } else {
    
      //print situation
/*
      Serial.print("Humidity: ");
      Serial.print(hum);
      Serial.print("%");
  
      Serial.print("  |  "); 
  
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print("°C\n");
*/
      //water
      if(temp > reqtemp || hum < reqAhum || Shum < reqShum){
        Serial.print("watering\n");
        float initTime = millis();
        while(millis()-initTime < ActiveTime){menu();}
        Serial.print("done\n");
        initTime = millis();
        while(millis()-initTime < InActiveTime){menu();}
      }
   }
}
