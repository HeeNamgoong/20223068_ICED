#define PIN_LED 7
unsigned int count;

void setup() {
  pinMode(7, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  
  Serial.println("Hello World!");
  int count = 0;
}


void loop () {

  Serial.println(++count);

  digitalWrite(PIN_LED, 0);
  delay(1000);

  repeat();
  repeat();
  repeat();
  repeat();
  repeat();
  repeat();

  while(1){}
  
}


void repeat(){
  digitalWrite(PIN_LED, LOW);
  delay(100);
  digitalWrite(PIN_LED, HIGH);
  delay(100);
  }
