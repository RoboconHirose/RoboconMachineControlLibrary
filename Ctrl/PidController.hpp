//
// Created by agatsuma on 19/04/09.
//

#ifndef MYSTEERING_PIDCONTROLLER_HPP
#define MYSTEERING_PIDCONTROLLER_HPP

namespace ctrl {

	const int KP = 0;
	const int KI = 1;
	const int KD = 2;

	/**
	 *
	 * Example:
	 * @code
	 * //////////////////////////////////////////////////////
	 * // インクルード
	 * //////////////////////////////////////////////////////
	 *#include "mbed.h"
	 *
	 * // 以下のどちらかでライブラリをインクルード
	 *#include "Ctrl/PidController.hpp"
	 *#include "Ctrl/Ctrl.hpp"
	 *
	 * //////////////////////////////////////////////////////
	 * // グローバル宣言
	 * //////////////////////////////////////////////////////
	 * // KP:0.6, KI:0.3, KD:0.5, 出力最大値:M_PI, 割り込み周期:0.05秒で宣言
	 * ctrl::PidController pid(0.6, 0.3, 0.9, M_PI, 0.05);
	 *
	 * // 割り込みの宣言
	 * Ticker ticker;
	 *
	 * // PCとシリアル通信して値を確認. ボーレートは38400にする宗教のためこの値
	 * Serial serial(USBTX, USBRX, 38400);
	 *
	 * // pidのターゲットと入力, 出力値を保持する変数
	 * double sinWave=0.0;
	 * double input=0.0;
	 * double output=0.0;
	 * int i=0;
	 *
	 * //////////////////////////////////////////////////////
	 * // 自作関数
	 * //////////////////////////////////////////////////////
	 * // 割り込みで呼び出される関数
	 * void pidCallback(){
	 * 	++i;
	 * 	sinWave=std::sin(i/10.0);
	 *
	 *  // 計算させる(sin波にinputの値を追従させる制御)
	 *	output = pid.calculate(target, input);
	 *
	 *	// ArduinoIDEのシリアルプロッタで補正できているか値を確認
	 *	serial.printf("%lf,%lf,%lf,%lf,\n", sinWave, input, output + input,output);
	 *
	 *	// 揺らぎを加える
	 *	input += output + ((std::sin((i / 6.0) + M_PI_4) / 2.0) + 0.05);
	 * }
	 *
	 * //////////////////////////////////////////////////////
	 * // メイン関数
	 * //////////////////////////////////////////////////////
	 * int main(){
	 *  // 初期化
	 *	// 割り込みを設定
	 *	ticker.attach(pidCallback, 0.05);
	 *
	 *  // メインループ
	 * 	while(1){
	 *		;
	 *  }
	 *
	 * }
	 * @endcode
	 */
	class PidController {
	public:
		/**
		 * @brief コンストラクタ (割り込み使用時はこちらを使う)
		 * @param[in] kp 比例成分の係数
		 * @param[in] ki 積分成分の係数
		 * @param[in] kd 微分成分の係数
		 * @param[in] max_output_value 出力の最大値
		 * @param[in] attach_period_s メンバ関数`calculate`の割り込み周期. 単位は秒
		 */
		PidController(double kp, double ki, double kd, double max_output_value, double attach_period_s=0.0);

		/**
		 * @brief PIDの計算を呼び出す関数
		 * @param[in] targetValue 目標値
		 * @param[in] inputValue  入力値
		 * @return 出力値
		 */
		double calculate(double targetValue, double inputValue);

		/**
		 * @brief PIDの計算を呼び出す関数(割り込みを場合はこちらを使用すること)
		 * @param[in] targetValue 目標値
		 * @param[in] inputValue  入力値
		 * @param[in] max_output_value 前回のこのメンバ関数読み出して今回の処理までかかった時間幅
		 * @return 出力値
		 */
		double calculate(double targetValue, double inputValue, double attach_period_s);

		/**
		 * @brief PIDの各係数を変更できる
		 * @param[in] inputValue 変更値
		 * @param[in] setting ここに, KP, KI, KD を指定してどの係数か選ぶ
		 */
		void setCoefficient(double coefficient, int selector) {
			if (selector >= 0 && selector <= 2) {
				k[selector] = coefficient;
			}
		}

		/**
		 * @brief 擬似的に積分をするための使う時間を指定する
		 * @param[in] attach_period_s 秒が基準です
		 */
		void setAttachPeriodS(double attach_period_s) {
			this->attach_period_s = attach_period_s;
		}

		/**
		 * @brief 出力値の最大値を変更
		 * @param[in] max_output_value 変更したい値を指定する
		 */
		void setMaxOutputValue(double max_output_value) {
			this->attach_period_s = max_output_value;
		}

	private:
		double deviation[2]; // 偏差の保管
		double k[3]; // 係数の指定
		double attach_period_s; // 割り込み周期の設定
		double max_output_value; // 出力の最大値
		double proportionalTerm; // 比例成分の格納
		double integralTerm; // 積分成分の格納
		double differentialTerm; // 微分線分の格納
		double outputValue; // 出力値
		int i; // 制御変数
	};

}


#endif //MYSTEERING_PIDCONTROLLER_HPP
