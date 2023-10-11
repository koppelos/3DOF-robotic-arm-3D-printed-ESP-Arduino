#include <Stepper.h>
#include <Servo.h>
#include <math.h>
#include <stdio.h>

Servo servo;
//predefine ESP32 pins with 28BYJ-48 stepper motors, 3 stepper motors in use
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


const int steps = 2048; //number of steps stepper motor definition
//steppers define
Stepper stepper1(steps, IN12, IN32, IN22, IN42); 
Stepper stepper2(steps, IN11, IN31, IN21, IN41);
Stepper stepper3(steps, IN13, IN33, IN23, IN43);

//the first carthesian desirable coordinates (POS1)
float floatFromPCx = -80.0;
float floatFromPCy = 80.0;     
float floatFromPCz = 80.0;

//the second carthesian desirabled cordinates (POS2)
float x2 = 70.0 ;
float y2 = 80.0;
float z2 = 50.0;



float b = atan2(floatFromPCy,floatFromPCx) * (180/3.1415);   
float b_cw1 = atan2(floatFromPCx,floatFromPCy)*(180/3.1415);
float l = sqrt(floatFromPCx*floatFromPCx + floatFromPCy*floatFromPCy);
float h = sqrt(l*l + floatFromPCz*floatFromPCz);

float phi = atan(floatFromPCz/l)* (180/3.1415);
float theta = acos((h/2)/90) * (180 / 3.1415);

float a1 = phi + theta;  //angle for first part of arm
float a2 = phi - theta;  //angle for second part of arm

float ga = 180.0 - (90.0+theta);
float be = 180.0-(2*ga); //the angle presented in degrees, not radians

float ang1 = (b * 5.66)-36; //-36 is the correction for the shift resulting from the structure of the arm
float ang1_cw1 = (b_cw1 * 5.66)-36; //-36 is the shift correction
float ang2 = ((90 - a1) * 5.66)-20; //-20 is the shift correction
float ang3 = (be * 5.66)+70;// +70 is the shift correction

float cw_offset = 90*5.66; //offset deg2rad

float step1_cw2 = -(ang1-cw_offset); //value ang1 for cw2
float step1_cw3 = -(ang1+cw_offset); //value ang1 for cw3
float step1_cw4 = -(ang1+cw_offset); //value ang1 for cw4



float b_2 = atan2(y2,x2) * (180/3.1415);
float b_2_cw1 = atan2(x2,y2) * (180/3.1415);
float l_2 = sqrt(x2*x2 + y2*y2);
float h_2 = sqrt(l_2*l_2 + z2*z2);
float phi_2 = atan(z2/l_2)* (180/3.1415);
float theta_2 = acos((h_2/2)/90) * (180 / 3.1415);
float a1_2 = phi_2 + theta_2;
float a2_2 = phi_2 - theta_2;  //angle for second part of arm
float ga_2 = 180.0 - (90.0+theta_2);
float be_2 = 180.0-(2*ga_2); //in degrees
float ang1_2 = (b_2 * 5.66)-36;
float ang1_2_cw1 = (b_2_cw1 * 5.66)-36; //46   ta poprawka dziala tylko do tylu a nie do przodu
float ang2_2 = ((90 - a1_2) * 5.66)-20;//28
float ang3_2 = (be_2 * 5.66)+70;//+110

float cw2_ang1_2 = -(ang1_2-cw_offset);
float cw3_ang1_2 = -(ang1_2+cw_offset);
float cw4_ang1_2 = -(ang1_2+cw_offset);



float step1_cw2_2 = -(ang1_2-cw_offset);
float step1_cw3_2 = -(ang1_2+cw_offset);
float step1_cw4_2 = -(ang1_2+cw_offset);


void cw1(float b, float a1, float be) // dla ruchu ktory wykracza poza ta sama cwiartke
{
    stepper1.step(ang1_cw1);
    stepper2.step(ang2);
    stepper3.step(-ang3);
    delay(4000);
    stepper1.step(-ang1_cw1);
    
}
void cw2(float b, float a1, float be)
{   
    stepper1.step(step1_cw2);
    stepper2.step(ang2);
    stepper3.step(-ang3);
    delay(4000);
    stepper1.step(-step1_cw2);
    
}
void cw3(float b, float a1, float be)
{   
    stepper1.step(step1_cw3);
    stepper2.step(-ang2);
    stepper3.step(ang3);
    delay(4000);
    stepper1.step(-step1_cw3);
    
}
void cw4(float b, float a1, float be)
{   
    stepper1.step(step1_cw4);
    stepper2.step(-ang2);
    stepper3.step(ang3);
    delay(4000);
    stepper1.step(-step1_cw4);
    
}

void same_quart1(float b, float a1, float be, float b_2, float a1_2, float be_2)  // dla ruchu w tej samej cwiartce
{ 
    stepper1.step(ang1_cw1);
    stepper2.step(ang2);
    stepper3.step(-ang3);
    delay(4000);
    stepper1.step(-ang1_cw1+ang1_2_cw1);
    stepper3.step(-(ang3_2-ang3));
    stepper2.step(ang2_2-ang2);
    delay(4000);
    stepper1.step(-ang1_2_cw1);
    stepper2.step(-ang2_2);
    stepper3.step(ang3_2);

    
}

void same_quart2(float b, float a1, float be, float b_2, float a1_2, float be_2)
{    
    stepper1.step(step1_cw2);
    stepper2.step(ang2);
    stepper3.step(-ang3);
    delay(4000);
    stepper1.step(-step1_cw2 + cw2_ang1_2);
    stepper3.step(-(ang3_2-ang3));
    stepper2.step(ang2_2-ang2);
    delay(4000);
    stepper1.step(-cw2_ang1_2);
    stepper2.step(-ang2_2);
    stepper3.step(ang3_2);
}

void same_quart3(float b, float a1, float be, float b_2, float a1_2, float be_2)
{
    stepper1.step(step1_cw3);
    stepper2.step(-ang2);
    stepper3.step(ang3);
    delay(4000);
    stepper1.step(-step1_cw3 + cw3_ang1_2);
    stepper3.step(ang3_2-ang3);
    stepper2.step(-(ang2_2-ang2));
    delay(4000);
    stepper1.step(-cw3_ang1_2);
    stepper2.step(ang2_2);
    stepper3.step(-ang3_2);
}

void same_quart4(float b, float a1, float be, float b_2, float a1_2, float be_2)
{
    stepper1.step(step1_cw4);
    stepper2.step(-ang2);
    stepper3.step(ang3);
    delay(4000);
    stepper1.step(-step1_cw4 + cw4_ang1_2);
    stepper3.step(ang3_2-ang3);
    stepper2.step(-(ang2_2-ang2));
    delay(4000);
    stepper1.step(-cw4_ang1_2);
    stepper2.step(ang2_2);
    stepper3.step(-ang3_2);
    
}

void cw1_2(float b_2, float a1_2, float be_2)
{
    stepper1.step(ang1_2_cw1);
    stepper3.step(-(ang3_2-ang3));
    stepper2.step(ang2_2-ang2);
    delay(2000);
    stepper1.step(-ang1_2_cw1);
    stepper2.step(-ang2_2);
    stepper3.step(ang3_2);
}

void cw2_2(float b_2, float a1_2, float be_2)
{
    stepper1.step(step1_cw2_2);
    stepper3.step(-(ang3_2-ang3));
    stepper2.step(ang2_2-ang2);
    delay(2000);
    stepper1.step(-step1_cw2_2);
    stepper2.step(-ang2_2);
    stepper3.step(ang3_2);
}

void cw3_2(float b_2, float a1_2, float be_2)
{
    stepper1.step(step1_cw3_2);
    stepper3.step(ang3_2-ang3);
    stepper2.step(-ang2_2-(-ang2)); 
    delay(1000);
    stepper1.step(-step1_cw3_2);
    stepper2.step(ang2_2);
    stepper3.step(-ang3_2);
}

void cw4_2(float b_2, float a1_2, float be_2)
{
    stepper1.step(step1_cw4_2);
    stepper3.step(ang3_2-ang3);
    stepper2.step(-ang2_2-(-ang2)); 
    delay(1000);
    stepper1.step(-step1_cw4_2);
    stepper2.step(ang2_2);
    stepper3.step(-ang3_2);
}

void change_sign_front_to_back(float b_2, float a1_2, float be_2){

  stepper3.step(ang3+ang3_2);
  stepper2.step(-ang2-ang2_2);
  delay(2000);
  stepper3.step(-ang3_2);
  stepper2.step(ang2_2);  
}

void change_sign_back_to_front(float b_2, float a1_2, float be_2){

  stepper3.step(-ang3-ang3_2);
  stepper2.step(ang2+ang2_2);
  delay(2000);
  stepper3.step(ang3_2);
  stepper2.step(-ang2_2);
  
}





void setup()
{       
    servo.attach(25);
    Serial.begin(9600);

    stepper1.setSpeed(5);
    stepper2.setSpeed(5);
    stepper3.setSpeed(5);

     

  

    if(floatFromPCx != 0 && floatFromPCy != 0 && floatFromPCz != 0 && x2 != 0 && y2 != 0 && z2 != 0){    
      if(floatFromPCx > 0 && floatFromPCy > 0 && x2 > 0 && y2 > 0)
      {
        same_quart1(b,a1,be,b_2,a1_2,be_2);  
      }
      if(floatFromPCx < 0 && floatFromPCy < 0 && x2 < 0 && y2 < 0)
      {
        same_quart3(b,a1,be,b_2,a1_2,be_2);  
      }
      if(floatFromPCx < 0 && floatFromPCy > 0 && x2 < 0 && y2 > 0)
      {
        same_quart2(b,a1,be,b_2,a1_2,be_2);  
      }
      if(floatFromPCx > 0 && floatFromPCy < 0 && x2 > 0 && y2 < 0)
      {
        same_quart4(b,a1,be,b_2,a1_2,be_2);  
      }
    }

    if(floatFromPCx != 0 && floatFromPCy != 0 && floatFromPCz != 0 ){
              if((floatFromPCx > 0 && floatFromPCy > 0) && ((x2 <0 && y2<0) || (x2<0 && y2>0) || (x2>0 && y2<0)) ){
                cw1(b,a1,be);
                }
              if((floatFromPCx < 0 && floatFromPCy > 0) && ((x2>0 && y2<0) || (x2 <0 && y2<0) || (x2>0 && y2>0))){
                cw2(b,a1,be);
                }
              if((floatFromPCx < 0 && floatFromPCy < 0) && ((x2>0 && y2>0) || (x2<0 && y2>0) || (x2>0 && y2<0))){
                cw3(b,a1,be);
                }
              if((floatFromPCx > 0 && floatFromPCy < 0) && ((x2<0 && y2>0) || (x2>0 && y2>0) || (x2 <0 && y2<0))){
                cw4(b,a1,be);
                }
               
        
                 if(x2 != 0 && y2 != 0 && z2 != 0 ){ // tutaj powinien najpier wykonac sie kod normalny cw1-4 a potem ten na cw1_2-4_2
                     
                     if(x2 > 0 && y2 > 0 && floatFromPCx<0 && floatFromPCy>0){ //2
                      cw1_2(b_2,a1_2,be_2);
                      }
                     if (x2 > 0 && y2 > 0 && floatFromPCx <0 && floatFromPCy<0){ //3
                      stepper1.step(ang1_2_cw1);

                      change_sign_back_to_front(b_2,a1_2, be_2);
                      stepper1.step(-ang1_2_cw1);
                    }
                     if (x2 > 0 && y2 > 0 && floatFromPCx>0 && floatFromPCy<0){ //4
                      stepper1.step(ang1_2_cw1);
                      change_sign_back_to_front(b_2,a1_2, be_2);
                      stepper1.step(-ang1_2_cw1);
                    }


                    
                    if(x2 < 0 && y2 > 0 && floatFromPCx>0 && floatFromPCy>0){ //1
                      cw2_2(b_2,a1_2,be_2);
                      }
                    if (x2 < 0 && y2 > 0 && floatFromPCx<0 && floatFromPCy<0){ //3
                      stepper1.step(step1_cw2_2);
                      change_sign_back_to_front(b_2,a1_2, be_2);
                      stepper1.step(-step1_cw2_2);
                    }

                    if (x2 < 0 && y2 > 0 && floatFromPCx>0 && floatFromPCy<0){ //4
                      stepper1.step(step1_cw2_2);
                      change_sign_back_to_front(b_2,a1_2, be_2);
                      stepper1.step(-step1_cw2_2);
                    }


                    
                    if(x2 < 0 && y2 < 0 && floatFromPCx>0 && floatFromPCy<0){ //4
                      cw3_2(b_2,a1_2,be_2);
                      }

                    if(x2 < 0 && y2 < 0 && floatFromPCx>0 && floatFromPCy>0){ //1
                      stepper1.step(step1_cw3_2);
                      change_sign_front_to_back(b_2,a1_2, be_2);
                      stepper1.step(-step1_cw3_2);
                    }
 
                    if(x2 < 0 && y2 < 0 && floatFromPCx<0 && floatFromPCy>0){ //2
                      stepper1.step(step1_cw3_2);
                      change_sign_front_to_back(b_2,a1_2, be_2);
                      stepper1.step(-step1_cw3_2);
                    }


                    
                    if(x2 > 0 && y2 < 0 && floatFromPCx<0 && floatFromPCy<0){ //3
                      cw4_2(b_2,a1_2,be_2);
                      }

                    if(x2 > 0 && y2 < 0 && floatFromPCx>0 && floatFromPCy>0){//1
                      stepper1.step(step1_cw4_2);
                      change_sign_front_to_back(b_2,a1_2, be_2);
                      stepper1.step(-step1_cw4_2);
                    }
                      

                    if(x2 > 0 && y2 < 0 && floatFromPCx<0 && floatFromPCy>0){//2
                      stepper1.step(step1_cw4_2);
                      change_sign_front_to_back(b_2,a1_2, be_2);
                      stepper1.step(-step1_cw4_2);
                    }
                     
       }
    }
}  


void loop()
{
   
}
