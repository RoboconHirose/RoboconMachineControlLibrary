//
// Created by Mayoi on 2019/08/18.
//

/**
 * 座標系が マシン前方が x の正方向, マシン左舷が y の正方向
 * となっていていつも使うデカルト座標系+PI/2してやらないといけない
 *
 * 	これマジでメカナムの角度もこれになってるから注意して代入すること
 */

#ifndef VECTORCTRL_VECTOR_HPP
#define VECTORCTRL_VECTOR_HPP

#include <cmath>

/*///////////////////////////////////////////////
 * 自作ライブラリは ctrl ネームスペース内に収める
 * //////////////////////////////////////////////
*/

#define STEER_LIMIT 1.0 // ステアリングの最大値, 処理的にこれが最大
#define SQUARE_ROOT_2 1.41421356 // √2
#define EPSILON 0.05 // 浮動小数点の誤差の許容できる大きさ

namespace ctrl {
	// ---------------------------------------------
	//
	// 正規化 値を-1から1の範囲に変換する
	//

	extern double normalize(double target, double min, double max, double center);

	//-------------------------------------------------
	//
	// ctrl::Vector class
	//
	class Vector {
	public:
		Vector();

		virtual double getAngle();

		virtual double getMagnitude();

		virtual void setAngle(double angle);

		virtual void setMagnitude(double magnitude);

	private:
		double angle;   // ラジアン
		double magnitude; // ベクトルの長さ

	};

	//-------------------------------------------------
	//
	// ctrl::VectorMove class
	//
	class VectorMove final : private ctrl::Vector {
	public:
	    // 入力データは(-1.0〜1.0に正規化すること) / 座標系を変換するプログラムを入れておく

		VectorMove();

		double getAngle() override;

		double getMagnitude() override;

		double getSteer();

		void setAngle(double angle) override;

		void setMagnitude(double magnitude) override; // (0~1.4)の範囲で指定

		void setSteer(double steer); // (-1.0~1.0)の範囲で指定

	private:
		double steer;
	};

	//-------------------------------------------------
	//
	// ctrl::WheelAttr class
	//
	class WheelAttr {
	public:
		WheelAttr();

		double getX();

		double getY();

		double getAngle();

		double getWheelDist();

		void setX(double x);

		void setY(double y);

		void setAngle(double angle);

	private:
		double x;
		double y;
		double angle;
	};

	//-------------------------------------------------
	//
	// ctrl::VectorCalculator class
	//
	class VectorCalculator {
	public:
		VectorCalculator();

		explicit VectorCalculator(double offset);

		virtual void setOffset(double offset);

		void calculateVector(ctrl::Vector &vecWheel, ctrl::VectorMove &vecMove, ctrl::WheelAttr &wheelAttr);

	private:
		double steerR;  // 基準位置からの旋回半径
		double turnR;   // 車両原点位置での旋回半径
		double turnSpeed; // 車両原点位置での旋回速度
		double cAngle;   // 旋回中心が位置する直線の角度
		double cx;      // 旋回中心座標
		double cy;
		double vAngle; // 旋回中心からホイール位置への角度
		double vx;    // 旋回中心からホイール位置への相対座標
		double vy;
		double speedFact;
		double offset; //  車両原点の調整(前+, 後-)
	};
}

#endif //VECTORCTRL_VECTOR_HPP