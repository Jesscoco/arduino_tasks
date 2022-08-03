/*


*/
const int trigPin = 14; 
const int echoPin = 12; 
const int led1 = 13;
const int led2 = 4;

long duration;
int distance;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
Serial.begin(9600); // Starts the serial communication
}
void loop() {

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= (duration*0.034)/2;

// Prints the distance on the Serial Monitor
Serial.println(distance);

 
if (distance <=7)
  {
    digitalWrite(led1, HIGH);// turn the LED on (HIGH is the voltage level)
  }
  else
  {
    digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
  }
 /* if (distance <=15)
  {
    digitalWrite(led2, HIGH);// turn the LED on (HIGH is the voltage level)
  }
  else
  {
    digitalWrite(led2, LOW);    // turn the LED off by making the voltage LOW
  }*/

}
