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

	return 0;
}