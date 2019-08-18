//
// Created by Mayoi on 2019/08/18.
//

#include "VectorCtrl.hpp"

//----------------------------------------------------
// ctrl::Vectorの実装
ctrl::Vector::Vector() : angle(0.0), magnitude(0.0) {
}

double ctrl::Vector::getAngle() {
	return this->angle;
}

double ctrl::Vector::getMagnitude() {
	return this->magnitude;
}

void ctrl::Vector::setAngle(double angle) {
	this->angle = angle;
}

void ctrl::Vector::setMagnitude(double magnitude) {
	this->magnitude = magnitude;
}

//----------------------------------------------------
// ctrl::MoveVectorの実装
ctrl::MoveVector::MoveVector() : Vector(), steer(0.0) {

}

double ctrl::MoveVector::getAngle() {
	return Vector::getAngle();
}

double ctrl::MoveVector::getMagnitude() {
	return Vector::getMagnitude();
}

double ctrl::MoveVector::getSteer() {
	return this->steer;
}

void ctrl::MoveVector::setAngle(double angle) {
	Vector::setAngle(angle);
}

void ctrl::MoveVector::setMagnitude(double magnitude) {
	if(magnitude >= 0.0 && magnitude <= MAGNITUDE_LIMIT){
		Vector::setMagnitude(magnitude);
	}else{
		Vector::setMagnitude(0.0);
	}
}

void ctrl::MoveVector::setSteer(double steer) {
	if(fabs(steer) <= STEER_LIMIT) {
		this->steer = steer;
	} else {
		this->steer = 0.0;
	}
}