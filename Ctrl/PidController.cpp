//
// Created by agatsuma on 19/04/09.
//
#include "PidController.hpp"

ctrl::PidController::PidController(double kp, double ki, double kd, double max_output_value, double attach_period_s) {
	this->deviation[0] = 0.0;
	this->deviation[1] = 0.0;
	this->k[0]=kp;
	this->k[0]=ki;
	this->k[0]=kd;
	this->max_output_value=max_output_value;
	this->attach_period_s=attach_period_s;
	this->proportionalTerm=0.0;
	this->integralTerm=0.0;
	this->differentialTerm=0.0;
	this->outputValue=0.0;
	this->i=0;
}

double ctrl::PidController::calculate(double targetValue, double inputValue, double attach_period_s) {
	this->attach_period_s = attach_period_s;
	return calculate(targetValue, inputValue);
}

double ctrl::PidController::calculate(double targetValue, double inputValue) {
	// 初期化
	deviation[0] = 0.0;
	// 今回の偏差値を格納
	deviation[0] = targetValue - inputValue;

	// 残留偏差を計算する. 台形公式を用いて積分の近似を取る
	integralTerm = attach_period_s * (deviation[1] + deviation[0]) / 2;

	// 出力値をオーバーしていたら丸め込む
	if (inputValue <= -max_output_value && inputValue >= max_output_value) {
		integralTerm = (inputValue < 0) ? -max_output_value : max_output_value;
	}

	// 各項の計算
	proportionalTerm = k[KP] * deviation[0];  // 比例成分 : 目標値まで一気に近づけてくれる働き
	integralTerm = k[KI] * integralTerm; // 積分成分 : 残留偏差(比例制御の式で出る誤差)埋める働き
	differentialTerm = k[KD] * (deviation[1] - deviation[0]); // 微分成分 : 机にぶつかったときなどに出る大きな誤差を瞬時に補正する働き

	// 各項を足して出力を決定
	outputValue = proportionalTerm + integralTerm + differentialTerm;

	// 差分を記録
	deviation[1] = deviation[0];

	// 出力処理 もっと合理化できそう
	if (outputValue > max_output_value) {
		return max_output_value;
	} else if (outputValue < -max_output_value) {
		return -max_output_value;
	}

	return outputValue;
}