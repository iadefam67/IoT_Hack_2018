/*
Adafruit Arduino - Lesson 3. RGB LED
*/
 
int redPin = 4;
int greenPin = 5;
int bluePin = 2;
 

int range;
  
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
 
void loop()

{
  for (int i = 0; i < 6; ++i) {
      range = i;
      delay(1000);    
  }


//  digitalWrite(redPin, 1);
//  digitalWrite(greenPin, 0);
//  digitalWrite(bluePin, 1);
    analogWrite(redPin, 0);
    analogWrite(greenPin, 1023);
    analogWrite(bluePin, 1023);
 
  switch (range) {
   
    case 0:
      //Good: Green 
      setColor(0, 1023, 0);
      delay(1000);
      break;
      
    case 1:
      //Moderate: Yellow
      setColor(1023, 1023, 0);  
      delay(1000);
      break;
      
    case 2:
      //Unhealthy for Sensitive Groups (USG): Orange
      setColor(1023, 300, 100);
      delay(1000);
      break;

    case 3:
      //Unhealthy: Red
      setColor(1023, 0, 0);
      delay(1000);
      break;
      
    case 4:
      //Very Unhealthy: Purple
      setColor(900, 0, 1023); 
      delay(1000);
      break;
      
    case 5:
      //Hazardous
      setColor(1023, 0, 1023);
      delay(1000);
      //darkest possible color
      break;
    default:
      //set default color? some sort of randomizer?
      break; 
      
  }
  
}
 //4B0082
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 1023 - red;
    green = 1023 - green;
    blue = 1023 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
