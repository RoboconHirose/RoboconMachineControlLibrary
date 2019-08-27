#include <iostream>
#include <fstream>
#include <cmath>
#include "VectorCtrl/VectorCtrl.hpp"
#include "VectorCtrl/MecanumWheel.hpp"

/*
 * 座標がくそってるから変換必須
 */

enum {
	FR,
	FL,
	BR,
	BL,
};

double d2r(double d) {
	return d / 180.0 * M_PI;
}

int main() {
	ctrl::MecanumWheelController controller(4, 1.0, 0.0);

	// ざひょうの指定するとき気をつけろ!
	controller.setWheelAttr(50, -50, M_PI_4, FR);
	controller.setWheelAttr(50, 50, M_PI_4 * 3, FL);
	controller.setWheelAttr(-50, -50, M_PI_4 * 3, BR);
	controller.setWheelAttr(-50, 50, M_PI_4, BL);

	ctrl::VectorMove move;

	std::ofstream outputcsv("debug.csv");
	outputcsv << "FL,FR,BL,BR" << "\n";

	for (int i = -9; i < 10; ++i) {
		move.setSteer(0.0);
		move.setMagnitude(1.0);
		// + (M_PI/2.0*3.0) で角度の変換ができる
		//move.setAngle(d2r((double) i) + (M_PI/2.0*3.0));
		move.setMagnitude(1.0);
		move.setSteer(i / 10.0);

		controller.calcWheelSpeed(move);

		outputcsv << controller.getWheelSpeed(FL) << ",";
		outputcsv << controller.getWheelSpeed(FR) << ",";
		outputcsv << controller.getWheelSpeed(BL) << ",";
		outputcsv << controller.getWheelSpeed(BR) << "\n";
	}

	outputcsv.close();

	return 0;
}