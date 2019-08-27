//
// Created by Mayoi on 2019/08/18.
//

#ifndef VECTORCTRL_MECANUMWHEEL_HPP
#define VECTORCTRL_MECANUMWHEEL_HPP

#include "VectorCtrl.hpp"
#include <cmath>

namespace ctrl {
	class MecanumWheelController final : private VectorCalculator {
	public:
		explicit MecanumWheelController(int wheelNum, double limitWheelSpeed=1.0, double offset = 0);

		~MecanumWheelController(); // メモリ開放

		void setWheelAttr(WheelAttr *wheelAttr);

		void setWheelAttr(double x, double y, double angle, int num);

		void setLimitWheelSpeed(double limitWheelSpeed);

		void setOffset(double offset) override;

		double getWheelSpeed(int num);

		void calcWheelSpeed(VectorMove &moveVector);

	private:
		//配列の長さを取得するテンプレート関数 [xx]に入れたxxが返ってくる
		const int WHEEL_NUM;
		double limitWheelSpeed;
		double maxWheelSpeed;
		double speedFact;
		double *wheelSpeed; // ホイールの数だけ生成
		ctrl::Vector *vecWheel;
		ctrl::WheelAttr *wheelAttr;
	};
}

#endif //VECTORCTRL_MECANUMWHEEL_HPP
