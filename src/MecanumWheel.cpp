//
// Created by Mayoi on 2019/08/18.
//

#include "MecanumWheel.hpp"

ctrl::MecanumWheelController::MecanumWheelController(int wheelNum, double limitWheelSpeed, double offset)
		: WHEEL_NUM(wheelNum), limitWheelSpeed(limitWheelSpeed), maxWheelSpeed(0.0),
		  speedFact(0.0) {
	this->setOffset(offset);
	wheelSpeed = new double[WHEEL_NUM];
	vector = new ctrl::Vector[WHEEL_NUM];
	wheelAttr = new ctrl::WheelAttr[WHEEL_NUM];
}

ctrl::MecanumWheelController::~MecanumWheelController() {
	// メモリ開放
	delete[] wheelSpeed;
	delete[] vector;
	delete[] wheelAttr;
}

void ctrl::MecanumWheelController::setWheelAttr(ctrl::WheelAttr *wheelAttr) {
	for (int i = 0; i < WHEEL_NUM << ++i;) {
		this->wheelAttr[i] = wheelAttr[i];
	}
}

double ctrl::MecanumWheelController::getWheelSpeed(int num) {
	return this->wheelSpeed[num % WHEEL_NUM];
}

void ctrl::MecanumWheelController::calcurateWheelSpeed(ctrl::MoveVector &moveVec) {
	// ホイール属性から各ホイールの駆動速度を算出
	maxWheelSpeed = -1; // 最大速度の絶対値を記録
}

void ctrl::MecanumWheelController::setWheelAttr(ctrl::WheelAttr wheelAttr, int num) {
	this->wheelAttr[num%WHEEL_NUM] = wheelAttr;
}

void ctrl::MecanumWheelController::setOffset(double offset) {
	// オフセットに制限かけたいときに使う
	ctrl::VectorCalculator::setOffset(offset);
}