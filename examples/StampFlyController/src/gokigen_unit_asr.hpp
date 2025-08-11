/* GOKIGEN Unit ASR */

#include <unit_asr.hpp>
ASRUnit asr;
bool isConnectedCalled = false;
bool isHandleTakeoff = false;
bool isHandleLanding = false;

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

void up40Handler()
{
    displayMessage("上昇 40", TFT_LIGHTGRAY);
}

void down40Handler()
{
    displayMessage("下降 40", TFT_LIGHTGRAY);
}

void right40Handler()
{
    displayMessage("右移動 40", TFT_LIGHTGRAY);
}

void left40Handler()
{
    displayMessage("左移動 40", TFT_LIGHTGRAY);
}

void forward40Handler()
{
    displayMessage("前進 40", TFT_LIGHTGRAY);
}

void back40Handler()
{
    displayMessage("後退 40", TFT_LIGHTGRAY);
}

void cw45Handler()
{
    displayMessage("右回り 45度", TFT_LIGHTGRAY);
}

void ccw45Handler()
{
    displayMessage("左回り 45度", TFT_LIGHTGRAY);
}

void up100Handler()
{
    displayMessage("上昇 100", TFT_WHITE);
}

void down100Handler()
{
    displayMessage("下降 100", TFT_WHITE);
}

void right100Handler()
{
    displayMessage("右移動 100", TFT_WHITE);
}

void left100Handler()
{
    displayMessage("左移動 100", TFT_WHITE);
}

void forward100Handler()
{
    displayMessage("前進 100", TFT_WHITE);
}

void back100Handler()
{
    displayMessage("後退 100", TFT_WHITE);
}

void cw90Handler()
{
    displayMessage("右回り 90度", TFT_WHITE);
}

void ccw90Handler()
{
    displayMessage("左回り 90度", TFT_WHITE);
}

void sendSpeedCommand(int currentSpeed = 100)
{
    char cmd[16];
    char disp[24];
    sprintf(disp, "速度 %d", currentSpeed);
    sprintf(cmd, "speed %d", currentSpeed);
    displayMessage(disp, TFT_WHITE);
}

void incSpeedHandler()
{
    sendSpeedCommand(75);
}

void decSpeedHandler()
{
    sendSpeedCommand(25);
}

void maxSpeedHandler()
{
    sendSpeedCommand(100);
}

void midSpeedHandler()
{
    sendSpeedCommand(55);
}

void minSpeedHandler()
{
    sendSpeedCommand(10);
}

void emergencyHandler()
{
    displayMessage("緊急停止!", TFT_ORANGE);
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
    asr.addCommandWord(0x30, "ok",receiveHandler);
    asr.addCommandWord(0x31, "hi_ASR",receiveHandler);
    asr.addCommandWord(0x32, "hello",receiveHandler);
    asr.addCommandWord(0x40, "increase_speed",incSpeedHandler);
    asr.addCommandWord(0x41, "decrease_speed",decSpeedHandler);
    asr.addCommandWord(0x42, "maximum_speed",maxSpeedHandler);
    asr.addCommandWord(0x43, "medium_speed",midSpeedHandler);
    asr.addCommandWord(0x44, "minimum_speed",minSpeedHandler);
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
    asr.addCommandWord(0x71, "up 70",up40Handler);
    asr.addCommandWord(0x72, "down 70",down40Handler);
    asr.addCommandWord(0x73, "right 70",right40Handler);
    asr.addCommandWord(0x74, "left 70",left40Handler);
    asr.addCommandWord(0x75, "forward 70",forward40Handler);
    asr.addCommandWord(0x76, "back 70",back40Handler);
    asr.addCommandWord(0x77, "ccw 45",ccw45Handler);
    asr.addCommandWord(0x78, "cw 45",cw45Handler);
    asr.addCommandWord(0x81, "up 150",up100Handler);
    asr.addCommandWord(0x82, "down 150",down100Handler);
    asr.addCommandWord(0x83, "right 150",right100Handler);
    asr.addCommandWord(0x84, "left 150",left100Handler);
    asr.addCommandWord(0x85, "forward 150",forward100Handler);
    asr.addCommandWord(0x86, "back 150",back100Handler);
    asr.addCommandWord(0x87, "ccw 90",ccw90Handler);
    asr.addCommandWord(0x88, "cw 90",cw90Handler);
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
