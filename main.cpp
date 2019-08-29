#include <iostream>
#include <fstream>
#include <cmath>
#include "Ctrl/PidController.hpp"

int main() {
	ctrl::PidController pid(0.6, 0.3, 0.9, 3.14, 0.0002);
	double sinWav, sinWavFix = 0, pidv, sum;

	std::ofstream outputcsv("pid.csv");

	outputcsv << "sin,input,fix,sum" << "\n";

	for (int i = 0; i < 70; i++) {
		sinWav = cos(i / 10.0);
		pidv = pid.calculate(sinWav, sinWavFix);
		sum = pidv + sinWavFix;
		sinWavFix += pidv + ((std::sin((i / 6.0) + M_PI_4) / 2.0) + 0.05);


		outputcsv << sinWav << ",";
		outputcsv << sinWavFix << ",";
		outputcsv << pidv << ",";
		outputcsv << sum << "\n";
	}
	outputcsv.close();

	return 0;
}