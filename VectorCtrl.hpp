//
// Created by Mayoi on 2019/08/16.
//

#ifndef VECTORCTRL_VECTORCTRL_HPP
#define VECTORCTRL_VECTORCTRL_HPP

// #inclide "mbed/mbed.h"
#include <math.h>

class VectorCtrl {
public:
	VectorCtrl(DigitalOut *digi, PwmOut *pwm);

	void move(double x, double y, double theta, double omega);
	void high(double high);
	void low(double low);
	void proportion(double value);
	void emergency();
	void debug(bool n, double power);

#define DEBUG_REGULAR false
#define DEBUG_INVERT  true
#define MOTOR_OUTPUT_MAX 1.0
#define MOTOR_LOWER_LIMIT 0.05
#define MOTOR_HIGHER_LIMIT 1.0
#define PWMOUT_PROPORTION 0.05

	//inline void move(double x, double y, double theta, double omega);
	//Error: Warning: L6320W: Ignoring --keep command. Cannot find argument 'os_cb_sections'.

protected:
	DigitalOut *_digi; //DigitalOut pointer
	PwmOut *_pwm;      //PwmOut pointer
	double result[4];  //calculate result
	double out[4][2];  //output value
	double h_limit;    //output higher limit
	double l_limit;    //output lower limit
	double prop;
};

#endif //VECTORCTRL_VECTORCTRL_HPP
