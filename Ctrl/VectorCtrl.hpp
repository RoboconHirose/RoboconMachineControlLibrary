//
// Created by Mayoi on 2019/08/18.
//

/**
 * @file VectorCtrl.hpp
 */

#ifndef VECTORCTRL_VECTOR_HPP
#define VECTORCTRL_VECTOR_HPP

#include <cmath>

/*///////////////////////////////////////////////
 * 自作ライブラリは Ctrl ネームスペース内に収める
 * //////////////////////////////////////////////
 */

/**
 * @def STEER_LIMIT
 * @brief ステアリングの最大値, 処理的にこれが最大
 */
#define STEER_LIMIT 1.0
/**
 * @def SQUARE_ROOT_2
 * @brief √2
 */
#define SQUARE_ROOT_2 1.41421356
/**
 * @def EPSILON
 * @brief 浮動小数点の誤差の許容できる大きさ
 */
#define EPSILON 0.05


/**
 * @namespace ctrl
 * @brief 制御ライブラリ用ネームスペース
 * @details 制御系のコードを書くときは ctrl ネームスペースに属するようにすること
 */
namespace ctrl {

	/**
	 * @brief 正規化 値を-1から1の範囲に変換する
	 * @param[in] target 変換したいターゲットの値
	 * @param[in] min ターゲットの最小値
	 * @param[in] max ターゲットの最大値
	 * @param[in] center 中央の値
	 * @return 正規化後の値
	 * @note 実装はVectorCtrl.cppに存在している
	 */
	extern double normalize(double target, double min, double max, double center);

	/**
	 * @brief ベクトル量を保持するクラス
	 * @details 極座標でベクトルを保持する. 状況に応じて継承してメソッドをオーバーライドすることを推奨する
	 */
	class Vector {
	public:
		/**
		 * @brief デフォルトコンストラクタ
		 * @details フィールドの初期化をする
		 */
		Vector();

		/**
		 * @brief アクセサー
		 * @return Angle(ラジアン)を返す
		 */
		virtual double getAngle();

		/**
		 * @brief アクセサー
		 * @return Magnitudeを返す
		 */
		virtual double getMagnitude();

		/**
		 * @brief アクセサー
		 * @param[in] angle angleをセットする
		 */
		virtual void setAngle(double angle);

		/**
		 * @brief アクセサー
		 * @param[in] magnitude magnitudeをセットする
		 */
		virtual void setMagnitude(double magnitude);

	private:
		double angle;   // ラジアン
		double magnitude; // ベクトルの長さ

	};


	/**
	 * @brief 移動ベクトルを保持するクラス
	 * @details ベクトル制御クラスに直接渡して構造体のように使う
	 */
	class VectorMove final : private ctrl::Vector {
	public:
		/**
		 * @brief デフォルトコンストラクタ
		 * @details フィールドをすべて初期化する
		 */
		VectorMove();

		/**
		 * @brief アクセサー
		 * @return angle(ラジアン)を返す
		 * @brief 上記で示した座標系からの角度
		 */
		double getAngle() override;

		/**
		 * @brief アクセサー
		 * @return magnitude を返す
		 * @details 範囲は0~√2
		 */
		double getMagnitude() override;

		/**
		 * @brief アクセサー
		 * @return steer(操舵量)を返す
		 * @details 範囲は1.0～-1.0 (正が左方向,負が右方向)
		 */
		double getSteer();

		/**
		 * @brief アクセサー
		 * @param[in] angle angleをセット
		 * @brief 上記で示した座標系からの角度
		 */
		void setAngle(double angle) override;

		/**
		 * @brief アクセサー
		 * @param magnitude magnitudeをセット
		 * @details 範囲は0~√2
		 */
		void setMagnitude(double magnitude) override; // (0~1.4)の範囲で指定

		/**
		 * @brief アクセサー
		 * @param steer steer操舵量をセット
		 * @details 範囲は1.0～-1.0 (正が左方向,負が右方向)
		 */
		void setSteer(double steer); // (-1.0~1.0)の範囲で指定

	private:
		double steer;
	};

	/**
	 * @brief ホイールの位置を指定するクラス
	 * @details 他クラスから集約としてデータクラスとして使ってもらう予定
	 */
	class WheelAttr {
	public:
		/**
		 * @brief デフォルトコンストラクタ
		 * @details フィールドを初期化
		 */
		WheelAttr();

		/**
		 * @brief アクセサー
		 * @return Xを返す
		 */
		double getX();

		/**
		 * @brief アクセサー
		 * @return Yを返す
		 */
		double getY();

		/**
		 * @brief アクセサー
		 * @return angleを返す
		 */
		double getAngle();

		/**
		 * @brief アクセサー
		 * @return ホイール軸から車両原点までの最短距離を返す
		 */
		double getWheelDist();

		/**
		 * @brief アクセサー
		 * @param x Xをセット
		 */
		void setX(double x);

		/**
		 * @brief アクセサー
		 * @param y Yをセット
		 */
		void setY(double y);

		/**
		 * @brief アクセサー
		 * @param angle angleをセット
		 */
		void setAngle(double angle);

	private:
		double x;
		double y;
		double angle;
	};

	/**
	 * @brief 各ホイールの移動ベクトルを算出するクラス
	 * @details 車輪の設置位置に従った移動ベクトルを算出可能
	 * @note 座標系がマシンの中心を原点としてマシンの正面(12時の方向)がX軸の正方向, 右舷(9時の方向)がY軸の正方向になっていて角度もこれに依存している. 注意して扱うこと
	 */
	class VectorCalculator {
	public:
		/**
		 * @brief デフォルトコンストラクタ
		 * @details フィードの初期化
		 */
		VectorCalculator();

		/**
		 * @brief コンストラクタ
		 * @param[in] offset X軸のオフセットを設定
		 */
		explicit VectorCalculator(double offset);

		/**
		 * @brief オフセットの設定
		 * @param[in] offset オフセットを設定
		 */
		virtual void setOffset(double offset);

		/**
		 * @brief 移動ベクトルを駆動ベクトルに変換
		 * @param[out] vectorWheel 駆動ベクトルを代入するクラスを指定
		 * @param[in] vectorMove 移動ベクトルを指定
		 * @param[in] wheelAttr ホイールの位置情報を指定
		 */
		void calculateVector(ctrl::Vector &vectorWheel, ctrl::VectorMove &vectorMove, ctrl::WheelAttr &wheelAttr);

	private:
		double steerR;  // 基準位置からの旋回半径
		double turnR;   // 車両原点位置での旋回半径
		double turnSpeed; // 車両原点位置での旋回速度
		double cAngle;   // 旋回中心が位置する直線の角度
		double cx;      // 旋回中心座標
		double cy;
		double vAngle; // 旋回中心からホイール位置への角度
		double vx;    // 旋回中心からホイール位置への相対座標
		double vy;
		double speedFact; //
		double offset; //  車両原点の調整(前+, 後-)
	};
}

#endif //VECTORCTRL_VECTOR_HPP