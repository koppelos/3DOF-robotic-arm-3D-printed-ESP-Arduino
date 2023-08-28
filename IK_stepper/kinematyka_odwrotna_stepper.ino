#include <Stepper.h>
#include <Servo.h>
#include <math.h>
#include <stdio.h>

//Kinematyka odwrotna, biblioteka stepper

Servo servo;

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

Stepper stepper1(steps, IN12, IN32, IN22, IN42);
Stepper stepper2(steps, IN11, IN31, IN21, IN41);
Stepper stepper3(steps, IN13, IN33, IN23, IN43);


float Px = -80.0;    
float Py = -80.0;          
float Pz = 5.0;

float Beta = atan2(Py,Px) * (180/3.1415);
float Beta_cw1 = atan2(Px,Py)*(180/3.1415);
float l = sqrt(Px*Px + Py*Py);
float h = sqrt(l*l + Pz*Pz);

float phi = atan(Pz/l)* (180/3.1415);
float theta = acos((h/2)/90) * (180 / 3.1415);

float Q1 = phi + theta;
float a2 = phi - theta;
float delta = 180.0 - (90.0+theta);
float psi = 180.0-(2*delta);

float Sil_1 = (Beta * 5.653);
float Sil_1_cw1 = (Beta_cw1 * 5.653);
float Sil_2 = ((90 - Q1) * 5.653);
float Sil_3 = (psi * 5.653);


float cw_offset = 90*5.653;


void cw1(float Beta_cw1, float Q1, float psi)
{   delay(1000);    
    stepper1.step((Sil_1_cw1+55));
    stepper2.step((Sil_2));
    stepper3.step((-Sil_3));
    delay(4000);
    stepper3.step((Sil_3));
    stepper2.step((-Sil_2));
    stepper1.step((-Sil_1_cw1-55));
}
void cw2(float Beta, float Q1, float psi)
{   delay(1000);
    stepper1.step(-(Sil_1-cw_offset)+55);
    stepper2.step(Sil_2);
    stepper3.step(-Sil_3);
    delay(4000);
    stepper3.step(Sil_3);
    stepper2.step(-Sil_2);
    stepper1.step(Sil_1-cw_offset-55);
}
void cw3(float Beta, float Q1, float psi)
{   delay(1000);
    stepper1.step(-(Sil_1+cw_offset)-40);
    stepper2.step(-Sil_2);
    stepper3.step(Sil_3+70);
    delay(4000);

    stepper3.step(-Sil_3-70);
    stepper2.step(Sil_2);
    stepper1.step((Sil_1+cw_offset)+40);
}
void cw4(float Beta, float Q1, float psi)
{   delay(1000);
    stepper1.step(-(Sil_1+cw_offset)-80);
    stepper2.step(-Sil_2);
    stepper3.step(Sil_3+80);
    delay(4000);
    stepper3.step(-Sil_3-80);
    stepper2.step(Sil_2);
    stepper1.step(Sil_1+cw_offset+80);
}
void setup()
{   
    
    servo.attach(25);
    Serial.begin(9600);
    Serial.println("Enter data in this style   <HelloWorld, 12, 24.7>  ");
    Serial.println();
    stepper1.setSpeed(5);
    stepper2.setSpeed(5);
    stepper3.setSpeed(5);
    

    if(Px != 0 && Py != 0 && Pz != 0){
      if(Px > 0 && Py > 0){
         cw1(Beta_cw1,Q1,psi);
      }
      if(Px < 0 && Py > 0){
         cw2(Beta,Q1,psi);
      }
      if(Px < 0 && Py < 0){
         cw3(Beta,Q1,psi);
      }
      if(Px > 0 && Py < 0){
         cw4(Beta,Q1,psi);
      }
    }
}
 
void loop()
{
    Serial.print("X ");
    Serial.println(Px);
    Serial.print("Y ");
    Serial.println(Py);
    Serial.print("Z ");
    Serial.println(Pz);

    Serial.print("test cw 1");
    Serial.print(" ");
    Serial.print("Obrot sil_1: ");
    Serial.println(Sil_1_cw1);
    Serial.print("Obrot sil_2: ");
    Serial.println(Sil_2);
    Serial.print("Obrot sil_3: ");
    Serial.println(Sil_3);

}
