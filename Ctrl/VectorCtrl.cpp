//
// Created by Mayoi on 2019/08/18.
//

#include "VectorCtrl.hpp"

// ---------------------------------------------
// 正規化
double ctrl::normalize(double target, double min, double max, double center) {
	double val;

	if (target >= center) {
		val = (target - center) / (max - center);
	} else {
		val = -((center - target) / (center - min));
	}
	return val;
}

//----------------------------------------------------
// Ctrl::Vectorの実装
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
// Ctrl::MoveVectorの実装
ctrl::VectorMove::VectorMove() : Vector(), steer(0.0) {

}

double ctrl::VectorMove::getAngle() {
	return Vector::getAngle();
}

double ctrl::VectorMove::getMagnitude() {
	return Vector::getMagnitude();
}

double ctrl::VectorMove::getSteer() {
	return this->steer;
}

void ctrl::VectorMove::setAngle(double angle) {
	Vector::setAngle(angle);
}

void ctrl::VectorMove::setMagnitude(double magnitude) {
	if (magnitude >= 0.0 && magnitude <= SQUARE_ROOT_2 + EPSILON) {
		Vector::setMagnitude(magnitude);
	} else {
		Vector::setMagnitude(0.0);
	}
}

void ctrl::VectorMove::setSteer(double steer) {
	if (fabs(steer) <= STEER_LIMIT) {
		this->steer = steer;
	} else {
		this->steer = 0.0;
	}
}

//----------------------------------------------------------
// Ctrl::WheelAttr

ctrl::WheelAttr::WheelAttr() : x(0.0), y(0.0), angle(0.0) {

}

double ctrl::WheelAttr::getX() {
	return this->x;
}

double ctrl::WheelAttr::getY() {
	return this->y;
}

double ctrl::WheelAttr::getAngle() {
	return this->angle;
}

double ctrl::WheelAttr::getWheelDist() {
	return std::hypot(this->x, this->y);
}

void ctrl::WheelAttr::setX(double x) {
	this->x = x;
}

void ctrl::WheelAttr::setY(double y) {
	this->y = y;
}

void ctrl::WheelAttr::setAngle(double angle) {
	if (angle >= 0.0 && angle <= M_PI) {
		this->angle = angle;
	} else {
		this->angle = 0.0;
	}
}

//----------------------------------------------------------
// Ctrl::VectorCalculator
ctrl::VectorCalculator::VectorCalculator() : VectorCalculator(0.0) {

}

ctrl::VectorCalculator::VectorCalculator(double offset) : steerR(0.0), turnR(0.0), turnSpeed(0.0), cAngle(0.0), cx(0.0),
                                                          cy(0.0), vAngle(0.0), vx(0.0), vy(0.0), speedFact(0.0),
                                                          offset(offset) {

}

void ctrl::VectorCalculator::setOffset(double offset) {
	this->offset = offset;
}

void ctrl::VectorCalculator::calculateVector(ctrl::Vector &vecWheel, ctrl::VectorMove &vecMove,
                                             ctrl::WheelAttr &wheelAttr) {
	//動作の場合分け
	// スティックの操作あり
	if (vecMove.getMagnitude() > EPSILON) {
		// 回転操作なし
		if (std::fabs(vecMove.getSteer()) < EPSILON) {
			// 直進
			vecWheel.setMagnitude(vecMove.getMagnitude());
			vecWheel.setAngle(vecMove.getAngle());

		} // 旋回	(緩旋回と超信地旋回)
		else {
			// オフセットがある超信地旋回は、旋回中心と基準位置が重ならないので緩旋回処理になる。
			// 旋回中心を決め、各ホイールの移動ベクトル個別に計算
			// 旋回半径を求める（wheelAttr.getWheelDist()は中心からホイールまでの距離）
			// 負数だと右旋回
			// steerRは基準位置ベースの旋回半径、turnRは車両中心ベースの旋回半径
			if (std::fabs(vecMove.getSteer()) > 0.95) { // フルステアでは計算がエラーになるので、例外処理
				steerR = 0;
			} else {
				steerR = wheelAttr.getWheelDist() / std::tan(vecMove.getSteer() * M_PI_2);
			}
			// 旋回中心が位置する直線の角度
			cAngle = vecMove.getAngle() + M_PI_2;
			// 旋回中心の座標を求める
			cx = steerR * std::cos(cAngle) + offset;
			cy = steerR * std::sin(cAngle);
			// 車両原点での旋回半径
			turnR = std::sqrt(cx * cx + cy * cy);
			if (vecMove.getSteer() < 0) { // steerRと正負を揃える
				turnR = -turnR;
			}

			// 基準位置で旋回時の速度を規定すると急旋回時に速くなりすぎるため
			// ジョイスティックによる速度指定は、車両外周部の速度とする。
			// そのため半径が小さくなると、基準位置での速度が小さくなる。
			// turnSpdは基準位置の速度（常に正）
			turnSpeed = std::fabs(turnR) / (std::fabs(turnR) + wheelAttr.getWheelDist()) * vecMove.getMagnitude();

			// 移動ベクトルを算出
			// 旋回中心とホイール位置の距離（XY座標）
			vx = wheelAttr.getX() - cx;
			vy = wheelAttr.getY() - cy;

			if ((std::fabs(vx) < 5) && (std::fabs(vy) < 5)) {
				// 旋回中心とホイール位置が重なっているのでゼロベクトルにする
				vecWheel.setMagnitude(0.0);
				vecWheel.setAngle(0.0);

			} // ホイールの移動あり
			else {
				// 旋回中心から見たホイール位置の角度
				vAngle = std::atan2(vy, vx);
				// ホイール位置での移動ベクトルの向き（軌跡円の接線方向）
				vecWheel.setAngle(vAngle + M_PI_2);
				// 旋回半径の差による速度の増減

				if (std::fabs(turnR) > 10) { // 車両中心の旋回半径が0でないので緩旋回
					speedFact = std::sqrt(vx * vx + vy * vy) / turnR;
					// ホイール位置での移動速度
					vecWheel.setMagnitude(turnSpeed * speedFact);

				} else if (vecMove.getSteer() < 0) { // 旋回半径が極めて小さいので超信地旋回（右旋回）
					// 本来はturnRの正負で速度の正負が決まるが、0なのでsteerの正負を使う
					// 右旋回なので速度を負数にする
					vecWheel.setMagnitude(-vecMove.getMagnitude());

				} else { // 左超信地旋回
					vecWheel.setMagnitude(vecMove.getMagnitude());

				}
			}
		}

	} // 停止
	else {
		vecWheel.setMagnitude(0.0);
		vecWheel.setAngle(0.0);
	}
}