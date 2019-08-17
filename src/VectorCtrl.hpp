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
	/**
	 *
	 * @param outputPower[out] [0],[1],[2],[3]
	 */
	VectorCtrl(double *outputPower);

	/**
	 * move
	 * @param x [in] x方向のベクトル
	 * @param y [in] y方向のベクトル
	 * @param theta [in] 現在の車体の角度(ラジアン)
	 * @param omega [in] 目標の車体の角度(ラジアン)
	 */
	void calculate(double x, double y, double theta, double omega);

	void high(double high);

	void low(double low);

	//inline void caluc(double x, double y, double theta, double omega);
	//Error: Warning: L6320W: Ignoring --keep command. Cannot find argument 'os_cb_sections'.

protected:
	double *result;  //calculate result
	double h_limit;    //output higher limit
	double l_limit;    //output lower limit
};

#endif //VECTORCTRL_VECTORCTRL_HPP
