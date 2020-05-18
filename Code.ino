#define TxD 4
#define RxD 2
#include <SoftwareSerial.h>

int valve[7] = {0,8,6,10,12,9,3};
int activatedTimes[8] = {1,1,1,1,1,1,1,1};
boolean valveOpen[7];
boolean done, specialSequence;
int incomingNumber, sequence, tempNumber, pulseTime, cycles, pulseValve, inflationTime, deflationTime, cyclesTime;
char firstType;


SoftwareSerial bluetoothSerial(TxD, RxD);


//Runs once to setup the Arduino board. 
//Initialize the pins and closes the valves if open.
void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
bluetoothSerial.begin(9600);
for(int i = 0; i < 7; i++)
  {
    //lägg till två till för de två ventilerna som tillkommer.
    pinMode(valve[i], OUTPUT);
    digitalWrite(valve[i], LOW);
    valveOpen[i] = false;
  }
}


/*
 * 
 * SEQUENCE 3 thing
 * 
 */
void doSequence(int a){
  
  if(a == 0){
  //---------Open reference then open first valve----------
    Serial.println("S-C1 Rätt är om försöksperson säger: Vänster");
    digitalWrite(valve[3], HIGH);
    delay(1000);
    digitalWrite(valve[3], LOW);
    delay(1000);
    digitalWrite(valve[1], HIGH);
    delay(1000);
    digitalWrite(valve[1], LOW);

    
  }else if(a == 1){
  //---------Open reference then open second valve----------  
    Serial.println("S-C2 Rätt är om försöksperson säger: Vänster");
    digitalWrite(valve[3], HIGH);
    delay(1000);
    digitalWrite(valve[3], LOW);
    delay(1000);
    digitalWrite(valve[2], HIGH);
    delay(1000);
    digitalWrite(valve[2], LOW);   
    Serial.println("svängigsnabel"); 


  }else if(a == 2){
    //---------Open reference then open third valve----------
    Serial.println("S-C3 Rätt är om försöksperson säger: Höger");
    digitalWrite(valve[3], HIGH);
    delay(1000);
    digitalWrite(valve[3], LOW);
    delay(1000);
    digitalWrite(valve[4], HIGH);
    delay(1000);
    digitalWrite(valve[4], LOW);
    
  }else if(a == 3){
    //---------Open reference then open fourth valve---------
    Serial.println("S-C4 Rätt är om försöksperson säger: Höger");
    digitalWrite(valve[3], HIGH);
    delay(1000);
    digitalWrite(valve[3], LOW);
    delay(1000);
    digitalWrite(valve[5], HIGH);
    delay(1000);
    digitalWrite(valve[5], LOW);
    
  }else if(a == 4){
    //---------Open first valve and the Reference----------
    Serial.println("C1-S Rätt är om försöksperson säger: Höger");
    digitalWrite(valve[1], HIGH);
    delay(1000);
    digitalWrite(valve[1], LOW);
    delay(1000);
    digitalWrite(valve[3], HIGH);
    delay(1000);
    digitalWrite(valve[3], LOW);    
    
  }else if(a == 5){
    //---------Open second valve and the Reference----------    
    Serial.println("C2-S Rätt är om försöksperson säger: Höger");
    digitalWrite(valve[2], HIGH);
    delay(1000);
    digitalWrite(valve[2], LOW);
    delay(1000);
    digitalWrite(valve[3], HIGH);
    delay(1000);
    digitalWrite(valve[3], LOW);
    
  }else if(a == 6){
    //---------Open third valve and the Reference----------  
    Serial.println("C3-S Rätt är om försöksperson säger: Vänster");
    digitalWrite(valve[4], HIGH);
    delay(1000);
    digitalWrite(valve[4], LOW);
    delay(1000);
    digitalWrite(valve[3], HIGH);
    delay(1000);
    digitalWrite(valve[3], LOW);
        
  }else if(a == 7){
    //---------Open forth valve and the Reference----------  
    Serial.println("C4-S Rätt är om försöksperson säger: Vänster"); 
    digitalWrite(valve[5], HIGH);
    delay(1000);
    digitalWrite(valve[5], LOW);
    delay(1000);
    digitalWrite(valve[3], HIGH);
    delay(1000);
    digitalWrite(valve[3], LOW);    
    
  }
}

void loop() {
 
//Awaits a bluetooth input.
 while(Serial.available()==0) ;

 
//reads the bluetooth input
 if(Serial.available() > 0) {
    //read the incoming bite, firstType decides what will happen next.
    firstType = Serial.read();

    //-----------------OPEN/CLOSE-----------------
    if(firstType == 'o'){
      incomingNumber = Serial.parseInt();
    }

    //-----------------PULSE---------------------
    if(firstType == 'p'){
      pulseValve = Serial.parseInt();
      pulseTime = Serial.parseInt();
      cycles = Serial.parseInt();
    }

    //----------Inflation/Deflation--------------
    if(firstType == 'd'){
      pulseValve = Serial.parseInt();
      inflationTime = Serial.parseInt();
      deflationTime = Serial.parseInt();
      cycles = Serial.parseInt(); 
    }

    //-------------Sequences---------------------
    if(firstType == 's'){
      sequence = Serial.parseInt();
    }
    //------------Y Stupid stuff-----------------
    if(firstType == 'y'){
      pulseValve = Serial.parseInt();
      pulseTime = Serial.parseInt();
      cycles = Serial.parseInt();
     
    }
  }


//----------------------Open/close--------------------
/*
 * The Open close test used for test 1. With a 1000ms delay for opening and closing valves. 
 * Inflating/deflating McKibben.
 * 
 */
if(firstType == 'o'){
  do{
    tempNumber = incomingNumber % 10;{
      if(tempNumber < 7){
        digitalWrite(valve[tempNumber], HIGH);
        delay(1000);
        digitalWrite(valve[tempNumber], LOW);
      }
    }
    incomingNumber = incomingNumber / 10;
  }while(incomingNumber != 0);
}

 /**************************************************
  * 
  * Open close without delay. 
if(firstType == 'o'){
 do{
  tempNumber = incomingNumber % 10;{
    if(tempNumber < 7){      
      if(valveOpen[tempNumber]){
        digitalWrite(valve[tempNumber], LOW);
        valveOpen[tempNumber] = false;
      }else if(!valveOpen[tempNumber]){
        digitalWrite(vavle[tempNumber], HIGH);
        valveOpen[tempNumber] = true;
      }
    }
 }
  incomingNumber = incomingNumber / 10;
}while(incomingNumber != 0);

}
**************************************************/

/*
 * 
 * 
 * Some different 
 * 
 * 
 */
 

if(firstType == 'y'){

  for(int i = 0; i < cycles; i++){
  digitalWrite(valve[pulseValve], HIGH);
  delay(pulseTime);
  digitalWrite(valve[pulseValve + 1], HIGH);
  delay(pulseTime);
  digitalWrite(valve[pulseValve + 2], HIGH);
  delay(pulseTime);
  digitalWrite(valve[pulseValve + 3], HIGH);
  delay(pulseTime);
  digitalWrite(valve[pulseValve + 4], HIGH);
  delay(pulseTime);
  digitalWrite(valve[pulseValve + 5], HIGH);
  delay(pulseTime);    
  digitalWrite(valve[pulseValve], LOW);
  delay(pulseTime);
  digitalWrite(valve[pulseValve + 1], LOW);
  delay(pulseTime);
  digitalWrite(valve[pulseValve + 2], LOW);
  delay(pulseTime);
  digitalWrite(valve[pulseValve + 3], LOW);
  delay(pulseTime);
  digitalWrite(valve[pulseValve + 4], LOW);
  delay(pulseTime);  
  digitalWrite(valve[pulseValve + 5], LOW);
  delay(pulseTime);  
  }
}

//----------------Waveform------------------------
if(firstType == 'p'){

  if(pulseValve < 7){
    for(int i = 0; i < cycles; i++){
      digitalWrite(valve[pulseValve], HIGH);
      delay(pulseTime);
      digitalWrite(valve[pulseValve + 1], HIGH);
      digitalWrite(valve[pulseValve], LOW);
      delay(pulseTime);
      digitalWrite(valve[pulseValve + 1], LOW);
      digitalWrite(valve[pulseValve + 2], HIGH);
      delay(pulseTime);
      digitalWrite(valve[pulseValve + 2], LOW);
      digitalWrite(valve[pulseValve + 3], HIGH);
      delay(pulseTime);
      digitalWrite(valve[pulseValve + 3], LOW);
      digitalWrite(valve[pulseValve + 4], HIGH);
      delay(pulseTime);
      digitalWrite(valve[pulseValve + 4], LOW);
      digitalWrite(valve[pulseValve + 5], HIGH);
      delay(pulseTime);
      digitalWrite(valve[pulseValve + 5], LOW);
      digitalWrite(valve[pulseValve + 4], HIGH);
      delay(pulseTime);
      digitalWrite(valve[pulseValve + 4], LOW);
      digitalWrite(valve[pulseValve + 3], HIGH);
      delay(pulseTime);
      digitalWrite(valve[pulseValve + 3], LOW);
      digitalWrite(valve[pulseValve + 2], HIGH);
      delay(pulseTime);
      digitalWrite(valve[pulseValve + 2], LOW);
      digitalWrite(valve[pulseValve + 1], HIGH);
      delay(pulseTime);
      digitalWrite(valve[pulseValve + 1], LOW); 
    }
  }
}

//---------------Deflate/inflate-----------------
if(firstType == 'd'){
    if(pulseValve < 7){
    for(int i = 0; i < cycles; i++){
      digitalWrite(valve[pulseValve], HIGH);
      delay(inflationTime);
      digitalWrite(valve[pulseValve], LOW);
      delay(deflationTime);
    }
  }
}

if(firstType == 's'){
  if(sequence == 1){
    //------------------Crazy Random----------------
    int times = random(60,90);
    for(int i = 0; i < times; i++){
      int a = random(1,7);
      digitalWrite(valve[a], HIGH);
      int b = random(40,70);
      delay(b);
      digitalWrite(valve[a], LOW);
      delay(b);
    } 
  }
  if(sequence == 2){
  //-------------------Staircase--------------------
    for(int cycles = 0; cycles < 4; cycles++){
      for(int i = 1; i < 7; i++){
        digitalWrite(valve[i], HIGH);
        delay(400);
      }
      for(int i = 1; i < 7; i++){
        digitalWrite(valve[i], LOW);
        delay(400);
      }
    }
  }

 /*
  * SEQUENCE 3
  * 
  * Will be used for test 2. 
  * 
  * 
  * 
  */
  if(sequence == 3){
    int a = random(0,8);
    cyclesTime = -7;
    for(int i = 0; i < 8; i++){
       cyclesTime = activatedTimes[i] + cyclesTime;
       if(cyclesTime == 80){
        done = true;
       }
     }
     Serial.println(cyclesTime);
    if(done){
        /*
         * 
         * DO crazy sequence?
         * SÅ man vet att den är klar.  
         * 
         */
      Serial.println("STOP! YOU ARE DONE!");
         
    }
    do{
      if(activatedTimes[a] <= 10){
        doSequence(a);
        Serial.println("-----------------------------------------");
        activatedTimes[a] += 1;
        specialSequence = true;
      }
      a = random(0,8);     
  }while(!specialSequence);
  firstType = 'i';
  specialSequence = false;
}
if(sequence == 4)
{
  
      for(int i = 0; i < 40; i++){
      digitalWrite(valve[2], HIGH);
      delay(30);
      digitalWrite(valve[2], LOW);
      digitalWrite(valve[3], HIGH);
      delay(30);
      digitalWrite(valve[3], LOW);
}
}
}
}
