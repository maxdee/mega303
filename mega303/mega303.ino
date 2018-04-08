#include "TimerOne.h"
#include "TimerThree.h"

// #include "patches.h"
#include "MCInput.h"
#include "MCPart.h"
#include "MCConstants.h"
#include "MCMode.h"

///////////////////////////////////////////////////////////////////////////////
// SEQ stuff
///////////////////////////////////////////////////////////////////////////////

int step = 0;
uint16_t cycleCount = 0;

MCInput input ;
MCPart mcParts[PART_COUNT];

#define MODE_COUNT 4
MCMode * mode[MODE_COUNT];// = {ModeTwo(), ModeTwo(),ModeTwo()};
ModeOne modeOne;
ModeTwo modeTwo;
ModeThree modeThree;
ModeThree modeThree2;

int modeIndex;


bool doStep;
int rate = 28;

void setup() {
    // set the data rate for the SoftwareSerial port (MIDI rate)
    Serial1.begin(31250); // midi for the mc303
    Serial2.begin(31250); // midi jacks on the back
	Serial.begin(9600); // usb debugging

    // Timer1.initialize(5000);
    // Timer1.attachInterrupt(timed);
    // Timer3.initialize(1000);
    // Timer3.attachInterrupt(frequentCheck);

    // set mc303 in sound module mode
    soundModuleMode();
    // const FlashString F("YES3.0.3")
    input.displayString("YES3.0.3");
    // mc303 buttons and pots
    input.setEventCallback(event);

    // mcPart.releaseTime(110);
    // mcPart.portamentoTime(0);



    for(int i = 0; i < PART_COUNT; i++){
        setupPart(i);
    }

    mode[0] = &modeOne;
    mode[1] = &modeTwo;
    mode[2] = &modeThree;
    mode[3] = &modeThree2;

    for(int i = 0; i < MODE_COUNT; i++){
        mode[i]->begin(&Serial);
        mode[i]->setInput(&input);
        mode[i]->setParts(mcParts);
    }

    // mcParts[1].controlChange(0, 64);
    // mcParts[1].controlChange(32, 0);
    // mcParts[1].programChange(15);
}

void setupPart(uint8_t _i){
    mcParts[_i].begin(&Serial1, _i == 0 ? 9 : _i);
}

void loop() {
    input.update();
    timed();
    // Serial.println(input.checkButton(4,0));
    // snifMidiIn();
}

void timed(){
    cycleCount++;
    cycleCount %= rate;
    if(cycleCount == 0){
        step++;
        step%=16;
        doStep = true;
        // char _buf[12];
        // sprintf(_buf, "YES%03d", step);
        // input.displayString(_buf);
        input.setStep(step);
    }
    for(int i = 0; i < PART_COUNT; i++){
        if(doStep){
            mcParts[i].step(step);
        }
        // mcParts[i].update();
    }
    for(int i = 0; i < MODE_COUNT; i++){
        mode[i]->update(step);
    }
    doStep = false;
}


///////////////////////////////////////////////////////////////////////////////
// events
///////////////////////////////////////////////////////////////////////////////

void setMode(int _mode){
    mode[modeIndex]->unSelectMode();
    modeIndex = _mode;
    if(modeIndex < 0) modeIndex = MODE_COUNT-1;
    modeIndex %= MODE_COUNT;
    mode[modeIndex]->selectMode();
    char _buf[12];
    sprintf(_buf, "MoD%03d", modeIndex);
    input.displayString(_buf);
}

void event(int _index, int _state){
    // char _buf[12];
    // sprintf(_buf, "%03d%03d", _index, _state);
    // input.displayString(_buf);
    // Serial.print(_index);
    // Serial.print(' ');
    // Serial.println(_state);

    mode[modeIndex]->event(_index, _state);
    if(_state == 1 && input.checkButton(SHIFT_BUTTON)){
        if(_index == SELECT_LEFT_BUTTON) setMode(modeIndex-1);
        else if(_index == SELECT_RIGHT_BUTTON) setMode(modeIndex+1);
    }
}

// char _buf[12];
// sprintf(_buf, "%03d%03d", _pot, _val);
// input.displayString(_buf);

///////////////////////////////////////////////////////////////////////////////
// mc303 api
///////////////////////////////////////////////////////////////////////////////

void printByte(byte _b){
    Serial.print(_b, BIN);
    Serial.print(" ");
    Serial.println(_b, HEX);
}

///////////////////////////////////////////////////////////////////////////////
// Midi
///////////////////////////////////////////////////////////////////////////////

// enable sound module mode!!!
void soundModuleMode(){
    byte data[] = { 0xF0, 0x41, 0x10, 0x00, 0x03, 0x12, 0x00, 0x40, 0x00, 0x7F, 0x00, 0x3F, 0xF7 };
    for(int i = 0; i < 13; i++){
        midiByte(data[i]);
    }
}

void midiByte(byte _b){
    Serial1.write(_b);
}

// Send sysex data
// void midiSysEx(byte addr1, byte addr2, byte value) {
//     byte data[20] = { 0x41, 0x10, 0x00, 0x18, 0x12, 0x40, 0x00, 0x00, 0x00, 0x00 };
//     data[6] = addr1;
//     data[7] = addr2;
//     data[8] = value;
//     byte checksum = GetRolandChecksum(data+5, 4);
//     data[9] = checksum;
//
//     // Sysex starts wth 0xF0, ends with 0xF7
//     midiByte(0xF0);
//     for (int i = 0; i < 10; i++)
//         midiByte(data[i]);
//
//     midiByte(0xF7);
//
//     // delay(50);
// }

// calculate Roland sysex checksum
byte GetRolandChecksum(byte* data, int length) {
    // Roland sysex checksum = 128 - (data sum % 128)
    int sum = 0;
    for (int i = 0; i < length; i++)
        sum += data[i];

    int rem = sum % 128;
    int checksum = (128 - rem);
    //int check = sum + checksum;
    return byte(checksum);
}
