#define dirpin 2
#define steppin 3

#define STEP_SIZE 255 //x10-7m
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>


Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void configureSensor(void){
  tsl.enableAutoRange(true); 
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS); 
}

void setup() {
  pinMode (dirpin,OUTPUT);
  pinMode (steppin,OUTPUT);
     
  Serial.begin(9600);
  if(!tsl.begin()){
    /* There was a problem detecting the TSL2561 ... check your connections */
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  /* Setup the sensor gain and integration time */
  configureSensor();
  
}

int i;
void loop() {
  i=0;
  digitalWrite(dirpin,LOW);
  delay(500);
  for(i=0;i<1000;i++){
    digitalWrite(steppin,LOW);
    digitalWrite(steppin,HIGH);
    SensorReadandReport(i);
    delayMicroseconds(10000);
  }
  
  digitalWrite (dirpin,HIGH);
  delay(500);
  for(i=0;i<1000;i++){
    digitalWrite(steppin,LOW);
    digitalWrite(steppin,HIGH);
    SensorReadandReport(1000-i);
    delayMicroseconds(10000);
  }
}

void SensorReadandReport(int steps){
  sensors_event_t event;
  tsl.getEvent(&event);
 
  /* Display the results (light is measured in lux) */
  if (event.light){
    Serial.print(steps);
    Serial.print("E-7");    
    Serial.print(",");
    Serial.println(event.light);
    
  }else{
    /* If event.light = 0 lux the sensor is probably saturated
       and no reliable data could be generated! */
    Serial.println("Sensor overload");
  }
  delay(250);
}
