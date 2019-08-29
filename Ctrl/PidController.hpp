//
// Created by agatsuma on 19/04/09.
//

#ifndef MYSTEERING_PIDCONTROLLER_HPP
#define MYSTEERING_PIDCONTROLLER_HPP

namespace ctrl {

    const int KP = 0;
    const int KI = 1;
    const int KD = 2;

    class PidController {
    public:/**
         * @brief コンストラクタ (割り込みを使わないときはこちらを使用する)
         * @param kp [in] 比例成分の係数
         * @param ki [in] 積分成分の係数
         * @param kd [in] 微分成分の係数
         * @param max_output_value [in]　出力の最大値
         */
        PidController(double kp, double ki, double kd, double max_output_value);

        /**
         * @brief コンストラクタ (割り込み使用時はこちらを使う)
         * @param kp [in] 比例成分の係数
         * @param ki [in] 積分成分の係数
         * @param kd [in] 微分成分の係数
         * @param max_output_value [in]　出力の最大値
         * @param attach_period_s [in] メンバ関数`calculate`の割り込み周期. 単位は秒
         */
        PidController(double kp, double ki, double kd, double max_output_value, double attach_period_s);

        /**
         * @brief PIDの計算を呼び出す関数
         * @param targetValue [in] 目標値
         * @param inputValue  [in] 入力値
         * @return [out] 出力値
         */
        double calculate(double targetValue, double inputValue);

        /**
         * @brief PIDの計算を呼び出す関数(割り込みを場合はこちらを使用すること)
         * @param targetValue [in] 目標値
         * @param inputValue  [in] 入力値
         * @param max_output_value [in] 前回のこのメンバ関数読み出して今回の処理までかかった時間幅
         * @return [out] 出力値
         */
        double calculate(double targetValue, double inputValue, double attach_period_s);

        /**
         * @brief PIDの各係数を変更できる
         * @param inputValue [in] 変更値
         * @param setting [in] ここに, KP, KI, KD を指定してどの係数か選ぶ
         */
        void setCoefficient(double coefficient, int selector) {
            if (selector >= 0 && selector <= 2) {
                k[selector] = coefficient;
            }
        }

        /**
         * @brief 擬似的に積分をするための使う時間を指定する
         * @param attach_period_s [in] 秒が基準です
         */
        void setAttachPeriodS(double attach_period_s) {
            this->attach_period_s = attach_period_s;
        }

        /**
         * @brief 出力値の最大値を変更
         * @param max_output_value [in] 変更したい値を指定する
         */
        void setMaxOutputValue(double max_output_value) {
            this->attach_period_s = max_output_value;
        }

    private:
        double deviation[2]; //! 偏差の保管
        double k[3]; //! 係数の指定
        double attach_period_s; //! 割り込み周期の設定
        double max_output_value; //! 出力の最大値
        double proportionalTerm; //! 比例成分の格納
        double integralTerm; //! 積分成分の格納
        double differentialTerm; //! 微分線分の格納
        double outputValue; //! 出力値
        int i; //! 制御変数
    };

}


#endif //MYSTEERING_PIDCONTROLLER_HPP
