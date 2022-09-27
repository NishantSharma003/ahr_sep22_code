#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <SoftwareSerial.h>


const byte rxPin = 5;
const byte txPin = 6;

SoftwareSerial robotserial (rxPin, txPin);

int i2c_data;
int i2c_write_data;

int throttle,steering;

//char data1 = 'a';
//char data_write;


char base_command = 's';
//int base_command =5;
char mystr[5] = "Hello"; //String data

RF24 radio(7, 8);   // nRF24L01 (CE, CSN)
const byte addresses[][6] = {"00001", "00002"};

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  byte leftpotupdown;
  byte leftpotside;
  byte rightpotupdown;
  byte rightpotside;
  byte touchbutton;
};
Data_Package data; //Create a variable with the above structure

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00001
  radio.openReadingPipe(1, addresses[1]); // 00002
  radio.setPALevel(RF24_PA_MIN);

  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);

  robotserial.begin(9600);
  
  resetData();
  Serial.println("receiver started");

  
}
void loop() {
    
  radio.startListening();
  // Check whether there is data to be received
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data
  }
  // Check whether we keep receving data, or we have a connection between the two modules
  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone has a throttle up and we lose connection, it can keep flying unless we reset the values
  }

  // Parse the data from the Joystic 1 to the throttle and steering variables
  throttle = data.rightpotupdown;
  steering = data.rightpotside;  
  
  // Throttle used for forward and backward control
  // Joystick values: 0 to 255; down = 0; middle = 127; up = 255
if (data.touchbutton ==5)
{ 
  //robotserial.write(5);
  if (throttle < 110) {
    Serial.println("backward");
    robotserial.write(54);
  }
  if (throttle > 140) {
    Serial.println("forward");
    robotserial.write(52);
  }
  // If joystick stays in middle the motors are not moving
  if((throttle <140) && (throttle>110))
  { if((steering >110)&&(steering <140))
    { Serial.println("stop");
     robotserial.write(56);
    }
  }
  // Steering used for left and right control
  if (steering < 110) {
     Serial.println("right");
     robotserial.write(58);
  }
  if (steering > 140) {
    Serial.println("left");
    robotserial.write(60);
  }
  
}
if (data.touchbutton ==10){
  //robotserial.write(10);
  //robotserial.write(10);
  if (throttle < 110) {
    Serial.println("down");
    robotserial.write(64);
  }
  if (throttle > 140) {
    Serial.println("up");
    robotserial.write(62);
  }
  // If joystick stays in middle the motors are not moving
  if((throttle <140) && (throttle>110))
  { if((steering >110)&&(steering <140))
    { Serial.println("stop");
     robotserial.write(66);
    }
  }
  // Steering used for left and right control
  if (steering < 110) {
     Serial.println("right");
     robotserial.write(68);
  }
  if (steering > 140) {
    Serial.println("left");
    robotserial.write(70);
  }
}
if (data.touchbutton ==15){
  robotserial.write(15);
}
if (data.touchbutton ==20){
  robotserial.write(20);
}
if (data.touchbutton ==25){
  robotserial.write(25);
}
if (data.touchbutton ==30){
  robotserial.write(30);
}
if (data.touchbutton ==30){
  robotserial.write(30);
}
if (data.touchbutton ==35){
  robotserial.write(35);
}
if (data.touchbutton ==40){
  robotserial.write(40);
}






















  
  // Print the data in the Serial Monitor
  
//  Serial.print("leftup: ");
//  Serial.print(data.leftpotupdown);
//  Serial.print("; leftside: ");
//  Serial.print(data.leftpotside);
  Serial.print("; rightup: ");
  Serial.print(data.rightpotupdown);
  Serial.print("; rightside: ");
  Serial.print(data.rightpotside);
  Serial.print("; button: ");
  Serial.println(data.touchbutton); 

  
}



void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.leftpotupdown = 127;
  data.leftpotside = 127;
  data.rightpotupdown = 127;
  data.rightpotside = 127;
  data.touchbutton = 0;
}
