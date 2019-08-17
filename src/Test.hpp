//
// Created by Mayoi on 2019/08/18.
//

#ifndef VECTORCTRL_TEST_HPP
#define VECTORCTRL_TEST_HPP

#include <iostream>

/*
 * コンパイラの仕様を考えればclass template使ったときヘッダファイルでしか実装できないわけが分かる
 * なぜなら単体でコンパイルされてリンクされるからこんな挙動になる. #include "xxx.h"とかかかれているなら
 * その場所にコードが張り付けられてコンパイルされて, メイン関数で Class<int>とか書いたやつの型の情報が伝わるけど
 * 単体コンパイルされる実装部のcppファイルには伝わらないからできない. あーコンパイルじにテンプレートの型
 * が決定されれるからこうなる. あらかじめすべてのファイルを見てからコンパイルするコンパイラがあれば別だが
 * そんなものはC/C++の汎用コンパいらのなかには存在しないからできないってわけ. てか.lib/.dllとかも今の方式じゃねぇと
 * 生き残れない.まぁ型はバージョン分けてリリースすればいいよねと.
 * */

template<class T>
class Test {
public:
	Test(T data);
	void showData();
private:
	T data;
};

template <class T> Test<T>::Test(T data) {
	this->data = data;
}

template<class T> void Test<T>::showData() {
	std::cout << "data" << data << "\n";
}

#endif //VECTORCTRL_TEST_HPP
