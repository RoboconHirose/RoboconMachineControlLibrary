//
// Created by Mayoi on 2019/08/16.
//

#include "VectorCtrl.hpp"

//コンストラクタ
VectorCtrl::VectorCtrl(DigitalOut *digi, PwmOut *pwm) {
	//initialize
	l_limit = MOTOR_LOWER_LIMIT;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 2; ++j)
			out[i][j] = 0.0;
}

//移動の実行関数
void VectorCtrl::move(double x, double y, double theta, double omega) {
	double _sin, _cos, direct, _fix;

	if (hypot(x, y) < l_limit) {
		//出力の下限以下なら回転の成分しか出力しない
		for (int i = 0; i < 4; ++i) result[i] = omega;
	} else {
		//一時変数
		_sin = sin(theta + M_PI / 4);
		_cos = cos(theta + M_PI / 4);

		//出力をそのまま使うとx, y軸方向の移動の出力が1/root2になるので補正値を計算
		direct = atan2(y, x);
		_fix = sqrt(2.0) / (fabs(sin(theta + direct)) + fabs(cos(theta + direct)));

		//ベクトル演算で各モーター出力の目標値を決定
		result[0] = (-x * _sin + y * _cos) * _fix * (MOTOR_OUTPUT_MAX - fabs(omega)) + omega;
		result[1] = (-x * _cos - y * _sin) * _fix * (MOTOR_OUTPUT_MAX - fabs(omega)) + omega;
		result[2] = (x * _sin - y * _cos) * _fix * (MOTOR_OUTPUT_MAX - fabs(omega)) + omega;
		result[3] = (x * _cos + y * _sin) * _fix * (MOTOR_OUTPUT_MAX - fabs(omega)) + omega;
	}
}

//出力の上限を設定
void VectorCtrl::high(double high) {
	if (high <= l_limit) return; //下限が上限より大きい場合は変えない

	if (high < 0.0 || high > 1.0) {
		h_limit = MOTOR_HIGHER_LIMIT; //範囲外の場合は初期値に設定
	} else {
		h_limit = high; //上限値を設定
	}
}

//出力の下限を設定
void VectorCtrl::low(double low) {
	if (h_limit <= low) return; //下限が上限より大きい場合は変えない

	if (low < 0.0 || low > 1.0) {
		l_limit = MOTOR_LOWER_LIMIT; //範囲外の場合は初期値に設定
	} else {
		l_limit = low;  //下限値を設定
	}
}

//台形制御の加減算の割合を設定
void VectorCtrl::proportion(double value) {
	if (value < 0.0 || value > 1.0) {
		//範囲外の場合は初期値に設定
	}
}

