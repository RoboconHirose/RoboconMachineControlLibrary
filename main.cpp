#include <iostream>
#include "src/VectorCtrl.hpp"

int main() {
	double power[4];
	double in[4];
	VectorCtrl v(power);
	v.high(265);
	v.low(10);

	bool ableLoop = true;
	while(ableLoop){
		std::cout << "input : x, y, t, o\n";
		std::cin >> in[0] >> in[1] >> in[2] >> in[3];

		v.calculate(in[0], in[1],in[2], in[3]);

		std::cout << "result\n";
		std::cout << "|" << power[0] << "|" << power[1]<< "|" << power[2] << "|" << power[3] << "|" << "\n";

		//----------------------
		std::string buff;
		std::cout << "continue? Y/n\n";
		std::cin >> buff;
		if(buff == "n"){
			ableLoop = false;
		}
	}

	return 0;
}