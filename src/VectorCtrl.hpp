//
// Created by Mayoi on 2019/08/18.
//

#ifndef VECTORCTRL_VECTOR_HPP
#define VECTORCTRL_VECTOR_HPP

#include <cmath>

/*///////////////////////////////////////////////
 * 自作ライブラリは ctrl ネームスペース内に収める
 * //////////////////////////////////////////////
*/

#define STEER_LIMIT 1.0 // ステアリングの最大値, 処理的にこれが最大
#define MAGNITUDE_LIMIT 1.4 // たぶん大きくしても大丈夫
#define EPSILON 0.05 // 浮動小数点の誤差の許容できる大きさ

namespace ctrl {

	//-------------------------------------------------
	// ctrl::Vector class
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
	// ctrl::MoveVector class
	class MoveVector : Vector {
	public:
		MoveVector();

		double getAngle();

		double getMagnitude();

		double getSteer();

		void setAngle(double angle);

		void setMagnitude(double magnitude); // (0~1.4)の範囲で指定

		void setSteer(double steer); // (-1.0~1.0)の範囲で指定

	private:
		double steer;
	};

	//-------------------------------------------------
	// ctrl::WheelAttr class
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
	// ctrl::VectorCalculator class
	class VectorCalculator {
	public:
		VectorCalculator();

		VectorCalculator(double offset);

		virtual void setOffset(double offset);

	protected: // debugするときコメントアウトすること
		void calculateVector(Vector &out, MoveVector &moveVector, WheelAttr &wheelAttr);

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