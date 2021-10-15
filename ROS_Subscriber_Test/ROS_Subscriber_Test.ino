
#include <ArduinoHardware.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>


#define enA 10
#define in1 6
#define in2 7

#define enB 9
#define in3 5
#define in4 4


double w_r=0, w_l=0;

//wheel_rad is the wheel radius ,wheel_sep is
double wheel_rad = 0.0325, wheel_sep = 0.295;


ros::NodeHandle nh;
int lowSpeed = 200;
int highSpeed = 50;
double speed_ang=0, speed_lin=0;

void messageCb( const geometry_msgs::Twist& msg){
  speed_ang = msg.angular.z;
  speed_lin = msg.linear.x;
  
  w_r = (speed_lin/wheel_rad) + ((speed_ang*wheel_sep)/(2.0*wheel_rad));
  w_l = (speed_lin/wheel_rad) - ((speed_ang*wheel_sep)/(2.0*wheel_rad));
}


ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );
void Motors_init();
void MotorL(int Pulse_Width1);
void MotorR(int Pulse_Width2);

void setup(){

 pinMode(enA, OUTPUT);
 pinMode(enB, OUTPUT);
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
 pinMode(in3, OUTPUT);
 pinMode(in4, OUTPUT);

 digitalWrite(enA, LOW);
 digitalWrite(enB, LOW);
 digitalWrite(in1, LOW);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);

 nh.initNode();

 nh.subscribe(sub);

}


void loop(){
 MotorL(w_l*10);

 MotorR(w_r*10);

 nh.spinOnce();

}


void MotorL(int Pulse_Width1){
 if (Pulse_Width1 > 0){

     analogWrite(enA, Pulse_Width1);

     digitalWrite(in1, HIGH);

     digitalWrite(in2, LOW);

 }

 if (Pulse_Width1 < 0){

     Pulse_Width1=abs(Pulse_Width1);

     analogWrite(enA, Pulse_Width1);

     digitalWrite(in1, LOW);

     digitalWrite(in2, HIGH);

 }

 if (Pulse_Width1 == 0){

     analogWrite(enA, Pulse_Width1);

     digitalWrite(in1, LOW);

     digitalWrite(in2, LOW);

 }

}


void MotorR(int Pulse_Width2){


 if (Pulse_Width2 > 0){

     analogWrite(enB, Pulse_Width2);

     digitalWrite(in3, LOW);

     digitalWrite(in4, HIGH);

 }

 if (Pulse_Width2 < 0){

     Pulse_Width2=abs(Pulse_Width2);

     analogWrite(enB, Pulse_Width2);

     digitalWrite(in3, HIGH);

     digitalWrite(in4, LOW);

 }

 if (Pulse_Width2 == 0){

     analogWrite(enB, Pulse_Width2);

     digitalWrite(in3, LOW);

     digitalWrite(in4, LOW);

 }

}
