#include <Arduino.h>
#include <string.h>

typedef struct
{
  int* wrt;
  int* read;
  int set[20];
}C_buffer;
C_buffer buffer;
int mockSensorData = 0;
unsigned long lastwritetime = 0;
const unsigned long writeInterval = 200; 
unsigned long lastReadTime = 0;
const unsigned long readInterval = 300;  


void setup() {
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  buffer.wrt = &(buffer.set[0]);
  buffer.read = &(buffer.set[0]);
}

void loop() {
 unsigned long now = millis();
 if(now - lastwritetime >= writeInterval){
  mockSensorData++;
  *buffer.wrt = mockSensorData;
  buffer.wrt++;
  lastwritetime = now;
  if(buffer.wrt == &(buffer.set[20])){
    buffer.wrt = &(buffer.set[0]);
  }
  if(buffer.wrt == buffer.read){
  buffer.read++;
  if(buffer.read == &(buffer.set[20])) {
    buffer.read = &(buffer.set[0]);
  }
}
 }
 if(buffer.read != buffer.wrt  && now - lastReadTime >= readInterval){
  Serial.println(*buffer.read);
  buffer.read++;
  if(buffer.read == &(buffer.set[20])){
    buffer.read = &(buffer.set[0]);
  }
  lastReadTime = now;
 }

}
