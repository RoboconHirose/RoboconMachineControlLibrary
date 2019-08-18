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

namespace ctrl {

	class Vector {
	public:
		Vector();

		virtual double getAngle();

		virtual double getMagnitude();

	protected:
		virtual void setAngle(double angle);

		virtual void setMagnitude(double magnitude);

	private:
		double angle;   // ラジアン
		double magnitude; // ベクトルの長さ

	};

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
}

#endif //VECTORCTRL_VECTOR_HPP