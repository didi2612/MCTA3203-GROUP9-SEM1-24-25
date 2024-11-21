int tval;
 float temp;
  int ldr;
  int ldrper;
  int temppin = A0;
  int ldrpin = A1;
 

void setup() {
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL, CLOCK, TEMPERATURE, LIGHT");
  pinMode(temppin, INPUT);
  pinMode(ldrpin, INPUT);
}

void loop() {
  tval = analogRead(temppin);
  temp = ((float)tval/1023)*5000;
  temp = temp/10;

  ldr = analogRead(ldrpin);
  ldrper = map(ldr, 0,1023, 0,100);
  Serial.print("ldr value :");
  Serial.println(ldrper);
  Serial.print("Temp Value : ");
  Serial.println(temp);
  Serial.print("DATA, TIME,");
  Serial.print(temp);
  Serial.print(",");
  Serial.println(ldrper);
  delay(500);

}