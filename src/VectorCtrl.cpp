//
// Created by Mayoi on 2019/08/16.
//

#include "VectorCtrl.hpp"

//コンストラクタ
VectorCtrl::VectorCtrl(double *outputPower) {
	result = outputPower;
}

//移動の実行関数
void VectorCtrl::calculate(double x, double y, double theta, double omega) {
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
		result[0] = (-x * _sin + y * _cos) * _fix * (h_limit - fabs(omega)) + omega;
		result[1] = (-x * _cos - y * _sin) * _fix * (h_limit - fabs(omega)) + omega;
		result[2] = (x * _sin - y * _cos) * _fix * (h_limit - fabs(omega)) + omega;
		result[3] = (x * _cos + y * _sin) * _fix * (h_limit - fabs(omega)) + omega;
	}
}

//出力の上限を設定
void VectorCtrl::high(double high) {
	h_limit = high; //上限値を設定
}

//出力の下限を設定
void VectorCtrl::low(double low) {
	l_limit = low;  //下限値を設定
}

