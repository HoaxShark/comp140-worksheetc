// These constants won't change. They're used to give names to the pins used:
const int analogInPinLeft = A0;  // Analog input pin that the potentiometer left is attached to
const int analogInPinRight = A1;  // Analog input pin that the potentiometer right is attached to
const int analogOutPinLeft = 9; // Analog output pin that the left LED is attached to
const int analogOutPinRight = 6; // Analog output pin that the right LED is attached to

int sensorValueLeft = 0;        // value read from the left pot
int outputValueLeft = 0;        // value output to the left PWM (analog out)
int sensorValueRight = 0;        // value read from the right pot
int outputValueRight = 0;        // value output to the right PWM (analog out)
int inByte;
int led1 = 9;
bool led1state;

void setup() {
  // initialize serial communications:
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    inByte = Serial.read();
    if (inByte == 'P') sendPositions();
    if (inByte == 'L'){
      if (led1state == false){
        led1state =true;
        digitalWrite(led1, HIGH);
      }else{
        led1state = false;
    }
  }

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}

void sendPositions(){
  // read the analog in values:
  sensorValueLeft = analogRead(analogInPinLeft);
  sensorValueRight = analogRead(analogInPinRight);
  // map them to the range of the analog outs:
  outputValueLeft = map(sensorValueLeft, 0, 1023, 0, 255);
  outputValueRight = map(sensorValueRight, 0, 1023, 0, 255);
  // change the analog out values:
  analogWrite(analogOutPinLeft, outputValueLeft);
  analogWrite(analogOutPinRight, outputValueRight);
  

  // print the results to the Serial Monitor:
  Serial.print(getPadded(sensorValueLeft));
  Serial.println(getPadded(sensorValueRight));

}

String getPadded(int num){
  char buff[5];
  char padded[6];

  sprintf(buff, "%.4u", num);
  padded[0] = buff[0];
  padded[1] = buff[1];
  padded[2] = buff[2];
  padded[3] = buff[3];
  padded[4] = buff[4];
  padded[5] = '\0';

  return String(padded);
}


