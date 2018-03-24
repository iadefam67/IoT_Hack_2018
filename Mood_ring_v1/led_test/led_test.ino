/*
Adafruit Arduino - Lesson 3. RGB LED
*/
 
int redPin = 4;
int greenPin = 5;
int bluePin = 2;
 
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}
 
void loop()

//take a sample
//if sample is in a range, assign to r value (maybe another switch table)
{
  switch (range) {
   
    case r0:
      //Good: Green 
      setColor(0, 255, 0);
      delay(1000);
      break;
      
    case r1:
      //Moderate, yellow
      setColor(255, 255, 0);  
      delay(1000);
      break;
      
    case r2:
      //Unhealthy for Sensitive Groups (USG) 
      // orange
      break;
      
    case r3:
      //Very Unhealthy
      setColor(80, 0, 80);  // purple
      delay(1000);
      break;
      
    case r4:
      //Hazardous 
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
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
