const int HStepResolution = 400;
const int VStepResolution = 200;
const int TStepResolution = 200;
const double afstandgleuf = 335;

//Gleufposities
const int G1 = 10*VStepResolution;
const int G2 = G1 + afstandgleuf;
const int G3 = G2 + afstandgleuf;
const int G4 = G3 + afstandgleuf;
const int G5 = G4 + afstandgleuf;
const int G6 = G5 + afstandgleuf;
const int G7 = G6 + afstandgleuf;
const int G8 = G7 + afstandgleuf;
const int G9 = G8 + afstandgleuf;

//Stepmotor Pins
const int Enable = 46;
const int HStep = 53;
const int VStep = 51;
const int TStep = 49;
const int DHStep = 52;
const int DVStep = 50;
const int DTStep = 48;

//Button Pins
const int HEnd = 25;
const int VEnd = 22;
const int Bakje = 23;
const int Start = 24;

//Sensor Pins
const int Tel = 26;

//LEDS
const int Groen = 30;
const int Geel = 31;
const int Rood = 32;

//Status
int Status = 0;
int PositionH = -1;
int PositionV = -1;
int PositionT = 0;
int Teller = 0;

void setup() {
  // put your setup code here, to run once:
  //OUTPUTS
  pinMode(Enable, OUTPUT);
  pinMode(HStep, OUTPUT);
  pinMode(VStep, OUTPUT);
  pinMode(TStep, OUTPUT);
  pinMode(DHStep, OUTPUT);
  pinMode(DVStep, OUTPUT);
  pinMode(DTStep, OUTPUT);
  pinMode(Groen, OUTPUT);
  pinMode(Geel, OUTPUT);
  pinMode(Rood, OUTPUT);

  //INPUTS
  pinMode(HEnd, INPUT_PULLUP);
  pinMode(VEnd, INPUT_PULLUP);
  pinMode(Bakje, INPUT);
  pinMode(Start, INPUT);
  pinMode(Tel, INPUT);
  //SETUP
  digitalWrite(DTStep, LOW);
  digitalWrite(Enable, LOW);
  digitalWrite(Geel, HIGH);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(Status == 0){
    Teller = 0;
    digitalWrite(Geel, HIGH);
    digitalWrite(DHStep,LOW);
    while(true){
      digitalWrite(HStep, HIGH);
      delay(1);
      digitalWrite(HStep,LOW);
      delay(1);
      if(digitalRead(HEnd) == LOW){
        break;
      }

    }
    PositionH = 0;

    digitalWrite(DVStep, HIGH);
    while(true){
      digitalWrite(VStep, HIGH);
      delay(1);
      digitalWrite(VStep, LOW);
      delay(1);
      if(digitalRead(VEnd) == LOW){
        break;
      }
    }
    PositionV = 0;

    digitalWrite(Geel, LOW);
    Status = 1;
    
  }else if(Status == 1){
    while(digitalRead(Bakje) == LOW){
      digitalWrite(Groen, HIGH);
    }
    while(digitalRead(Start) == LOW){
      digitalWrite(Groen, HIGH);
      delay(800);
      digitalWrite(Groen, LOW);
      delay(800);
    }
    digitalWrite(Groen, LOW);
    digitalWrite(Geel, HIGH);

    digitalWrite(DVStep, LOW);
    while(PositionV != (35*VStepResolution+ 100)){
      digitalWrite(VStep, HIGH);
      delay(1);
      digitalWrite(VStep, LOW);
      delay(1);
      PositionV++;
    }

    digitalWrite(DHStep, HIGH);
    while(PositionH != G5){
      digitalWrite(HStep, HIGH);
      delay(1);
      digitalWrite(HStep, LOW);
      delay(1);
      PositionH++;
    }
  Status = 2;
    
  }else if(Status == 2){
    int Slots[9] = {G5,G6,G4,G7,G3,G8,G2,G9,G1};
    int lastcheck = -26;
    for(int i = 0; i < 10; i++){ 
    int aantal = 0;
    while(PositionH != Slots[i]){
      digitalWrite(HStep, HIGH);
      delay(1);
      digitalWrite(HStep, LOW);
      delay(1);
      PositionH++;
    }
    while(aantal != 3){
      if(lastcheck < PositionT - 25){  
        if(digitalRead(Tel) == LOW){
          aantal++;
          Teller++;
          lastcheck = PositionT;
        }
       }
    digitalWrite(TStep, HIGH);
    delay(1);
    digitalWrite(TStep, LOW);
    delay(1);
    PositionT++;
  }
    }
   Status = 3;
  }else if(Status == 3){
    int Slots[9] = {G1,G2,G3,G4,G5,G6,G7,G8,G9};
    int Values[9] = {39,38,39,38,39,38,39,39,39};
    int lastcheck = -26;

    for(int i = 0; i < 9; i++){
    int aantal = 0;
    while(PositionH != Slots[i]){
      digitalWrite(HStep, HIGH);
      delay(1);
      digitalWrite(HStep, LOW);
      delay(1);
      PositionH++;
    }
    while(aantal != Values[i]){
      if(lastcheck < PositionT - 25){  
        if(digitalRead(Tel) == LOW){
          aantal++;
          Teller++;
          lastcheck = PositionT;
        }
       }
    digitalWrite(TStep, HIGH);
    delay(1);
    digitalWrite(TStep, LOW);
    delay(1);
    PositionT++;
  }
    }
    Status = 0;
  }
  
}
