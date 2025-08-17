/* GOKIGEN Unit ASR */

#include <unit_asr.hpp>

#define ASR_INPUT_LIMIT_LOW  0x0780
#define ASR_INPUT_LIMIT_HIGH 0x0900

#define ASR_OUTPUT_COUNT_SHORT  50
#define ASR_OUTPUT_COUNT_LONG  100

#define ASR_OUTPUT_COUNT_TURN_S 25
#define ASR_OUTPUT_COUNT_TURN   50

#define ASR_OUTPUT_BIG_LOW   0x0100
#define ASR_OUTPUT_BIG_HIGH  0x0e00
#define ASR_OUTPUT_MID_LOW   0x0400
#define ASR_OUTPUT_MID_HIGH  0x0c00
#define ASR_OUTPUT_IDLE      0x0800

ASRUnit asr;
bool isConnectedCalled = false;
bool isHandleTakeoff = false;
bool isHandleLanding = false;

uint8_t moveUpDownCounter = 0;
uint16_t moveUpDownValue = 0;

uint8_t moveLeftRightCounter = 0;
uint16_t moveLeftRightValue = 0;

uint8_t moveForwardBackCounter = 0;
uint16_t moveForwardBackValue = 0;

uint8_t moveCwCcwCounter = 0;
uint16_t moveCwCcwValue = 0;

uint8_t moveIdleCounter = 0;
uint16_t moveIdleValue = 0;

void onConnectedAnnounce()
{
    try
    {
        asr.sendComandNum(0x4f);
    }
    catch(...) { }
}

void displayMessage(const char *message, int fontColor = TFT_WHITE)
{
    USBSerial.printf("%s\n", message);
}

void takeoffHandler()
{
    isHandleTakeoff = true;
    isHandleLanding = false;
    displayMessage("離陸!", TFT_ORANGE);
}

void landHandler()
{
    isHandleTakeoff = false;
    isHandleLanding = true;
    displayMessage("着陸!", TFT_ORANGE);
}

void upShortHandler()
{
    displayMessage("上昇 短", TFT_LIGHTGRAY);
    moveUpDownCounter = ASR_OUTPUT_COUNT_SHORT;
    moveUpDownValue = ASR_OUTPUT_MID_LOW;
}

void downShortHandler()
{
    displayMessage("下降 短", TFT_LIGHTGRAY);
    moveUpDownCounter = ASR_OUTPUT_COUNT_SHORT;
    moveUpDownValue = ASR_OUTPUT_MID_HIGH;
}

void leftShortHandler()
{
    displayMessage("左移動 短", TFT_LIGHTGRAY);
    moveLeftRightCounter = ASR_OUTPUT_COUNT_SHORT;
    moveLeftRightValue = ASR_OUTPUT_MID_LOW;
}

void rightShortHandler()
{
    displayMessage("右移動 短", TFT_LIGHTGRAY);
    moveLeftRightCounter = ASR_OUTPUT_COUNT_SHORT;
    moveLeftRightValue = ASR_OUTPUT_MID_HIGH;
}

void forwardShortHandler()
{
    displayMessage("前進 短", TFT_LIGHTGRAY);
    moveForwardBackCounter = ASR_OUTPUT_COUNT_SHORT;
    moveForwardBackValue = ASR_OUTPUT_MID_LOW;
}

void backShortHandler()
{
    displayMessage("後退 短", TFT_LIGHTGRAY);
    moveForwardBackCounter = ASR_OUTPUT_COUNT_SHORT;
    moveForwardBackValue = ASR_OUTPUT_MID_HIGH;
}

void ccwShortHandler()
{
    displayMessage("左回り 短", TFT_LIGHTGRAY);
    moveCwCcwCounter = ASR_OUTPUT_COUNT_TURN_S;
    moveCwCcwValue = ASR_OUTPUT_MID_LOW;
}

void cwShortHandler()
{
    displayMessage("右回り 短", TFT_LIGHTGRAY);
    moveCwCcwCounter = ASR_OUTPUT_COUNT_TURN_S;
    moveCwCcwValue = ASR_OUTPUT_MID_HIGH;
}

void upLongHandler()
{
    displayMessage("上昇 長", TFT_WHITE);
    moveUpDownCounter = ASR_OUTPUT_COUNT_LONG;
    moveUpDownValue = ASR_OUTPUT_MID_LOW;
}

void downLongHandler()
{
    displayMessage("下降 長", TFT_WHITE);
    moveUpDownCounter = ASR_OUTPUT_COUNT_LONG;
    moveUpDownValue = ASR_OUTPUT_MID_HIGH;
}

void leftLongHandler()
{
    displayMessage("左移動 長", TFT_WHITE);
    moveLeftRightCounter = ASR_OUTPUT_COUNT_LONG;
    moveLeftRightValue = ASR_OUTPUT_MID_LOW;
}

void rightLongHandler()
{
    displayMessage("右移動 長", TFT_WHITE);
    moveLeftRightCounter = ASR_OUTPUT_COUNT_LONG;
    moveLeftRightValue = ASR_OUTPUT_MID_HIGH;
}

void forwardLongHandler()
{
    displayMessage("前進 長", TFT_WHITE);
    moveForwardBackCounter = ASR_OUTPUT_COUNT_LONG;
    moveForwardBackValue = ASR_OUTPUT_MID_LOW;
}

void backLongHandler()
{
    displayMessage("後退 長", TFT_WHITE);
    moveForwardBackCounter = ASR_OUTPUT_COUNT_LONG;
    moveForwardBackValue = ASR_OUTPUT_MID_HIGH;
}

void ccwLongHandler()
{
    displayMessage("左回り 長", TFT_WHITE);
    moveCwCcwCounter = ASR_OUTPUT_COUNT_TURN;
    moveCwCcwValue = ASR_OUTPUT_MID_LOW;
}

void cwLongHandler()
{
    displayMessage("右回り 長", TFT_WHITE);
    moveCwCcwCounter = ASR_OUTPUT_COUNT_TURN;
    moveCwCcwValue = ASR_OUTPUT_MID_HIGH;
}

void stopHandler()
{
    displayMessage("停止", TFT_WHITE);
    
    moveIdleCounter = ASR_OUTPUT_COUNT_LONG; // ASR_OUTPUT_COUNT_SHORT;
    moveIdleValue = ASR_OUTPUT_IDLE;

    // ---- ASRからの動作要求をリセット
    moveUpDownCounter = 0;
    moveUpDownValue = 0;

    moveLeftRightCounter = 0;
    moveLeftRightValue = 0;

    moveForwardBackCounter = 0;
    moveForwardBackValue = 0;

    moveCwCcwCounter = 0;
    moveCwCcwValue = 0;
}

void emergencyHandler()
{
    displayMessage("緊急停止!", TFT_ORANGE);

    // ---- ASRからの動作要求をクリア (アイドルも含む)
    moveIdleCounter = 0;
    moveIdleValue = 0;

    moveUpDownCounter = 0;
    moveUpDownValue = 0;

    moveLeftRightCounter = 0;
    moveLeftRightValue = 0;

    moveForwardBackCounter = 0;
    moveForwardBackValue = 0;

    moveCwCcwCounter = 0;
    moveCwCcwValue = 0;
}

void connectedHandler()
{
    displayMessage("接続!", TFT_ORANGE);
}

void movieStartHandler()
{
    displayMessage("録画開始", TFT_WHITE);
}

void movieEndHandler()
{
    displayMessage("録画終了", TFT_WHITE);
}

void receiveHandler()
{
    USBSerial.printf("Not support command received!\n");
    displayMessage("(命令受信)", TFT_LIGHTGREY);
}


void prepareUnitASR()
{
    int8_t port_a_pin_rx = 1, port_a_pin_tx = 2;
    USBSerial.printf("--- Initialize Unit ASR ---\n");
    //port_a_pin1 = M5.getPin(m5::pin_name_t::port_a_pin1);
    //port_a_pin2 = M5.getPin(m5::pin_name_t::port_a_pin2);
    USBSerial.printf("  Pin: RX:%d TX:%d\n", port_a_pin_rx, port_a_pin_tx);
    asr.begin(&Serial1, 115200, port_a_pin_rx, port_a_pin_tx);
    asr.addCommandWord(0x1A, "previous",receiveHandler);
    asr.addCommandWord(0x1B, "next",receiveHandler);
    asr.addCommandWord(0x20, "zero",receiveHandler);
    asr.addCommandWord(0x21, "one",receiveHandler);
    asr.addCommandWord(0x22, "two",receiveHandler);
    asr.addCommandWord(0x23, "three",receiveHandler);
    asr.addCommandWord(0x24, "four",receiveHandler);
    asr.addCommandWord(0x25, "five",receiveHandler);
    asr.addCommandWord(0x26, "six",receiveHandler);
    asr.addCommandWord(0x27, "seven",receiveHandler);
    asr.addCommandWord(0x28, "eight",receiveHandler);
    asr.addCommandWord(0x29, "nine",receiveHandler);
    asr.addCommandWord(0x30, "ok",stopHandler);
    asr.addCommandWord(0x31, "hi_ASR",receiveHandler);
    asr.addCommandWord(0x32, "hello",receiveHandler);
    asr.addCommandWord(0x40, "increase_speed",receiveHandler);
    asr.addCommandWord(0x41, "decrease_speed",receiveHandler);
    asr.addCommandWord(0x42, "maximum_speed",receiveHandler);
    asr.addCommandWord(0x43, "medium_speed",receiveHandler);
    asr.addCommandWord(0x44, "minimum_speed",receiveHandler);
    asr.addCommandWord(0x45, "fw_version",receiveHandler);
    asr.addCommandWord(0x46, "out_finished",receiveHandler);
    asr.addCommandWord(0x47, "out_started",receiveHandler);
    asr.addCommandWord(0x48, "out_desu",receiveHandler);
    asr.addCommandWord(0x49, "out_NG2",receiveHandler);
    asr.addCommandWord(0x4a, "out_NG",receiveHandler);
    asr.addCommandWord(0x4b, "out_fail",receiveHandler);
    asr.addCommandWord(0x4c, "out_ok",receiveHandler);
    asr.addCommandWord(0x4d, "out_yes",receiveHandler);
    asr.addCommandWord(0x4e, "out_accepted",receiveHandler);
    asr.addCommandWord(0x4f, "out_connected",connectedHandler);
    asr.addCommandWord(0x50, "out_zero",receiveHandler);
    asr.addCommandWord(0x51, "out_one",receiveHandler);
    asr.addCommandWord(0x52, "out_two",receiveHandler);
    asr.addCommandWord(0x53, "out_three",receiveHandler);
    asr.addCommandWord(0x54, "out_four",receiveHandler);
    asr.addCommandWord(0x55, "out_five",receiveHandler);
    asr.addCommandWord(0x56, "out_six",receiveHandler);
    asr.addCommandWord(0x57, "out_seven",receiveHandler);
    asr.addCommandWord(0x58, "out_eight",receiveHandler);
    asr.addCommandWord(0x59, "out_nine",receiveHandler);
    asr.addCommandWord(0x5a, "out_ten",receiveHandler);
    asr.addCommandWord(0x5b, "out_error",receiveHandler);
    asr.addCommandWord(0x5c, "out_timeout",receiveHandler);
    asr.addCommandWord(0x5d, "out_disconnect",receiveHandler);
    asr.addCommandWord(0x5e, "out_success",receiveHandler);
    asr.addCommandWord(0x5f, "out_failure",receiveHandler);
    asr.addCommandWord(0x61, "command",receiveHandler);
    asr.addCommandWord(0x62, "takeoff",takeoffHandler);
    asr.addCommandWord(0x63, "land",landHandler);
    asr.addCommandWord(0x64, "landing",landHandler);
    asr.addCommandWord(0x65, "capture",receiveHandler);
    asr.addCommandWord(0x66, "movie_start",movieStartHandler);
    asr.addCommandWord(0x67, "movie_end",movieEndHandler);
    asr.addCommandWord(0x68, "status",receiveHandler);
    asr.addCommandWord(0x69, "time",receiveHandler);
    asr.addCommandWord(0x6a, "remain",receiveHandler);
    asr.addCommandWord(0x71, "up 70",upShortHandler);
    asr.addCommandWord(0x72, "down 70",downShortHandler);
    asr.addCommandWord(0x73, "right 70",rightShortHandler);
    asr.addCommandWord(0x74, "left 70",leftShortHandler);
    asr.addCommandWord(0x75, "forward 70",forwardShortHandler);
    asr.addCommandWord(0x76, "back 70",backShortHandler);
    asr.addCommandWord(0x77, "ccw 45",ccwShortHandler);
    asr.addCommandWord(0x78, "cw 45",cwShortHandler);
    asr.addCommandWord(0x81, "up 150",upLongHandler);
    asr.addCommandWord(0x82, "down 150",downLongHandler);
    asr.addCommandWord(0x83, "right 150",rightLongHandler);
    asr.addCommandWord(0x84, "left 150",leftLongHandler);
    asr.addCommandWord(0x85, "forward 150",forwardLongHandler);
    asr.addCommandWord(0x86, "back 150",backLongHandler);
    asr.addCommandWord(0x87, "ccw 90",ccwLongHandler);
    asr.addCommandWord(0x88, "cw 90",cwLongHandler);
    asr.addCommandWord(0x91, "out_100",receiveHandler);
    asr.addCommandWord(0x92, "out_1000",receiveHandler);
    asr.addCommandWord(0x93, "out_degree",receiveHandler);
    asr.addCommandWord(0x94, "out_percent",receiveHandler);
    asr.addCommandWord(0x95, "out_hour",receiveHandler);
    asr.addCommandWord(0x96, "out_second",receiveHandler);
    asr.addCommandWord(0x97, "out_minute",receiveHandler);
    asr.addCommandWord(0x98, "out_remain",receiveHandler);
    asr.addCommandWord(0x99, "emergency",emergencyHandler);
    asr.addCommandWord(0x9a, "out_time",receiveHandler);
    asr.addCommandWord(0x9b, "out_speed",receiveHandler);
    asr.addCommandWord(0x9c, "out_height",receiveHandler);
    asr.addCommandWord(0x9d, "out_temp",receiveHandler);
    asr.addCommandWord(0xfe, "announce",receiveHandler);
    asr.addCommandWord(0xff, "hi_m_five",receiveHandler);

    USBSerial.printf("--- Done initialize. ---\n");
}
