int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;// the analog reading from the sensor divider
int photocellReading2;
int photocellReading3;
int photocellReading4;
int photocellReading5;
int photocellReading6;
int readout;
void setup(void) {
  
  Serial.begin(9600);   
}

void loop(void) {
  photocellReading = analogRead(photocellPin);  
  photocellReading2 = analogRead(photocellPin);  
  photocellReading3 = analogRead(photocellPin);  
  photocellReading4 = analogRead(photocellPin);  
  photocellReading5 = analogRead(photocellPin);  
  photocellReading6 = analogRead(photocellPin);  
  readout = (photocellReading+photocellReading2+photocellReading3+photocellReading4+photocellReading5+photocellReading6)/6    
  Serial.println(readout);     // the average raw analog reading
  delay(100);
}

