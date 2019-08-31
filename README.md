高専ロボコンでラクするためのライブラリたち

# TOC  

- [概要](#概要)
- [機能](#機能)
- [クイックスタート](#クイックスタート)
    - [ライブラリを使いたい](#ライブラリを使いたい)
    - [ライブラリを改良,開発したい](#ライブラリを改良,開発したい)
- [サンプルコード](#サンプルコード)
    - [PID制御を使う](#PID制御を使う)
    - [メカナムを動かす](#メカナムを動かす)
    - [ナビゲーターを使う](#ナビゲーターを使う)
- [ドキュメント](#ドキュメント)
    - [ライブラリを使う](#ライブラリを使う)
        - [PidController](#PidController)
        - [MecanumWheelController](#MecanumWheelController)
        - [VectorMove](#VectorMove)
    - [ライブラリを作る](#ライブラリを作る)
        - [Vector](#Vector)
        - [WheelAttr](#WheelAttr)
        - [VectorCalculator](#VectorCalculator)
- [Q&A](#qa)
    - [これが使える環境は?](#これが使える環境は?)
    - [速度が出ない](#速度が出ない)  
    - [これ作った作者と直接話したい](#これ作った作者と直接話したい)
    
# 概要

- 簡単に使用できる  
- 移動, PID制御, 自動走行をサポート  
- マイコンの機種に依存しない設計  

# 機能

- PID制御  
    - 微分積分の知識がなくとも使用可
- ベクトル制御  
    - ベクトル演算,制御理論の知識がなくとも使用可
    - ホイールの位置に従って最適な移動ベクトルを算出  
    - メカナムホイールに対応  
    - 汎用的な基底クラス設計. 車輪移動系のマシンであれば簡単に対応可能  
- 自動走行
    - 移動したい座標, 自己位置を渡すことで自動で目標へ移動  
    - 現在実装と確認作業中

# クイックスタート

## ライブラリを使いたい

初めに[このページ](https://github.com/Agatsuma854/RoboconMachineControlLibrary)の`Clone or download`をクリックし`Download ZIP`を選択してダウンロード  

次に`RoboconMachineControlLibrary`を解凍し中にある`Ctrl`フォルダをコピーし自分がコードを書いているフォルダに貼り付ける  

コピーしたらライブラリを使用したいソースコードの上部で`Ctrl/Ctrl.hpp`と記述しライブラリ群をインクルードする  

## ライブラリを改良,開発したい  

[このページ](https://github.com/Agatsuma854/RoboconMachineControlLibrary)から`fork`を選択して自分のリポジトリに追加する  

or 

クローンする  

```$xslt
$ git clone https://github.com/Agatsuma854/RoboconMachineControlLibrary.git
```

そして開発する. バグや誤字を発見した場合はプルリクエストを出していただけるとありがたい  

# サンプルコード

### PID制御を使う  

```cpp  
// 工事中
```  

### メカナムを動かす

```cpp  
// 工事中
```

### ナビゲーターを使う  

```cpp
// 工事中
```

#ドキュメント  

## ライブラリを使う  

### PidController  

### MecanumWheelController  

### VectorMove  

## ライブラリを作る  

### Vector  

### WheelAttr  

### VectorCalculator  

# Q&A  

### これが使える環境は?  

C++14以上の環境であればどこでも

### 速度が出ない  

お使いのマイコンはdoubleがた

### これ作った作者と直接話したい  

# License  

まだ正式リリースではないから保留. (一部ファイルを除きGNU AGPLにしようか検討中)

# Author

Agatsuma854  
email : s1701002@semdai-nct.jp  
Twitter : @oserobo2221  