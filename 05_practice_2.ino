unsigned int count;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  
  Serial.println("Hello World!");
  int count = 0;
}


void loop () {

  Serial.println(++count);

  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);

  repeat();
  repeat();
  repeat();
  repeat();
  repeat();
  
  while(1){}
  
}


void repeat(){
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  }
