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

	return 0;
}