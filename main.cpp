#include <iostream>
#include <cmath>
#include "src/VectorCtrl.hpp"

int main(){

	//------------------------------------------------------------
	// ctrl::Vector debug <- O
	/*
	ctrl::Vector v;

	std::cout << v.getAngle() << ":" << v.getMagnitude() << "\n";
	*/

	//------------------------------------------------------------
	// ctrl::MoveVector debug <- O
	/*
	ctrl::MoveVector mv;

	for (int i = -20; i < 20; ++i) {
		mv.setAngle(i / 10.0);
		mv.setMagnitude(i / 10.0);
		mv.setSteer(i / 10.0);

		std::cout << "|" << mv.getAngle() << "|" << mv.getMagnitude() << "|" << mv.getSteer() << "|\n";
	}
	 */

	//-------------------------------------------------------------
	// ctrl::WheelAttr debug <- O
	/*
	ctrl::WheelAttr wheelAttr;

	for (int i = -40; i < 40; ++i) {
		wheelAttr.setAngle(i / 10.0);
		wheelAttr.setX(i / 10.0);
		wheelAttr.setY(i / 10.0);

		std::cout << "|" << wheelAttr.getX() << "|" << wheelAttr.getY() << "|" << wheelAttr.getAngle() << "|"
		          << wheelAttr.getWheelDist() << "|\n";
	}
	*/

	//-------------------------------------------------------------
	// ctrl::VectorCalculator debug

	ctrl::VectorCalculator vc;
	ctrl::Vector v;
	ctrl::MoveVector mv;
	ctrl::WheelAttr va[2];

	va[0].setX(50);
	va[0].setY(50);
	va[0].setAngle(M_PI_4);

	va[1].setX(-50);
	va[1].setY(-50);
	va[1].setAngle(M_PI_4);

	for (int i = 0; i < 20; ++i) {
		mv.setMagnitude(i / 10.0);
		mv.setAngle(M_PI_4);
		mv.setSteer(i/20.0);
		vc.calculateVector(v,mv,va[0]);
		std::cout << "[0]mag:" << v.getMagnitude() << "| angl:" << v.getAngle() << "\n";
		vc.calculateVector(v,mv,va[1]);
		std::cout << "[1]mag:" << v.getMagnitude() << "| angl:" << v.getAngle() << "\n";
	}

	return 0;
}