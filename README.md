# ArduinoDDS
AVR DDS signal generator V2.0 for Arduino

有名なSignalGeneratorである"AVR DDS signal generator V2.0"をArduino向けに移植したものです。オリジナル版は以下の本家サイトを参照してください。
* ScienceProg - AVR DDS signal generator V2.0(http://www.scienceprog.com/avr-dds-signal-generator-v20/)

## 動作環境
以下のArduinoボードで動作確認をしています。
（確認は出来ていませんが、Arduino unoでも恐らく動作するかと思います）

* Arduino nano(ATmega328p)

## ビルド環境
以下の環境でビルドを行いました。他の環境でビルドされる場合はセクション指定(リンカオプションの"-section-start")が必要です。platformio.iniの内容を参考にしてください。

* PlatformIO IDE(1.6.0)

