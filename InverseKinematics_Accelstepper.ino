#include <AccelStepper.h>
#include <Servo.h>
#include <math.h>
#include <stdio.h>

Servo servo;
//define pins used by microcontroller for 3 stepper motors
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

const int steps = 2048; //define full rotation steps number for BYJ-48

AccelStepper stepper1(AccelStepper::FULL4WIRE, IN12, IN32, IN22, IN42);
AccelStepper stepper2(AccelStepper::FULL4WIRE, IN11, IN31, IN21, IN41);
AccelStepper stepper3(AccelStepper::FULL4WIRE, IN13, IN33, IN23, IN43);

//set of desired X,Y,Z coordinates
float floatFromPCx = 50.0;    
float floatFromPCy = 50.0;          
float floatFromPCz = 50.0;


float b = atan2(floatFromPCy,floatFromPCx) * (180/3.1415);
float b_cw1 = atan2(floatFromPCx,floatFromPCy)*(180/3.1415);
float l = sqrt(floatFromPCx*floatFromPCx + floatFromPCy*floatFromPCy);
float h = sqrt(l*l + floatFromPCz*floatFromPCz);

float phi = atan(floatFromPCz/l)* (180/3.1415);
float theta = acos((h/2)/90) * (180 / 3.1415);

float a1 = phi + theta;  //angle for first part of arm
float a2 = phi - theta;  //angle for second part of arm

float ga = 180.0 - (90.0+theta);
float be = 180.0-(2*ga); //in degrees



float ang1 = (b * 5.66)-36; //angle times gear ratio(5.66) -36 arm shift fix
float ang1_cw1 = (b_cw1 * 5.66)-36;
float pom_sil2 = ((90 - a1) * 5.66)-20;//-20 arm shift 
float pom_sil3_v2 = (be * 5.66)+70;//+70 arm shift

float cw_offset = 90*5.66;

//function controlling movement in the first quarter of carthesian plate
void cw1(float b, float a1, float be)
{     
    stepper1.moveTo(ang1_cw1);
    stepper2.moveTo(pom_sil2);
    stepper3.moveTo(-pom_sil3_v2);
    
    
    stepper1.setMaxSpeed(300.0);
    stepper1.setAcceleration(100.0);
    stepper2.setMaxSpeed(300.0);
    stepper2.setAcceleration(100.0);
    stepper3.setMaxSpeed(300.0);
    stepper3.setAcceleration(100.0);
    stepper1.run();
    stepper2.run();
    stepper3.run();
}
void cw1_back(float b_cw1, float a1, float be){ //function controlling return movement in first quarter carthesian plate
   
    stepper3.moveTo(pom_sil3_v2);
    stepper2.moveTo(-pom_sil2);
    stepper1.moveTo(-ang1_cw1 );
    
    stepper1.setMaxSpeed(300.0);
    stepper1.setAcceleration(100.0);
    stepper2.setMaxSpeed(300.0);
    stepper2.setAcceleration(100.0);
    stepper3.setMaxSpeed(300.0);
    stepper3.setAcceleration(100.0);
    stepper1.run();
    stepper2.run();
    stepper3.run();
}
void cw2(float b, float a1, float be)
{   //delay(1000);
    stepper1.moveTo(-(ang1-cw_offset));
    stepper2.moveTo(pom_sil2);
    stepper3.moveTo(-pom_sil3_v2);
    //delay(4000);
    //stepper3.moveTo(pom_sil3_v2);
    //stepper2.moveTo(-pom_sil2);
    //stepper1.moveTo(ang1-cw_offset);

    stepper1.setMaxSpeed(300.0);
    stepper1.setAcceleration(100.0);
    stepper2.setMaxSpeed(300.0);
    stepper2.setAcceleration(100.0);
    stepper3.setMaxSpeed(300.0);
    stepper3.setAcceleration(100.0);
    stepper1.run();
    stepper2.run();
    stepper3.run();
}

void cw3(float b, float a1, float be)
{   //delay(1000);
    stepper1.moveTo(-(ang1+cw_offset));
    stepper2.moveTo(-pom_sil2);
    stepper3.moveTo(pom_sil3_v2);

    
    stepper1.setMaxSpeed(300.0);
    stepper1.setAcceleration(100.0);
    stepper2.setMaxSpeed(300.0);
    stepper2.setAcceleration(100.0);
    stepper3.setMaxSpeed(300.0);
    stepper3.setAcceleration(100.0);
    stepper1.run();
    stepper2.run();
    stepper3.run();
}
void cw4(float b, float a1, float be)
{   
    stepper1.moveTo(-(ang1+cw_offset));
    stepper2.moveTo(-pom_sil2);
    stepper3.moveTo(pom_sil3_v2);
    stepper1.setMaxSpeed(300.0);
    stepper1.setAcceleration(100.0);
    stepper2.setMaxSpeed(300.0);
    stepper2.setAcceleration(100.0);
    stepper3.setMaxSpeed(300.0);
    stepper3.setAcceleration(100.0);
    stepper1.run();
    stepper2.run();
    stepper3.run();
}
void setup()
{   
    
    servo.attach(25); //servo attachment to pin25 of ESP32
    Serial.begin(9600);
    Serial.println("Enter data in this style   <HelloWorld, 12, 24.7>  ");
    Serial.println();
    cw1(b_cw1,a1,be);
    


}
 
void loop()
{
   

      if(floatFromPCx != 0 && floatFromPCy != 0 && floatFromPCz != 0){
        if(floatFromPCx > 0 && floatFromPCy > 0){
        cw1(b_cw1,a1,be);
        }
        if(floatFromPCx < 0 && floatFromPCy > 0){
        cw2(b,a1,be);
        }
        if(floatFromPCx < 0 && floatFromPCy < 0){
        cw3(b,a1,be);
        }
        if(floatFromPCx > 0 && floatFromPCy < 0){
        cw4(b,a1,be);
        }
      }

 
      //loop2();
}

void loop2(){
  cw1_back(b_cw1,a1,be);
}
