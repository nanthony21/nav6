

#ifndef _IMUN_MOTOR_
#define _IMUN_MOTOR_
#define MAX_SERVO_TIME 2000
#define MIN_SERVO_TIME 1000
#include <Arduino.h>
#include <Servo.h>

const uint16_t timeDifference=MAX_SERVO_TIME-MIN_SERVO_TIME;

class ImunMotor
{
	float throttle;
	Servo motor;
	public:
		uint8_t getThrottle();
		ImunMotor(uint8_t pin);
		void setThrottle(float newThrottle); 
		void escCalibration();
};

uint8_t ImunMotor::getThrottle()
{
	return throttle;
}

ImunMotor::ImunMotor(uint8_t pin)
{
	motor.attach(pin,MIN_SERVO_TIME,MAX_SERVO_TIME);
}

void ImunMotor::setThrottle(float newThrottle) //newThrottle is a value between 0 and 255
{
	throttle=newThrottle;
	motor.writeMicroseconds(MIN_SERVO_TIME+timeDifference*newThrottle);
}

void ImunMotor::escCalibration()
{
	motor.writeMicroseconds(MAX_SERVO_TIME);
	delay(2200);
	motor.writeMicroseconds(MIN_SERVO_TIME);
}

class ImunQuadMotor
{
	float _thrust=0;
	float _yaw=0;
	float _pitch=0;
	float _roll=0;
	ImunMotor &_m1,&_m2,&_m3,&_m4;
	public:
		ImunQuadMotor(ImunMotor &motor1,ImunMotor &motor2,ImunMotor &motor3,ImunMotor &motor4);
		void setYaw(float yaw);
		void setThrust(float thrust);
		void setPitch(float pitch);
		void setRoll(float roll);
		void setMotors();
		void killMotors();
};

ImunQuadMotor::ImunQuadMotor(ImunMotor &motor1,ImunMotor &motor2,ImunMotor &motor3,ImunMotor &motor4):_m1(motor1),_m2(motor2),_m3(motor3),_m4(motor4)//1=front left 2=front right 3=back left 4= back right
{
}

void ImunQuadMotor::setPitch(float pitch){
	_pitch=pitch;
	setMotors();
}
void ImunQuadMotor::setRoll(float roll){
	_roll=roll;
	setMotors();
}

void ImunQuadMotor::setYaw(float yaw){
	_yaw=yaw;
	setMotors();
}
void ImunQuadMotor::setThrust(float thrust)
{
	_thrust=thrust;
	setMotors();
}	
void ImunQuadMotor::setMotors(){
	_m1.setThrottle(_thrust+_yaw+_pitch+_roll);
	_m2.setThrottle(_thrust-_yaw+_pitch-_roll);
	_m3.setThrottle(_thrust-_yaw-_pitch+_roll);	
	_m4.setThrottle(_thrust+_yaw-_pitch-_roll);
}
void ImunQuadMotor::killMotors(){
	_pitch=0;
	_yaw=0;
	_roll=0;
	_thrust=0;
	_m1.setThrottle(0);
	_m2.setThrottle(0);
	_m3.setThrottle(0);	
	_m4.setThrottle(0);
}

#endif /*_IMUN_MOTOR_ */