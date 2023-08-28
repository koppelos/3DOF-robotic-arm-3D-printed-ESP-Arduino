#include <Ps3Controller.h>
#include <Stepper.h>
#include <Servo.h>

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

int pos;
const int steps = 2048;
Stepper stepper1(steps, IN12, IN32, IN22, IN42);
Stepper stepper2(steps, IN11, IN31, IN21, IN41);
Stepper stepper3(steps, IN13, IN33, IN23, IN43);

void setup()
{
    
    servo.attach(25);
    Serial.begin(115200);
    Ps3.begin("44:19:1a:03:04:05");
    Serial.println("Kontroler skomunikowany poprawnie.");

    stepper1.setSpeed(8);
    stepper2.setSpeed(8);
    stepper3.setSpeed(8);

}

void left()
{
  stepper1.setSpeed(8);
  stepper1.step(-3); 
}
void right()
{
  stepper1.setSpeed(8);
  stepper1.step(3);
}
void up()
{
  stepper2.setSpeed(5);
  stepper2.step(-5);
}
void down()
{
  stepper2.setSpeed(5);
  stepper2.step(5);
}
void triangle()
{
  stepper3.setSpeed(5);
  stepper3.step(5);
}
void cross()
{
  stepper3.setSpeed(5);
  stepper3.step(-5);
}
void gripper_open()
{
      pos++;
      servo.write(pos);              
      
}
void gripper_closed()
{
      pos++;
      servo.write(-pos);                
    
}

void loop()
{
    if(Ps3.isConnected()){
        if( Ps3.data.button.left ){    
            left();
        }
         if( Ps3.data.button.right ){
            right();
        }
         if( Ps3.data.button.up ){
            up();
        }
         if( Ps3.data.button.down ){
            down();
        }
        if( Ps3.data.button.cross ){
            cross();  
        }
        if( Ps3.data.button.triangle ){     
            triangle();    
        }
        if( Ps3.data.button.square ){
         
              pos++;
              pos = abs(pos);
              servo.write(pos);
              delay(30);
            }
            
        
        if( Ps3.data.button.circle ){
           
              pos--;
              pos = abs(pos);
              servo.write(pos);
              delay(10);
            }

        }
     
    }
 
