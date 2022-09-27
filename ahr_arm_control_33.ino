//  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$                              keep in mind Serial.print is used to send audio commands to raspberry pi

#include <Servo.h>

//***************************                right hand *************************************
Servo r_f1;
Servo r_f2;
Servo r_f3;
Servo r_f4;
Servo r_thm;

Servo r_elborotate;
//Servo r_elboupdown;  // for future

Servo r_sholderupdown;
Servo r_sholderrotate;

//***************************                 left hand *************************************
Servo l_f1;
Servo l_f2;
Servo l_f3;
Servo l_f4;
Servo l_thm;

Servo l_elborotate;
Servo l_elboupdown;

Servo l_sholderupdown;
Servo l_sholderrotate;

// **************************              rc parameters   *********************************** 
int receiver_data;
int flag_left_hand_shake = 0;
int flag_right_hand_shake = 0;


//****************************             parameters for raspberry pi ***********************
int flag_pi_audio_forward = 0;
int flag_pi_audio_welcome = 0;
int flag_pi_audio_bye = 0;


String (command_for_pi);

void setup() {

  Serial.begin(9600);  // raspberry pi audio commands
  Serial2.begin(9600); // receiver pcb
  Serial1.begin(9600); // hip pcb
  Serial3.begin(9600); // base controller pcb

  
  // ****************************       right hand pinout ****************************

  r_f1.attach(22); // index finger
  r_f2.attach(24); // little finger & thumb
  r_f3.attach(30); // next to little finger
  r_f4.attach(28); // middle finger
  r_thm.attach(26); // thumb

  r_elborotate.attach(32);
  //r_elboupdown.attach(34); // for future
  r_sholderupdown.attach(38);
  r_sholderrotate.attach(36);

  // ******************************    left hand pinout *****************************
  
  l_f1.attach(47); // index finger 
  l_f2.attach(49); // little finger & thumb
  l_f3.attach(51); // next to little finger
  l_f4.attach(45); // middle finger
  l_thm.attach(43); // thumb

  l_elborotate.attach(53);
  //l_elboupdown.attach(41); //for future

  l_sholderupdown.attach(37);
  l_sholderrotate.attach(39);

  //**********************************    default position *******************
  
  right_hand_rest();
  left_hand_rest();

  command_for_pi = "wakeup";
  Serial.println(command_for_pi);
  
//  right_hand_shake();
//  left_hand_shake();

}

void loop() {

  if(Serial2.available()>0){

    receiver_data = Serial2.read();

    // *********************   hip control ******************************

    if(receiver_data == 62)
    {
      //Serial.println("up command sent");
      Serial1.write(62);    
    }
    if(receiver_data == 64)
    {
      //Serial.println("down command sent");
      Serial1.write(64);    
    }
    if(receiver_data == 66)
    {
      //Serial.println("stop command sent");
      Serial1.write(66);    
    }
    if(receiver_data == 68)
    {
      //Serial.println("left command sent");
      Serial1.write(68);    
    }
    if(receiver_data == 70)
    {
      //Serial.println("right command sent");
      Serial1.write(70);    
    }

    // *********************   base control ******************************

    if(receiver_data == 52)
    {
      //Serial.println("forward command sent");
      Serial3.write(52);    

      if(flag_pi_audio_forward == 0)
      {
      command_for_pi = "forward";  //################################# pi audio commmand
      Serial.println(command_for_pi);
     
      flag_pi_audio_forward = 1;
      }
      
    }

    
    if(receiver_data == 54)
    {
      //Serial.println("backward command sent");
      Serial3.write(54);    
    }
    if(receiver_data == 56)
    {
      //Serial.println("stop command sent");
      Serial3.write(56);    
    }
    if(receiver_data == 58)
    {
      //Serial.println("left command sent");
      Serial3.write(58);    
    }
    if(receiver_data == 60)
    {
      //Serial.println("right command sent");
      Serial3.write(60);    
    }

    // ************************************** hand control **************************
    
    if(receiver_data == 30)
    {
      if(flag_right_hand_shake == 0){
      //Serial.println("right hand shake");
   
      right_hand_shake();
      flag_right_hand_shake = 1;
       
      }     
    }

    if(receiver_data == 35)
    {
      if(flag_left_hand_shake == 0){
      //Serial.println("left hand shake");
   
      left_hand_shake();
      flag_left_hand_shake = 1;
     
      }     
    }

    if(receiver_data == 40)  //****************      flag reset 
    {
      flag_left_hand_shake = 0;
      flag_right_hand_shake = 0;
      
      flag_pi_audio_forward = 0;
      flag_pi_audio_welcome = 0;
      flag_pi_audio_bye = 0;
    }


    if(receiver_data == 20)  // #########################    welcome
    { 
        if(flag_pi_audio_welcome == 0)
        {
          command_for_pi = "welcome";
          Serial.println(command_for_pi);
          delay(100);
          flag_pi_audio_welcome = 1;
        }
    }

    if(receiver_data == 25)  // #########################    bye
    { 
        if(flag_pi_audio_bye == 0)
        {
          command_for_pi = "bye";
          Serial.println(command_for_pi);
           delay(100);
          flag_pi_audio_bye = 1;
          
        }
      
    }
    

   }
}

// ****************************************       left hand functions **************************
void left_hand_open(){
  l_f1.write(180);
  l_f2.write(0);
  l_f3.write(0);
  l_f4.write(180);
  l_thm.write(170);
}

void left_hand_close(){
  l_f1.write(0);
  l_f2.write(180);
  l_f3.write(180);
  l_f4.write(0);
  l_thm.write(170);
}

void left_hand_rest() {
  left_hand_open();
  
  l_elborotate.write(180);

  l_sholderrotate.write(10);
  l_sholderupdown.write(177);
}

void left_hand_shake(){
    // step 1  rest with close hands 
  
  left_hand_close();
  
  l_elborotate.write(180);
  
  l_sholderrotate.write(10);
  l_sholderupdown.write(180);
  
  receiver_data = Serial2.read();
  delay(1000);
  receiver_data = Serial2.read();
  // step 2  move up 

  left_hand_close();
  
  l_elborotate.write(180);
  
  l_sholderrotate.write(10);
  l_sholderupdown.write(150);
  
  receiver_data = Serial2.read();
  delay(1000);
  receiver_data = Serial2.read();
  // step 3 open hand

  left_hand_open();
  
  l_elborotate.write(180);
  
  l_sholderrotate.write(10);
  l_sholderupdown.write(150);
  
  receiver_data = Serial2.read();
  delay(2000);
  receiver_data = Serial2.read();
  // step 4 close hand

  left_hand_close();
  
  l_elborotate.write(180);
  
  l_sholderrotate.write(10);
  l_sholderupdown.write(150);
  
  receiver_data = Serial2.read();
  delay(1000);
  receiver_data = Serial2.read();
  // step 5 up down

  left_hand_close();
  
  l_elborotate.write(180);
  
  l_sholderrotate.write(10);
  l_sholderupdown.write(145);
  
  receiver_data = Serial2.read();
  delay(1000);
  receiver_data = Serial2.read();

  //******************************            pi audio command in middle of routine 
  command_for_pi = "handshake";
  Serial.println(command_for_pi);
  
  left_hand_close();
  
  l_elborotate.write(180);
  
  l_sholderrotate.write(10);
  l_sholderupdown.write(150);

  receiver_data = Serial2.read();
  delay(1000);
  receiver_data = Serial2.read();

  left_hand_close();
  
  l_elborotate.write(180);
  
  l_sholderrotate.write(10);
  l_sholderupdown.write(145);

  receiver_data = Serial2.read();
  delay(500);
  receiver_data = Serial2.read();
  //step 6 release hand

  left_hand_open();
  
  l_elborotate.write(180);
  
  l_sholderrotate.write(10);
  l_sholderupdown.write(145);

  receiver_data = Serial2.read();
  delay(1500);
  receiver_data = Serial2.read();
  //step 7 back to rest
  
  left_hand_rest();
  receiver_data = Serial2.read();
}

// ****************************************       right hand functions **************************

void right_hand_open(){
  //  // open hand
  r_f1.write(0);
  r_f2.write(0);
  r_f3.write(180);
  r_f4.write(180);
  r_thm.write(60);
  
}

void right_hand_close(){
  //  // close hand
  r_f1.write(180);
  r_f2.write(180);
  r_f3.write(0);
  r_f4.write(0);
  r_thm.write(60);
  
}

void right_hand_rest(){
  right_hand_open();

  r_elborotate.write(150);
  
  r_sholderrotate.write(40);
  r_sholderupdown.write(90);
}


void right_hand_shake(){

  // step 1 rest with close hands
  
  right_hand_close();

  r_elborotate.write(140);
  
  r_sholderrotate.write(40);
  r_sholderupdown.write(90);
  
  receiver_data = Serial2.read();
  delay(1000);
  receiver_data = Serial2.read();
  // step 2 move arm up , straight elbo 

  right_hand_close();

  r_elborotate.write(120);
  
  r_sholderrotate.write(40);
  r_sholderupdown.write(120);
  
  receiver_data = Serial2.read();
  delay(1000); // wait 2 second
  receiver_data = Serial2.read();
  // step 3 open hand

  right_hand_open();

  r_elborotate.write(120);
  
  r_sholderrotate.write(40);
  r_sholderupdown.write(120);

  receiver_data = Serial2.read();
  delay(2000); // wait 2 second
  receiver_data = Serial2.read();
  // step 4 close hand

  right_hand_close();
  
  r_elborotate.write(120);
  
  r_sholderrotate.write(40);
  r_sholderupdown.write(120);

  receiver_data = Serial2.read();
  delay(1000);
  receiver_data = Serial2.read();
  // step 5 up down

  right_hand_close();
  
  r_elborotate.write(120);
  
  r_sholderrotate.write(40);
  r_sholderupdown.write(115);

  receiver_data = Serial2.read();
  delay(1000);  
  receiver_data = Serial2.read();

  //******************************            pi audio command in middle of routine 
  command_for_pi = "handshake";
  Serial.println(command_for_pi);
  
  right_hand_close();

  r_elborotate.write(120);
  
  r_sholderrotate.write(40);
  r_sholderupdown.write(120);

  receiver_data = Serial2.read();
  delay(1000);
  receiver_data = Serial2.read();
  
  right_hand_close();
  
  r_elborotate.write(120);
  
  r_sholderrotate.write(40);
  r_sholderupdown.write(115);

  
  receiver_data = Serial2.read();
  delay(500);
  receiver_data = Serial2.read();
  //step 6 release hand
  
  right_hand_open();

  r_elborotate.write(120);
  
  r_sholderrotate.write(40);
  r_sholderupdown.write(115);

  receiver_data = Serial2.read();
  delay(1500);
  receiver_data = Serial2.read();
  //step 7 back to rest 
  
  right_hand_rest();
  receiver_data = Serial2.read();
}
