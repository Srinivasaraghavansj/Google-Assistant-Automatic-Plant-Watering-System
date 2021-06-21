
#define waterlevelthreshhold 1
#define waterlevelpin 6
#define filluppin 3
#define drainpin 4
#define waterplantspin 5

#define estopbtnpin 2
#define drainbtnpin 9
#define fillupbtnpin 10
#define waterplantsbtnpin 11
 
#define waterplantstime 10000
#define draintime 150000

void estop();
void fill();
void btns();

unsigned long lm1 = 0, lm2 = 0, lm3 = 0, lm4 = 0;

void setup() {
pinMode(filluppin, OUTPUT);
pinMode(drainpin, OUTPUT);
pinMode(waterplantspin, OUTPUT);
pinMode(waterlevelpin, INPUT);
pinMode(estopbtnpin, INPUT_PULLUP);
pinMode(drainbtnpin, INPUT_PULLUP);
pinMode(fillupbtnpin, INPUT_PULLUP);
pinMode(waterplantsbtnpin, INPUT_PULLUP);

digitalWrite(waterplantspin, LOW);
digitalWrite(drainpin, LOW);
delay(waterplantstime);
digitalWrite(waterplantspin, HIGH);
delay(draintime);  

attachInterrupt(digitalPinToInterrupt(estopbtnpin), estop, LOW);
}

void loop() {

btns();

 if (millis() - lm1 > 28800001) {  //once every 8 hrs 1 ms
   digitalWrite(waterplantspin, LOW);
   delay(waterplantstime);
   digitalWrite(waterplantspin, HIGH);
   delay(draintime);   
 }
 if (millis() - lm2 > 14400000) { //once every 4 hrs
   digitalWrite(drainpin, LOW);
   delay(draintime);
   fill();
   digitalWrite(drainpin, HIGH);
  }
 if (millis() - lm3 > 900000) {fill();}

}

void estop()
{
  if(digitalRead(fillupbtnpin) == LOW || digitalRead(drainbtnpin) == LOW || digitalRead(waterplantsbtnpin) == LOW)
  {
    btns();  
  }
  else
  {
  digitalWrite(waterplantspin, HIGH);
  digitalWrite(filluppin, HIGH);
  digitalWrite(drainpin, HIGH);
 /* lm1 =millis();
  lm2 =millis();
  lm3 =millis();
  lm4 =millis();*/
  }
  }

void fill(){
while(waterlevelpin != waterlevelthreshhold){digitalWrite(filluppin, LOW);}
digitalWrite(filluppin, HIGH);
}


void btns(){
if(digitalRead(fillupbtnpin) == LOW)digitalWrite(filluppin, LOW);
else digitalWrite(filluppin, HIGH);

if(digitalRead(drainbtnpin) == LOW)digitalWrite(drainpin, LOW);
else digitalWrite(drainpin, HIGH);

if(digitalRead(waterplantsbtnpin) == LOW)digitalWrite(waterplantspin, LOW);
else digitalWrite(waterplantspin, HIGH);
}
