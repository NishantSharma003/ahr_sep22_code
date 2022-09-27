//left motor
#define left_M1              7                       // PWM outputs to motor driver module
#define left_M2              6


//right motor
#define right_M1             4                       // PWM outputs to motor driver module
#define right_M2             5

int rc_command;

//int rc_command;


int forward_rc_speed = 230;

int rc_max_speed = 180;

//int motor_speed_difference;

void setup() {
    Serial.begin(9600);
    Serial.println("base motor controller");
    Serial3.begin(9600);

//    analogWrite(left_M2, 100);                             // drive motor CW
//    analogWrite(left_M1, 0);
//
//    delay(400);
//    
//    analogWrite(left_M2, 0);                             // drive motor CW
//    analogWrite(left_M1, 0);
    
    
}

void loop() {
  
if(Serial3.available() > 0){

  rc_command = Serial3.read();
  Serial.println(rc_command);
 

  while(rc_command == 52)
  { 
    pwmOut_left(forward_rc_speed);
    pwmOut_right(forward_rc_speed);
    rc_command = Serial3.read();
    Serial.println("forward");
  }

  while(rc_command == 54)
  { 
    pwmOut_left(-rc_max_speed);
    pwmOut_right(-rc_max_speed);
    rc_command = Serial3.read();
    Serial.println("backward");
  }

  while(rc_command == 56)
  { 
    pwmOut_left(0);
    pwmOut_right(0);
    rc_command = Serial3.read();
    Serial.println("stop");
  }

  while(rc_command == 58)
  { 
    pwmOut_left(rc_max_speed);
    pwmOut_right(-rc_max_speed);
    rc_command = Serial3.read();
    Serial.println("left");
  }

  while(rc_command == 60)
  { 
    pwmOut_left(-rc_max_speed);
    pwmOut_right(rc_max_speed);
    rc_command = Serial3.read();
    Serial.println("right");
  }


   
   
  }


}

void pwmOut_left(float out_left) {                                
  if (out_left > 0) {
    analogWrite(left_M2, out_left);                             // drive motor CW
    analogWrite(left_M1, 0);
  }
  else {
    analogWrite(left_M2, 0);
    analogWrite(left_M1, abs(out_left));                        // drive motor CCW
  }
}


void pwmOut_right(float out_right) {                                
  if (out_right > 0) {
    analogWrite(right_M2, out_right);                             // drive motor CW
    analogWrite(right_M1, 0);
  }
  else {
    analogWrite(right_M2, 0);
    analogWrite(right_M1, abs(out_right));                        // drive motor CCW
  }
}
