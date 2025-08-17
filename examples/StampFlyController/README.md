# M5StampFly Controller

## Framework

Platfromio

## Base on project

[M5Fly-kanazawa/AtomJoy2024June (github.com)](https://github.com/M5Fly-kanazawa/AtomJoy2024June)

## Third-party libraries

m5stack/M5GFX @ ^0.1.16

fastled/FastLED @ ^3.7.0

lvgl @ ^8.3.10

M5AtomS3 @ ^0.0.3

m5stack/M5UnitASR @ ^0.0.1

-----

このリポジトリは、[Atom JoyStick](https://docs.m5stack.com/ja/app/Atom%20JoyStick)に、[Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)をつなぎ、[StampFly](https://docs.m5stack.com/ja/app/Stamp%20Fly) を音声でも制御可能にした、[Atom JoyStick](https://docs.m5stack.com/ja/app/Atom%20JoyStick)のソースコードです。音声操作よりもJoyStickの操作が優先されます。

以下の操作が可能です。（「すこし」をつけると、操作量が半分になります。）

![音声操作説明](https://github.com/MRSa/GokigenOSDN_documents/blob/main/images/attachments/StampFly-instruction.png?raw=true)

[PlatformIO](https://platformio.org/) でビルドしています。

## 使用する[Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)のカスタムファームウェア

音声操作に使用する[Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)は、次のファームウェアを使用します。

- [カスタムファームウェア 1.06](https://github.com/MRSa/GokigenOSDN_documents/raw/refs/heads/main/miscellaneous/M5/UnitASR/jx_ci_03t_firmware_v106_.bin)

[Unit ASR](https://docs.m5stack.com/ja/unit/Unit%20ASR)カスタムファームウェアの詳細は、[Unit ASRのカスタムファームウェア](https://github.com/MRSa/GokigenOSDN_documents/tree/main/miscellaneous/M5/UnitASR)ページを参照してください。
