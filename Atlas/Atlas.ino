

/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */


const int numReadings = 10;
 
int bluePin = 13;
int greenPin = 7;
int yellowPin = 3;
int redPin = 5;
 
float readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average

unsigned long timePassed;
 
int inputPin = A0 ;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  for(int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading]=0;
}
 
// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  total = total - readings[readIndex];
  int sensorValue = analogRead(inputPin);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  readings[readIndex] = voltage;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
 
  if(readIndex >= numReadings)
    readIndex = 0;
  // print out the value you read:
 
  average = total / numReadings;
    if(average >= 1.5){
    digitalWrite(bluePin, HIGH);
  } else if(average < 1.5){
    digitalWrite(bluePin, LOW);
  }
 
  if(average > 3.20){
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, LOW);
    } else if( average > 3.05 && average < 3.15){
      digitalWrite(greenPin, HIGH);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, LOW);
      timePassed = 0;
    } else if( average > 1.5 && average < 3.05){
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, HIGH);
      digitalWrite(redPin, LOW);
      if(timePassed == 0){
        timePassed = millis();
      }
    }else if( average > 1 && average < 1.4 ){
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, HIGH);
    } else if (average < 1) {
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, LOW);
    }
   
  Serial.print(average);
  Serial.print(" ");
  int passnum = timePassed - millis();
  Serial.println(passnum);
  delay(1);
}

