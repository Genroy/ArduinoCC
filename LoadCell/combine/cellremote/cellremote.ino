#include "HX711.h"
#include "IRremote.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);

#define zero_factor 8488625
#define DOUT  A3
#define CLK   A2
#define DEC_POINT  2

float calibration_factor = 92410.00; 
float offset=0;
float get_units_kg();
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;

float receive = 0;

static float change = 0;
static float showcr = 0;

HX711 scale(DOUT, CLK);

void setup() 
{
  Serial.begin(115200);
  irrecv.enableIRIn();
  lcd.begin();
  lcd.print("Loading Cell");
  Serial.println("Load Cell");
  scale.set_scale(calibration_factor); 
  scale.set_offset(zero_factor); 
  delay(2000);
  lcd.clear();
    
}

void loop() 
{ 

String data = String(get_units_kg()+offset, DEC_POINT);
float x = data.toFloat();
receive = x;

showcr = receive + change;

remote();

if(x <=0)
{
lcd.print("Reading : ");
lcd.setCursor(0, 1);
lcd.print(receive);
lcd.print(" *KG.          ");

}
else
{ 
lcd.print("Reading : ");
lcd.setCursor(0, 1);
lcd.print(showcr);
lcd.print(" *KG.          ");
}

}//loop

void remote()
{

  if (irrecv.decode(&results)) {
    
   //Serial.println(results.value);

    if(results.value == 3810010651)
    {
      change = 1;
    }

    if(results.value == 5316027)
    {
      change = 2;
    }

    if(results.value == 4001918335)
    {
      change = 0;
    }
   
    irrecv.resume(); // Receive the next value
    
  }
  
}//remote

float get_units_kg()
{
  return(scale.get_units()*0.453592);
 
}
