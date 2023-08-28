#include <AccelStepper.h>
#include <Stepper.h>

//setting to position zero from L1 reached frontwise and L2 in -90* / +90*

#define IN11 15
#define IN21 2
#define IN31 4
#define IN41 5

#define IN12 27
#define IN22 14
#define IN32 12
#define IN42 13

#define IN13 23
#define IN23 22
#define IN33 21
#define IN43 19

const int steps = 2048;
AccelStepper stepper1(AccelStepper::FULL4WIRE, IN12, IN32, IN22, IN42);
AccelStepper stepper2(AccelStepper::FULL4WIRE, IN11, IN31, IN21, IN41);
AccelStepper stepper3(AccelStepper::FULL4WIRE, IN13, IN33, IN23, IN43);

Stepper stepper1x(steps,IN12,IN32,IN22,IN42);
Stepper stepper2x(steps,IN11,IN31,IN21,IN41);
Stepper stepper3x(steps,IN13,IN33,IN23,IN43);

int switch1 = 32;
int switch2 = 34;
int switch3 = 35;

int a = 0;
int b = 0;
int flag1 =0;
int flag2 = 0;

void move1()
{

    stepper1.moveTo(-900);           
    stepper2.moveTo(-500);   
    stepper3.moveTo(-700); 
              
    if (digitalRead(switch1) == HIGH){
       flag1++;
       if(flag1>0){
          stepper1.setMaxSpeed(0);
          stepper1.setAcceleration(0);
          stepper1.moveTo(0);
          stepper1.stop();
          stepper1x.step(421);
          stepper2x.step(-38);
        }
    }
    
    if (digitalRead(switch2) == HIGH){
      flag2++;
      if(flag2>0){
          stepper2.setMaxSpeed(0);
          stepper2.setAcceleration(0);
          stepper2.moveTo(0);
          stepper2.stop();
          //stepper2x.step(-1);
      }
    }
    
    if (digitalRead(switch3) == HIGH){  //!=
    stepper3.setMaxSpeed(0);
    stepper3.setAcceleration(0);
    stepper3.moveTo(0);
    stepper3.stop();
    }
   
    stepper1.run();
    stepper2.run();
    stepper3.run();
    
}


 


void setup() {

   pinMode(switch1, INPUT);
   pinMode(switch2, INPUT);
   pinMode(switch3, INPUT);

   Serial.begin(9600);

   stepper1.setMaxSpeed(375.0);
   stepper1.setAcceleration(175.0);
   stepper2.setMaxSpeed(250.0);
   stepper2.setAcceleration(100.0);
   stepper3.setMaxSpeed(150.0);
   stepper3.setAcceleration(50.0);

   stepper1x.setSpeed(5);
   stepper2x.setSpeed(3);
   stepper3x.setSpeed(3);
   
       
}

void loop() {
  
  digitalRead(switch1);
  digitalRead(switch2);
  digitalRead(switch3);
  
  move1();
  
}
