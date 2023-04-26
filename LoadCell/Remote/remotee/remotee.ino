#include "IRremote.h"

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;


void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    
   //Serial.println(results.value);

    if(results.value == 3810010651)
    {
      Serial.println("1");
    }

    if(results.value == 5316027)
    {
      Serial.println("2");
    }

    if(results.value == 4001918335)
    {
      Serial.println("3");
    }

    if(results.value == 1386468383)
    {
      Serial.println("4");
    }

    if(results.value == 3622325019)
    {
      Serial.println("5");
    }
   
    irrecv.resume(); // Receive the next value
    
  }


  
  
}
