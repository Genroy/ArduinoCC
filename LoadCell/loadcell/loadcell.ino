#include "HX711.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);

float calibration_factor = 92410.00; 
#define zero_factor 8488625
#define DOUT  A3
#define CLK   A2
#define DEC_POINT  2

float offset=0;
float get_units_kg();

HX711 scale(DOUT, CLK);

void setup() 
{
  Serial.begin(115200);
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
static float a;


float x = data.toFloat();

lcd.print("Reading : ");
lcd.setCursor(0, 1);
lcd.print(x);
lcd.print(" *KG.          ");


}
float get_units_kg()
{
  return(scale.get_units()*0.453592);
  
}
