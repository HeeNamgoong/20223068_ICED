#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 0 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10
#define PIN_LED  9

#define _DUTY_MIN 520  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1460 // servo neutral position (90 degree)
#define _DUTY_MAX 2400 // servo full counter-clockwise position (180 degree)

#define DIST_MIN 100.0
#define DIST_MAX 250.0



#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)

#define _EMA_ALPHA 0.3    // EMA weight of new sample (range: 0 to 1)

Servo myservo;
unsigned long last_loop_time;   // unit: msec
unsigned long dist, dist_ema, dist_prev;

void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  
  Serial.begin(57600);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return ;
  last_loop_time += LOOP_INTERVAL;

  

 
  // Read IR Sensor value !!!
    a_value = analogRead(PIN_POTENTIOMETER);
  
  // Convert IR sensor value into distance !!!
    dist = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;

  // we need distance range filter here !!!


  if (dist < DIST_MIN) {
        dist = dist_prev;          
        digitalWrite(PIN_LED, 1);      
      } else if (dist > DIST_MAX) {
        dist = dist_prev;          
        digitalWrite(PIN_LED, 1);      
      } else {    // In desired Range
        dist_prev = dist;
        digitalWrite(PIN_LED, 0);       
      }

  
  // we need EMA filter here !!!
  dist_ema = _EMA_ALPHA * dist + (1-_EMA_ALPHA)*dist_ema;


  // map distance into duty
  //duty = map(a_value, 0, 1023, _DUTY_MIN, _DUTY_MAX);

  duty = (float) (dist_ema-100)*(_DUTY_MAX-_DUTY_MIN)/150.0+_DUTY_MIN;
  myservo.writeMicroseconds(duty);


  // print IR sensor value, distnace, duty !!!
  
  
  Serial.print("MIN:");   Serial.print(DIST_MIN);
  Serial.print(", IR:");   Serial.print(a_value);
  Serial.print(",dist:");   Serial.print(dist);
  Serial.print(",ema:");   Serial.print(dist_ema);
  Serial.print(",servo:");   Serial.print(duty);
  Serial.print(",MAX:");   Serial.print(DIST_MAX);

  Serial.println("");
}
