//const int BUZZER=3;
const int GSR=A1;
const int Temperature= A0;
const int ledSweatVidur =12;
const int ledTempVidur =11;
int threshold=0;
int thresholdTemperature=0;
int sensorValue;
int sensorValueTemperature;
int count=0;
float aref_voltage=5.0;

void setup(){
  long sum=0;
  long sumTemperature=0;
  Serial.begin(9600);
  pinMode(ledSweatVidur,OUTPUT);
  digitalWrite(ledSweatVidur,LOW);
  pinMode(ledTempVidur,OUTPUT);
    digitalWrite(ledTempVidur,LOW);

  delay(1000);
  
  for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  sum += sensorValue;
  delay(5);
  sensorValueTemperature=analogRead(Temperature);
  sumTemperature += sensorValueTemperature;
  }
  
  threshold = sum/500;
    thresholdTemperature = sumTemperature/500;
   Serial.print("threshold =");
   Serial.println(threshold);
   Serial.print("threshold Temperature =");
   Serial.println(((thresholdTemperature * aref_voltage/1024.0)-.5)*10);
      Serial.println("==============================================================");

   Serial.print("                                       | Sweat Sensor");
   Serial.println("         |        Temperature |");
  }

void loop(){
  int temp;
  int tempTemperature;
  sensorValue=analogRead(GSR);
  //Serial.print("sensorValue=           ");
  Serial.print("                                       | ");
  Serial.print(sensorValue);
   sensorValueTemperature=analogRead(Temperature);

 // Serial.print("Temperature Value=                       ");
  Serial.print("                  |            ");
  Serial.print(((sensorValueTemperature* aref_voltage/1024.0)-.5)*10);
  Serial.println("   | ");
  temp = threshold - sensorValue;
  if(abs(temp)>50){
      digitalWrite(ledSweatVidur,1);
    long sum=0;
   long sumTemperature=0;
  long sumHeart=0;
    count= count+1;
    sensorValue=analogRead(GSR);
    sensorValueTemperature=analogRead(Temperature);
    temp = threshold - sensorValue;
    tempTemperature = abs(thresholdTemperature - sensorValueTemperature);
    //if(abs(temp)>20){
    //digitalWrite(BUZZER,HIGH);
    Serial.println();
    Serial.println("================>LIAR IS SWEATING!<==================");
    Serial.print(" With Temperature off by:             ");
    Serial.println(((tempTemperature* aref_voltage/1024.0)-.5)*10);
    Serial.print(" With Sweat Sensor off by:             ");
    Serial.println(temp);
    if((((abs(tempTemperature-sensorValueTemperature)* aref_voltage/1024.0)-.5)*10)>4)
    {
      digitalWrite(ledTempVidur,1);
    }
    else{
        digitalWrite(ledTempVidur,0);
    }
    
    delay(500);
    //digitalWrite(BUZZER,LOW);
    //delay(1000);

    if(count>3){
    Serial.println("Please wait re-checking!");
     for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR);
  sum += sensorValue;
  sensorValueTemperature=analogRead(Temperature);
  sumTemperature += sensorValueTemperature;
  delay(5);
  }
  threshold = sum/500;
   thresholdTemperature = sumTemperature/500;
   Serial.print(" new sweat threshold =");
   Serial.println(threshold);
   Serial.print("new threshold Temperature =                            ");
   Serial.println(((thresholdTemperature * aref_voltage/1024.0)-.5)*10);
   count=0;
   Serial.println("==========================================================================================");
   Serial.print("                                       | Sweat Sensor");
   Serial.println("         |        Temperature |");
  }
  else{
    Serial.println("===============================================================================");

   Serial.print("                                       | Sweat Sensor");
   Serial.println("         |        Temperature |");
    }
    delay(5);
    }
    else{
                digitalWrite(ledSweatVidur,0);
                if((((abs(tempTemperature-sensorValueTemperature)* aref_voltage/1024.0)-.5)*10)<4)
    {
      digitalWrite(ledTempVidur,0);
    }
    }
        delay(500);

  }
