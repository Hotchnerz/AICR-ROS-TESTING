#include <CytronMotorDriver.h>
#include <DueTimer.h>
#include <Encoder.h>


#define leftEncA 10
#define leftEncB 10

#define rightEncA 10
#define rightEncB 10

#define TICKS_PER_CM 350

CytronMD motor1(PWM_PWM, 11, 10);   // PWM 1A = Pin 3, PWM 1B = Pin 9.
CytronMD motor2(PWM_PWM, 9, 6); // PWM 2A = Pin 10, PWM 2B = Pin 11.

const byte leftChannelA = 25;
const byte leftChannelB = 26;

Encoder leftEnc(leftChannelA, leftChannelB);

volatile long leftEncoder = 0;
volatile long prevLeftEncoder = 0;
volatile long changeLeftEncoder = 0;
volatile double changeLeftCentimeters = 0;
volatile double leftSpeed = 0;

int i =0;

//Florentin Functions
void timerInterrupt(){
  leftEncoder = leftEnc.read();
  changeLeftEncoder = leftEncoder - prevLeftEncoder;
  changeLeftCentimeters = changeLeftEncoder/TICKS_PER_CM;
  leftSpeed = changeLeftCentimeters/0.05; //Distance over time -- time is 50ms

  Serial.print(i);
  Serial.print(",");
  Serial.println(leftSpeed);
}



void setup() {
  Timer1.attachInterrupt(timerInterrupt);
  Timer1.start(50000);
  Serial.begin(250000);

}

void loop() {
  for(i=0; i<100; i+=5){
    //motor.control(i,0);
    delay(2000);
  }

}
