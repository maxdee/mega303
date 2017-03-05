#include "TimerOne.h"
#include "TimerThree.h"

// #include "patches.h"
#include "MCInput.h"
#include "MCPart.h"
#include "MCConstants.h"

///////////////////////////////////////////////////////////////////////////////
// SEQ stuff
///////////////////////////////////////////////////////////////////////////////

typedef struct{
    uint8_t chan_;
    uint8_t pitch_;
    uint8_t vel_;
    uint8_t time_;
} NoteEvent;

int step = 0;
uint16_t cycleCount = 0;

MCInput interface;
MCPart mcPart;

void setup() {
    // set the data rate for the SoftwareSerial port (MIDI rate)
    Serial1.begin(31250);
    Serial2.begin(31250);
    mcPart.begin(&Serial1, 1);
    mcPart.setPatch(64,22);

	Serial.begin(9600);
    Timer1.initialize(500000);
    Timer1.attachInterrupt(timed);
    // Timer3.initialize(1000);
    // Timer3.attachInterrupt(frequentCheck);
    soundModuleMode();
    // const FlashString F("YES3.0.3")
    interface.displayString("YES3.0.3");

    interface.setButtonEventCallback(buttonEvent);
    interface.setPotEventCallback(potEvent);

    mcPart.setPatch(64,22);
    mcPart.releaseTime(110);
    mcPart.portamentoTime(0);

}

int ha = 0;
int cnt = 0;
int currentNote = 0;
int rate = 0;
int low = 0;
int high = 0;

void loop() {
    interface.update();

    // Serial.println(interface.checkButton(4,0));
    // snifMidiIn();
}

void timed(){
    cycleCount++;
    cycleCount %= rate;
}

// void snifMidiIn(){
//     if(Serial2.available()){
//         Serial.println("|||||||||||");
//         byte _b = 0;
//         while(Serial2.available()){
//             _b = Serial2.read();
//             midiByte(_b);
//             Serial.print(_b, HEX);
//             Serial.print("  ");
//             Serial.println(_b, BIN);
//         }
//     }
// }

///////////////////////////////////////////////////////////////////////////////
// events
///////////////////////////////////////////////////////////////////////////////

void buttonEvent(int _index, int _state){
    interface.setLED(cnt, false);
    if(_index == ENCODER_BUTTON){
        cnt += _state;
    }
    if(_index < 40 && millis() > 3000){
        if(STEP_LOOKUP[_index] != 0){
            if(!_state){
                mcPart.noteOn(STEP_LOOKUP[_index]+36, 100);
            }
            else mcPart.noteOff(STEP_LOOKUP[_index]+36, 100);
        }
    }
    // if(_index == FUNC_BUTTON){
    //     interface.setLED(FUNC_LED, !_state);
    // }
    // if(_state){
    //     if(_index == SELECT_LEFT_BUTTON) cnt--;
    //     else if(_index == SELECT_RIGHT_BUTTON) cnt++;
        interface.setLED(cnt, true);
    // }

    char _buf[12];
    sprintf(_buf, "%03d", cnt);
    interface.displayString(_buf);
    // uint8_t note = (_col*3)+32;
    // if(_row == 4 || _row == 0){
    //     uint8_t note = (_col*3)+32;
    //     if(_row == 0) note = ((_col+8)*3)+32;
    //     if(!_state){
    //         mcPart.noteOn(note,100);
    //     }
    //     else {
    //         mcPart.noteOff(note,100);
    //     }
    // }
    // bitWrite(LEDStates[_index / COL_COUNT], _index % COL_COUNT, !_state);
    Serial.println(_index);
    if(_index == SHIFT_BUTTON) Serial.println(F("ahahah"));
    // Serial.print("  ");
    // Serial.print(_col);
    // Serial.print("  ");
    // Serial.println(_state);
}



void potEvent(int _pot, int _val){
    switch (_pot){
        case 0:
            mcPart.releaseTime(_val);
            break;
        case 1:
            mcPart.resonance(_val);
            break;
        case 2:
            mcPart.cutoff(_val);
            break;
        case 3:
            mcPart.cutoffFreq(_val);
            break;
        case 4:
            mcPart.vibratoRate(_val);
            break;
        case 5:
            mcPart.vibratoDepth(_val);
            break;
        case 6:
            mcPart.sustain(_val);
            break;
    }
    char _buf[12];
    sprintf(_buf, "%03d%03d", _pot, _val);
    interface.displayString(_buf);
    // Serial.println(_buf);
    // // Serial.print("  ");
    // // Serial.println(_val);
}

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
//
// //  plays a MIDI note.  Doesn't check to see that
// //  cmd is greater than 127, or that data values are  less than 127:
// void midiNoteOn(byte _chanel, byte _pitch, byte _vel) {
// //  Serial.write(cmd);
// //  Serial.write(_pitch);
// //  Serial.write(_vel);
//     midiByte(0x90 | _chanel);
//     midiByte(_pitch);
//     midiByte(_vel);
// }
//
// //  plays a MIDI note.  Doesn't check to see that
// //  cmd is greater than 127, or that data values are  less than 127:
// void midiNoteOff(byte _chan, byte _pitch, byte _vel) {
// //  Serial.write(cmd);
// //  Serial.write(_pitch);
// //  Serial.write(_vel);
//     midiByte(0x80 | _chan);
//     midiByte(_pitch);
//     midiByte(_vel);
// }
//
// //  Sends a MIDI control change
// void midiControlChange(byte channel, byte ccNum, byte value) {
// //  Serial.write(cmd);
// //  Serial.write(pitch);
// //  Serial.write(velocity);
//     midiByte(0xB0 | channel);
//     midiByte(ccNum);
//     midiByte(value);
// }
//
// //  Sends a MIDI RPN change
// void midiRPN(byte channel, byte cc100, byte cc101, byte value) {
//     midiByte(0xB0 | channel);
//     midiByte(0x64);
//     midiByte(cc100);
//     //Serial.write(0xB0 | channel);
//     midiByte(0x65);
//     midiByte(cc101);
//     //Serial.write(0xB0 | channel);
//     midiByte(0x06);
//     midiByte(value);
//     // Set RPN to null so that further spuriuous controller messages are ignored
//     midiByte(0x64);
//     midiByte(0x7F);
//     midiByte(0x65);
//     midiByte(0x7F);
//     // delay(50);
// }
//
// //  Sends a MIDI RPN change
// void midiNRPN(byte channel, byte msb, byte lsb, byte value) {
//     midiByte(0xB0 | channel);
//     midiByte(0x63);
//     midiByte(msb);
//     //Serial.write(0xB0 | channel);
//     midiByte(0x62);
//     midiByte(lsb);
//     //Serial.write(0xB0 | channel);
//     midiByte(0x06);
//     midiByte(value);
//     // Set RPN to null so that further spuriuous controller messages are ignored
//     midiByte(0x62);
//     midiByte(0x7F);
//     midiByte(0x63);
//     midiByte(0x7F);
//     // delay(50);
// }




// Send sysex data
void midiSysEx(byte addr1, byte addr2, byte value) {
    byte data[20] = { 0x41, 0x10, 0x00, 0x18, 0x12, 0x40, 0x00, 0x00, 0x00, 0x00 };
    data[6] = addr1;
    data[7] = addr2;
    data[8] = value;
    byte checksum = GetRolandChecksum(data+5, 4);
    data[9] = checksum;

    // Sysex starts wth 0xF0, ends with 0xF7
    midiByte(0xF0);
    for (int i = 0; i < 10; i++)
        midiByte(data[i]);

    midiByte(0xF7);

    // delay(50);
}

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
