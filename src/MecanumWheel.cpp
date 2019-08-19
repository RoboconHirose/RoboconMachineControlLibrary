//
// Created by Mayoi on 2019/08/18.
//

#include "MecanumWheel.hpp"

ctrl::MecanumWheelController::MecanumWheelController(int wheelNum, double limitWheelSpeed, double offset)
		: WHEEL_NUM(wheelNum), limitWheelSpeed(limitWheelSpeed), maxWheelSpeed(0.0),
		  speedFact(0.0) {
	this->setOffset(offset);
	wheelSpeed = new double[wheelNum];
	vector = new ctrl::Vector[wheelNum];
	wheelAttr = new ctrl::WheelAttr[wheelNum];
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

void ctrl::MecanumWheelController::setWheelAttr(double x, double y, double angle, int num) {
	this->wheelAttr[num % WHEEL_NUM].setX(x);
	this->wheelAttr[num % WHEEL_NUM].setY(y);
	this->wheelAttr[num % WHEEL_NUM].setAngle(angle);
}

double ctrl::MecanumWheelController::getWheelSpeed(int num) {
	return this->wheelSpeed[num % WHEEL_NUM];
}

void ctrl::MecanumWheelController::setOffset(double offset) {
	// オフセットに制限かけたいときに使う
	ctrl::VectorCalculator::setOffset(offset);
}

void ctrl::MecanumWheelController::calcWheelSpeed(ctrl::MoveVector &moveVector) {
	// ホイール属性から各ホイールの駆動速度を算出
	this->maxWheelSpeed = -1; // 最大速度の絶対値を記録

	for (int i = 0; i < this->WHEEL_NUM; ++i) {
		// 移動ベクトルを求める
		ctrl::VectorCalculator::calculateVector(this->vector[i], moveVector, this->wheelAttr[i]);

		if (vector[i].getMagnitude() == 0) { // 駆動せず
			this->wheelSpeed[i] = 0;
		} else { // 移動ベクトルから駆動速度を求める
			// ローラーの傾きの違いを考慮して、ホイール進行方向の速度を算出
			wheelSpeed[i] = limitWheelSpeed * 1.41421356 * sin(vector[i].getAngle() + wheelAttr[i].getAngle()) *
			                vector[i].getMagnitude();

		}
		// 一番速い駆動値を調べる
		if (std::fabs(wheelSpeed[i]) > maxWheelSpeed) {
			maxWheelSpeed = std::fabs(wheelSpeed[i]);
		}
	}

	// 駆動速度が上限値を超えたときの処理
	if (maxWheelSpeed > limitWheelSpeed) {
		// 最大速度を超えるホイールがあるので、減速の係数を求める
		speedFact = (float) limitWheelSpeed / maxWheelSpeed;
		// 速度を調整
		for (int i = 0; i < WHEEL_NUM; i++) {
			wheelSpeed[i] *= speedFact;
		}
	}
}