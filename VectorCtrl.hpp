//
// Created by Mayoi on 2019/08/16.
//

#ifndef VECTORCTRL_VECTORCTRL_HPP
#define VECTORCTRL_VECTORCTRL_HPP

// #inclide "mbed/mbed.h"
#include <math.h>

/*このクラスのやべぇ点
 * 1. 機能がごっちゃになってる <- ベクトルの計算部と台形制御部と出力を分離
 *
 * ほしい機能は ベクトル演算のみ <- 取り出してクラス化
 *              念のために台形制御も分離しておく
 * */

class VectorCtrl {
public:
	VectorCtrl(DigitalOut *digi, PwmOut *pwm);

	/**
	 * move
	 * @param x [in] x方向のベクトル
	 * @param y [in] y方向のベクトル
	 * @param theta [in] 現在の車体の角度(ラジアン)
	 * @param omega [in] 目標の車体の角度(ラジアン)
	 */
	void move(double x, double y, double theta, double omega);

	void high(double high);

	void low(double low);

	void proportion(double value);

#define DEBUG_REGULAR false
#define DEBUG_INVERT  true
#define MOTOR_OUTPUT_MAX 1.0
#define MOTOR_LOWER_LIMIT 0.05
#define MOTOR_HIGHER_LIMIT 1.0
#define PWMOUT_PROPORTION 0.05

	//inline void move(double x, double y, double theta, double omega);
	//Error: Warning: L6320W: Ignoring --keep command. Cannot find argument 'os_cb_sections'.

protected:
	double result[4];  //calculate result
	double h_limit;    //output higher limit
	double l_limit;    //output lower limit

};

#endif //VECTORCTRL_VECTORCTRL_HPP
