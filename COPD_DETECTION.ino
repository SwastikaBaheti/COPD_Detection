#include <LiquidCrystal.h>
int Contrast=90;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/*Below contains hypothetical values. You can insert the threshold values according to your analysis*/
const int LOWER_THRESHOLD_MQ3 = 3;
const int HIGHER_THRESHOLD_MQ3 = 8;
const int LOWER_THRESHOLD_MQ7 = 2;
const int HIGHER_THRESHOLD_MQ7 = 7;

const int mq3 = 0;
const int mq7 = 1;
float mq3_value;
float mq7_value;

void setup ()
{
  Serial.begin (115200) ;
  pinMode(mq3, INPUT);
  pinMode(mq7, INPUT);
  analogWrite(6, Contrast);
  lcd.begin(16, 2);
}

void loop ()
{
  mq3_value = analogRead(mq3) ;
  mq3_value = (mq3_value*10)/1023;
  Serial.print("MQ3 Sensor value: ");
  Serial.println(mq3_value) ;
  
  mq7_value= analogRead (mq7) ;
  Serial.print("MQT Sensor value: ");
  Serial.println(mq7_value);

  lcd.setCursor (0, 0); 

  if (mq3_value <= LOWER_THRESHOLD_MQ3 && mq7_value <= LOWER_THRESHOLD_MQ7) {
    lcd.clear();
    lcd.print("Healthy");
  } 
  else if ((mq3_value > LOWER_THRESHOLD_MQ3 && mq3_value <= HIGHER_THRESHOLD_MQ3) || (mq7_value > LOWER_THRESHOLD_MQ7 && mq7_value <= HIGHER_THRESHOLD_MQ7)) {
    lcd.clear();
    lcd.print("Chances of Lung Diseases");
  } 
  else if (mq3_value > HIGHER_THRESHOLD_MQ3 || mq7_value > HIGHER_THRESHOLD_MQ7) {
    lcd.clear();
    lcd.print("COPD Detected");
  }
}
