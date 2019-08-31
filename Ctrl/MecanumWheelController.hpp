/**
 * @file MecanumWheelController.hpp
 */

#ifndef VECTORCTRL_MECANUMWHEEL_HPP
#define VECTORCTRL_MECANUMWHEEL_HPP

#include "VectorCtrl.hpp"
#include <cmath>


namespace ctrl {
	/**
		 * @brief ベクトル制御でメカナムを動かすクラス
		 *
		 * @details 座標系がマシンの中心を原点としてマシンの正面(12時の方向)がX軸の正方向, 左舷(9時の方向)がY軸の正方向になっていて角度もこれに依存している. 注意して扱うこと
		 *
		 * @note 入力の範囲について
		 * @note VectorMove:Magnitude 0.0～√2 まで
		 * @note VectorMove:Angle ラジアンで指定する
		 * @note VectorMove:Steer 1.0～-1.0の範囲で指定. 左方向が正, 右方向が負. 座標系見ればわかる
		 * @note 出力の範囲について
		 * @note limitで指定した大きさになる. 絶対値で±になるが
		 *
		 * Example:
		 * @code
		 * //////////////////////////////////////////////////////
		 * // インクルード
		 * //////////////////////////////////////////////////////
		 *#include "mbed.h"
		 *
		 * // 以下のどちらかでライブラリをインクルード
		 *#include "Ctrl/MecanumWheel.hpp"
		 *#include "Ctrl/Ctrl.hpp"
		 *
		 * //////////////////////////////////////////////////////
		 * // 各種グローバル宣言
		 * //////////////////////////////////////////////////////
		 * // モーター用pwmピン宣言
		 *PwmOut pwm[4] = {
		 *      PwmOut(p26),
         *      PwmOut(p25),
         *      PwmOut(p24),
         *      PwmOut(p23)
         *      };
		 *
		 * // モータードライバー用デジタルピン宣言
		 *DigitalOut md[4] = {
		 * 			DigitalOut(P2_6),
         *      	DigitalOut(P2_7),
         *      	DigitalOut(P2_8),
         *      	DigitalOut(P2_10)
         * 					};
         *
         * // モーターの位置が分かりやすいようにenumすると便利
         * enum{
         * 	FRONT_RIGHT,
         * 	FRONT_LEFT,
         * 	BACK_RIGHT,
         * 	BACK_LEFT,
         * }
         *
         * // メカナム制御ライブラリ宣言 リミットとオフセットは規定値
         * ctrl::MecanumWheelController mwc(4);
         *
         * // 移動ベクトル管理ライブラリ宣言
         * ctrl::VectorMove vecMove;
         *
         * //////////////////////////////////////////////////////
         * // モーター動かす関数
         * //////////////////////////////////////////////////////
         * void move(PwmOut &pwm,DigitalOut &md, double power){
         * 	// 前進と後退で処理わけ
         * 	if(power >= 0.0){ // 正転
         * 		md.write(0);
         * 		pwm.write((float)power);
         * 	}else{ // 逆転
         * 		md.write(1);
         * 		pwm.write((float)(1.0 + power));
         * 	}
         * }
         *
         * //////////////////////////////////////////////////////
         * // メイン関数
         * //////////////////////////////////////////////////////
         * int main(){
         *  // 初期化
         *  for(int i=0;i < 4;++i){
         *  	pwm.write(0.0);
         *  	md.write(0.0);
         *  }
         *  // 座標系を考慮して指定する
         *  // 例) ホイールベース200mm、トレッド300mm <- 中心からホイール取り付け位置までの長さ(mm)を指定
         *  mwc.setWheelAttr( 100.0, -150.0, double angle, FRONT_RIGHT); // 右前輪
         *  mwc.setWheelAttr( 100.0, 150.0, double angle, FRONT_LEFT);   // 左前輪
         *  mwc.setWheelAttr( -100.0, -150.0, double angle, BACK_RIGHT); // 右後輪
         *  mwc.setWheelAttr( -100.0, 150.0, double angle, BACK_LEFT);   // 左後輪
         *
         *  // メインループ
         * 	while(1){
         * 		// コントローラから値を変換するならこんな感じ
         * 		double x = ctrl::normalize(120.0, 0.0, 255.0, 127.0);
         * 		double y = ctrl::normalize(12.0, 0.0, 255.0, 127.0);
         *		double mag = std::hypot(x, y);
         *		double ang = std::atan2(y ,x);
         *
         *		// 強さ. 範囲は0.0～√2,
         *		vecMove.setMagnitude(mag);
         *		// 角度. ラジアンで指定する
         *		vecMove.setAngle(ang);
         *
         *		// ステアリング(回転方向)のベクトルを設定. 範囲は-1.0～+1.0. 左が正
         *		vecMove.setSteer(0.2);
         *
         *
         *		// 駆動ベクトルを算出
         *		mwc.calcVector(vecMove);
         *
         *		for(int i = 0;i < 4;++i){
         *			// モーターを駆動させる
         *			move(pwm[i], md[i], mwc.getWheelSpeed(i));
         *		}
         *  }
         *
         * }
         * @endcode
		 */
	class MecanumWheelController final : private VectorCalculator {
	public:
		/**
		 * @brief コンストラクタ
		 * @param[in] wheelNum  ホイールの数
		 * @param[in] limitWheelSpeed  ホイールの最大出力値. デフォルトは1.0
		 * @param[in] offset 車体の中心のX軸の場所を変更できる. デフォルトは0.0
		 */
		explicit MecanumWheelController(int wheelNum, double limitWheelSpeed = 1.0, double offset = 0.0);

		/**
		 * @brief デストラクタ
		 * @details メモリの動的確保をするのでこれで開放する. オブジェクトをコピーさせると事故るがコピーコンストラクタを設けていない(すみません. 使用する人が管理してください)
		 */
		~MecanumWheelController();

		/**
		 * @brief 各メカナムの位置を中心からの距離で指定する(単位:xy(mm),angle(radian))
		 * @details ベクトルの演算で用いるので計算をする前に指定しておくこと. 座標系をよく確認して設定すること
		 * @param[in] x 原点からホイールの軸までのX方向の長さ(mm)を指定
		 * @param[in] y 原点からホイールの軸までのY方向の長さ(mm)を指定
		 * @param[in] angle どの向きにベクトルが発生するかラジアンで指定する
		 * @param[in] num このホイールが何番目のものなのか指定する
		 */
		void setWheelAttr(double x, double y, double angle, int num);

		/**
		 * @brief ホイールの最大速度を指定
		 * @param[in] limitWheelSpeed ホイールの最大速度を指定
		 */
		void setLimitWheelSpeed(double limitWheelSpeed); // ホイールの最大速度を指定

		/**
		 * @brief オフセットを指定
		 * @param offset オフセットを(mm)で指定. X軸方向のみ有効
		 */
		void setOffset(double offset) override;

		/**
		 * @brief 各ホイールの駆動ベクトルを取得
		 * @param[in] num どのホイールか指定
		 * @return 駆動ベクトルが返り値となる
		 */
		double getWheelSpeed(int num); // 各ホイールのスピード(出力値)を取得

		/**
		 * @brief 移動ベクトルを駆動ベクトルに変換
		 * @param[in] moveVector 移動ベクトルを指定したVectorMoveクラスを渡す
		 * @details VectorMoveに指定できる最大値は
		 */
		void calcWheelSpeed(VectorMove &moveVector); // 移動ベクトルを渡して駆動ベクトルを計算させる

	private:
		const int WHEEL_NUM;
		double limitWheelSpeed;
		double maxWheelSpeed;
		double speedFact;
		double *wheelSpeed;
		ctrl::Vector *vectorWheel;
		ctrl::WheelAttr *wheelAttr;
	};
}

#endif //VECTORCTRL_MECANUMWHEEL_HPP
