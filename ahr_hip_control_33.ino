#include <SoftwareSerial.h>

const byte rxPin = 7;
const byte txPin = 8;

SoftwareSerial hipserial (rxPin, txPin);

int hip_control_data; 

int joyrightupdown;
int joyrightside;
int buttontouch;

int throttle,steering;

//#########################################################################

// left motor
int motor_r_1=5;
int motor_r_2=6;

// right motor
int motor_l_1=11;
int motor_l_2=9;


// limit switch
int switch_l_down=A0;
int switch_l_up=3;

int switch_r_up=2;
int switch_r_down=A1;


// potention meter
int pot1=A2;
int pot2=A3;

// motor speed
int motor_left_speed_up = 120;
int motor_left_speed_down = 100;

int motor_right_speed_up = 120;
int motor_right_speed_down = 100; 


int motor_l_speed_up = 120;
int motor_l_speed_down = 120;

int motor_r_speed_up = 120;
int motor_r_speed_down = 90; 


int left_up_limit_switch;

int flag=1;
//###################################################################################

void setup() {
Serial.begin(9600);           // start serial for output

hipserial.begin(9600);        // communication with arm controller
Serial.println("hip pcb started");


pinMode(switch_l_up,INPUT_PULLUP);
pinMode(switch_l_down,INPUT_PULLUP);

pinMode(switch_r_up,INPUT_PULLUP);
pinMode(switch_r_down,INPUT_PULLUP);

pinMode(motor_l_1,OUTPUT);
pinMode(motor_l_2,OUTPUT);

pinMode(motor_r_1,OUTPUT);
pinMode(motor_r_2,OUTPUT);

// test piece $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

analogWrite(motor_l_1,0);
analogWrite(motor_l_2,0);

analogWrite(motor_r_1,0);
analogWrite(motor_r_2,0);

delay(100);

analogWrite(motor_l_1,0);
analogWrite(motor_l_2,0);

analogWrite(motor_r_1,0);
analogWrite(motor_r_2,0);

}

void loop() {
  
//Serial.print("right up    ");  
//Serial.print(digitalRead(switch_r_up));
//Serial.print("    right down    ");  
//Serial.print(digitalRead(switch_r_down));
//Serial.print("    left up    ");  
//Serial.print(digitalRead(switch_l_up));
//Serial.print("    left down    ");  
//Serial.println(digitalRead(switch_l_down));


//right_hip_motor_up(motor_right_speed_up);
//right_hip_motor_down(motor_right_speed_down);
//left_hip_motor_up(motor_left_speed_up);
//left_hip_motor_down(motor_left_speed_down);

if(hipserial.available()>0){

    hip_control_data = hipserial.read();
    Serial.println(hip_control_data);

    if(hip_control_data == 66)
    {
      right_hip_motor_up(0);
      right_hip_motor_down(0);
      left_hip_motor_up(0);
      left_hip_motor_down(0);

      //hip_control_data = hipserial.read();
    }
     if(hip_control_data == 62)
    {
      right_hip_motor_up(motor_right_speed_up);
      left_hip_motor_up(motor_left_speed_up);
      Serial.print("going up");
      //hip_control_data = hipserial.read();
    }
     if(hip_control_data == 64)
     {
      right_hip_motor_down(motor_right_speed_down);
      left_hip_motor_down(motor_left_speed_down);
      Serial.print("going down");
      //hip_control_data = hipserial.read();
     }
     if(hip_control_data == 68)
     {
      right_hip_motor_up(motor_right_speed_up);
      left_hip_motor_down(motor_left_speed_down);
      Serial.print("going left");
      //hip_control_data = hipserial.read();
     }
     if(hip_control_data == 70)
     {
       right_hip_motor_down(motor_right_speed_down);
       left_hip_motor_up(motor_left_speed_up);
       Serial.print("going right");
       //hip_control_data = hipserial.read();
     }
     
     
 }

}


void left_hip_motor_up(int motor_l_speed_up) {
 if (!digitalRead(switch_l_up)) 
 {analogWrite(motor_l_1,0);
  analogWrite(motor_l_2,0);
  }
 else{
  analogWrite(motor_l_1,motor_l_speed_up);
  analogWrite(motor_l_2,0);
//  Serial.print("motor_l_speed_up       ");
//  Serial.println(motor_l_speed_up);
 }  
}

void left_hip_motor_down(int motor_l_speed_down) {
 if (!digitalRead(switch_l_down)) 
 {analogWrite(motor_l_1,0);
  analogWrite(motor_l_2,0);
  }
 else{
  analogWrite(motor_l_1,0);
  analogWrite(motor_l_2,motor_l_speed_down);
//  Serial.print("motor_l_speed_down       ");
//  Serial.println(motor_l_speed_down);
 }  
}


void right_hip_motor_up(int motor_r_speed_up) {
 if (!digitalRead(switch_r_up)) 
 {analogWrite(motor_r_1,0);
  analogWrite(motor_r_2,0);
  }
 else{
  analogWrite(motor_r_1,motor_r_speed_up);
  analogWrite(motor_r_2,0);
//  Serial.print("motor_r_speed_up       ");
//  Serial.println(motor_r_speed_up);
 }  
}

void right_hip_motor_down(int motor_r_speed_down) {
 if (!digitalRead(switch_r_down)) 
 {analogWrite(motor_r_1,0);
  analogWrite(motor_r_2,0);
  }
 else{
  analogWrite(motor_r_1,0);
  analogWrite(motor_r_2,motor_r_speed_down);
//  Serial.print("motor_r_speed_down       ");
//  Serial.println(motor_r_speed_down); 
 }  
}
