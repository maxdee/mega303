#include "TimerOne.h"
#include "TimerThree.h"

// #include "patches.h"
#include "MCView.h"

#include "MCPart.h"
#include "MCMode.h"
#include "LEDMap.h"

///////////////////////////////////////////////////////////////////////////////
// SEQ stuff
///////////////////////////////////////////////////////////////////////////////

int step = 0;
uint16_t cycleCount = 0;

MCView view;
MCPart * mcParts[PART_COUNT];
DrumPart drumPart;
SynthPart synthPart1;
SynthPart synthPart2;
SynthPart synthPart3;
SynthPart synthPart4;
SynthPart synthPart5;
SynthPart synthPart6;
SynthPart synthPart7;


#define MODE_COUNT 4
MCMode * mode[MODE_COUNT];// = {ModeTwo(), ModeTwo(),ModeTwo()};
ModeOne modeOne;
ModeTwo modeTwo;
ModeThree modeThree;
ModeThree modeThree2;

int modeIndex;


bool doStep;
int rate = 100000;

HardwareSerial * mcMidi;
HardwareSerial * midiInput;

HardwareSerial * megaSerial;

void setup() {
    // set the data rate for the SoftwareSerial port (MIDI rate)
    Serial1.begin(115200); // coms with the mega
    megaSerial = &Serial1;
    Serial2.begin(31250); // midi for the mc303
    midiInput = &Serial2;
    Serial3.begin(31250);// midi jacks on the back
    mcMidi = &Serial3;

	Serial.begin(115200); // usb debugging
    Serial.println("bootin");
    // Timer1.initialize(5000);
    // Timer1.attachInterrupt(timed);
    // Timer3.initialize(1000);
    // Timer3.attachInterrupt(frequentCheck);

    // set mc303 in sound module mode
    soundModuleMode();
    // const FlashString F("YES3.0.3")
    // mc303 buttons and pots
    // view.begin(&input);
    view.printf("Foo3.0.3");


    // mcPart.releaseTime(110);
    // mcPart.portamentoTime(0);

    mcParts[0] = &drumPart;
    mcParts[1] = &synthPart1;
    mcParts[2] = &synthPart2;
    mcParts[3] = &synthPart3;
    mcParts[4] = &synthPart4;
    mcParts[5] = &synthPart5;
    mcParts[6] = &synthPart6;
    mcParts[7] = &synthPart7;

    for(int i = 0; i < PART_COUNT; i++){
        setupPart(i);
    }
    mode[0] = &modeOne;
    mode[1] = &modeTwo;
    mode[2] = &modeThree;
    mode[3] = &modeThree2;


    for(int i = 0; i < MODE_COUNT; i++){
        mode[i]->begin(&view);
        // mode[i]->setInput(&input);
        mode[i]->setParts(mcParts);
        mode[i]->setDrumPart(&drumPart);
        // for(int i = 0; i < PART_COUNT; i++){
        // }
    }

    // mcParts[1].controlChange(0, 64);
    // mcParts[1].controlChange(32, 0);
    // mcParts[1].programChange(15);
}

void setupPart(uint8_t _i){
    mcParts[_i]->begin(mcMidi, &view, _i == 0 ? 9 : _i);
}





void loop() {
    // input.update();
    if(megaSerial->available() > 1){
        uint8_t _cmd = megaSerial->read();
        uint8_t _val = megaSerial->read();
        event(_cmd, _val);
        // Serial.printf("%03i%03i\n", _cmd, _val);
        // view.printf("%03i%03i\n", _cmd, _val);
        // view.ledUpdate = true;
    }
    if(view.doLEDupdate(step)){
        megaSerial->write(42);
        megaSerial->write(view.LEDOutput, 16);
    }
    timed();
    // Serial.println(input.checkInput(4,0));
    // snifMidiIn();
}

void debugParts(){
    for(int i = 0; i < PART_COUNT; i++){

        mcParts[i]->debug();
    }
}

void timed(){
    cycleCount++;
    cycleCount %= rate;
    if(cycleCount == 0){
        step++;
        step%=16;
        doStep = true;
        // view.printf("STP%3i", step);
        // input.setStep(step);
    }
    for(int i = 0; i < PART_COUNT; i++){
        if(doStep){
            mcParts[i]->step(step);
            view.ledUpdate = true;
        }
        // mcParts[i].update();
    }
    for(int i = 0; i < MODE_COUNT; i++){
        if(doStep)mode[i]->update(step);
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
    view.printf("MoD%03d", modeIndex);
}

void event(uint8_t _index, uint8_t _state){
    // char _buf[12];
    // sprintf(_buf, "%03d%03d", _index, _state);
    // input.displayString(_buf);
    // Serial.print(_index);
    // Serial.print(' ');
    // Serial.println(_state);

    mode[modeIndex]->event(_index, _state);
    if(_state == 1 && mode[modeIndex]->checkInput(SHIFT_BUTTON)){
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
    Serial2.write(_b);
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
