const int green = 2;
const int blue = 3;
const int red = 4;
const int temperaturePin = A0;
const int fanPin = 5;
const int buttonPin = 6;
int buttonState = 0;
void setup() {
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
 float temperature = getVoltage(temperaturePin);  //getting the voltage reading from the temperature sensor 
 temperature = (temperature - .5) * 100;          //converting from 10 mv per degree wit 500 mV offset
                                                  //to degrees ((volatge - 500mV) times 100)
 Serial.println(temperature);                     //printing the result
 if (buttonOveride()){
  delay(5000);                                     
 }
 else{
 setLed(temperature);
 setFan(temperature);
 delay(5000);
 }
}

float getVoltage(int pin){
 return (analogRead(pin) * .004882814); //converting from a 0 to 1023 digital range
                                        // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}

void setLed(float temp)
{
  if (temp >= 30)
  {
    digitalWrite(red, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
  }
  else if (temp >= 25)
  {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  }
  else 
  {
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
  }
    
    
}

void setFan(int temp)
{
  if (temp >= 25)
    digitalWrite(fanPin, HIGH);
  else
    digitalWrite(fanPin, LOW);
  
 
}

bool buttonOveride()
{
 // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn fan on:
    digitalWrite(fanPin, HIGH);
    return true;
  } else {
    // turn fan off:
    digitalWrite(fanPin, LOW);
    return false;
  }
}
