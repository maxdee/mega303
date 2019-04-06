// Arduino Mega 1280 firmware
#include "TimerOne.h"
#include "TimerThree.h"

// #include "patches.h"
#include "MCInput.h"
// #include "HardwareMap.h"

///////////////////////////////////////////////////////////////////////////////
// SEQ stuff
///////////////////////////////////////////////////////////////////////////////

int step = 0;
uint16_t cycleCount = 0;

MCInput input;

int rate = 14;

void setup() {
    // set the data rate for the SoftwareSerial port (MIDI rate)
    Serial1.begin(115200); // link to the teensy
	Serial.begin(115200); // usb debugging
    // Timer1.initialize(5000);
    // Timer1.attachInterrupt(timed);
    // Timer3.initialize(1000);
    // Timer3.attachInterrupt(frequentCheck);

    // const FlashString F("YES3.0.3")
    // mc303 buttons and pots
    input.setEventCallback(event);
}

void loop() {
    input.update();
    if(Serial1.available() >= 17){
        if(Serial1.read() == 42){
            for(int i = 0; i < 16; i++){
                input.LEDStates[i] = Serial1.read();
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
// events
///////////////////////////////////////////////////////////////////////////////

void event(uint8_t _index, uint8_t _state){
    Serial1.write(_index);
    Serial1.write(_state);
}























//
// #include "TimerOne.h"
// #include "TimerThree.h"
//
// ///////////////////////////////////////////////////////////////////////////////
// // SEQ stuff
// ///////////////////////////////////////////////////////////////////////////////
//
// int step = 0;
// uint16_t cycleCount = 0;
//
//
// void setup() {
//     // set the data rate for the SoftwareSerial port (MIDI rate)
//     Serial1.begin(115200); // from the mega
//     Serial2.begin(31250);  // midi for the mc303
//     Serial3.begin(31250);  // midi jacks on the back
// 	Serial.begin(115200); // usb debugging
//     // Timer1.initialize(5000);
//     // Timer1.attachInterrupt(timed);
//     // Timer3.initialize(1000);
//     // Timer3.attachInterrupt(frequentCheck);
//
//     // set mc303 in sound module mode
//     soundModuleMode();
//
// }
//
// // enable sound module mode!!!
// void soundModuleMode(){
//     byte data[] = { 0xF0, 0x41, 0x10, 0x00, 0x03, 0x12, 0x00, 0x40, 0x00, 0x7F, 0x00, 0x3F, 0xF7 };
//     for(int i = 0; i < 13; i++){
//         midiByte(data[i]);
//     }
// }
//
// void midiByte(byte _b){
//     Serial3.write(_b);
// }
//
//
// void loop() {
//     // noteOn(69, 100);
//     // delay(1000);
//     // noteOff(69, 100);
//     // delay(1000);
// }
//
// int channel = 2;
//
// void noteOn(uint8_t _pitch, uint8_t _vel){
// 	// view -> printf("%03d%03d", channel, _pitch );
// 	Serial3.write(0x90 | channel);
// 	Serial3.write(_pitch);
// 	Serial3.write(_vel);
// }
//
// void noteOff(uint8_t _pitch, uint8_t _vel){
// 	Serial3.write(0x80 | channel);
// 	Serial3.write(_pitch);
// 	Serial3.write(_vel);
// }
