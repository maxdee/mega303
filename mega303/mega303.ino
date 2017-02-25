#include "TimerOne.h"
#include "TimerThree.h"

// #include "patches.h"
#include "MCInput.h"
#include "MCPart.h"

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

	Serial.begin(9600);
    Timer1.initialize(10000);
    Timer1.attachInterrupt(timed);
    // Timer3.initialize(1000);
    // Timer3.attachInterrupt(frequentCheck);
    soundModuleMode();

    interface.displayString("YES3.0.3");

    interface.setButtonEventCallback(buttonEvent);
    interface.setPotEventCallback(potEvent);

    // setKit(68);
}
int ha = 0;
int cnt = 0;

void loop() {
    interface.update();
    // cnt++;
    // cnt %= (analogRead(8)/10)+2;
    // if(cnt < 2){
    //     midiNoteOff(9, ha, 0);
    //     int low = analogRead(10)/8;
    //     int high = analogRead(9)/8;
    //     if(low>high) ha = low;
    //     else ha = random(high-low)+low;
    //     midiNoteOn(9, ha, 100);
    // }
    // Serial.println(interface.checkButton(4,0));
    // snifMidiIn();
}

void timed(){
    cycleCount++;
    // setLED(step,cycleCount%8, HIGH);
    // setLED(step,(cycleCount+1)%8,LOW);
    //
    // if(cycleCount % 18 == 0 ){
    //     step++;
    //     step%=16;
    //     // setKit(abs(enc.val));
    //     midiNoteOff(3,45,100);
    //     midiNoteOn(3,45,100);
    // }
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
void buttonEvent(int _row, int _col, int _state){
    if(_row == 4 || _row == 0){
        if(!_state){
            mcPart.noteOn(_col+64,100);
        }
        else {
            mcPart.noteOff(_col+64,100);
        }
    }
    // Serial.print(_row);
    // Serial.print("  ");
    // Serial.print(_col);
    // Serial.print("  ");
    // Serial.println(_state);
}

void potEvent(int _pot, int _val){
    switch (_pot){
        case 0:
            mcPart.fineTune(_val);
            break;
        case 1:
            mcPart.coarseTune(_val);
        case 2:
            mcPart.cutoff(_val);
            break;
        case 3:
            mcPart.resonance(_val);
            break;
        case 4:
            mcPart.setPatch(64, _val);
            break;
        case 5:
            mcPart.portamentoTime(_val);
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

void setInstrument(byte _part, byte _i, byte _j){
    midiControlChange(_part, 00, _i); // CC00 64-73
    midiControlChange(_part, 32, 00); // derp
    midiByte(0xC0 | _part);
    midiByte(_j);
    // myBus.sendMessage( new ShortMessage(ShortMessage.PROGRAM_CHANGE, _part, _j, 0) ); // PG
}
void setKit(uint8_t _kit){
    midiByte(0xC0 | 9);
    midiByte(_kit);
}

void printByte(byte _b){
    Serial.print(_b, BIN);
    Serial.print(" ");
    Serial.println(_b, HEX);
}


///////////////////////////////////////////////////////////////////////////////
// Midi
///////////////////////////////////////////////////////////////////////////////

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void midiNoteOn(byte _chanel, byte _pitch, byte _vel) {
//  Serial.write(cmd);
//  Serial.write(_pitch);
//  Serial.write(_vel);
    midiByte(0x90 | _chanel);
    midiByte(_pitch);
    midiByte(_vel);
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void midiNoteOff(byte _chan, byte _pitch, byte _vel) {
//  Serial.write(cmd);
//  Serial.write(_pitch);
//  Serial.write(_vel);
    midiByte(0x80 | _chan);
    midiByte(_pitch);
    midiByte(_vel);
}

//  Sends a MIDI control change
void midiControlChange(byte channel, byte ccNum, byte value) {
//  Serial.write(cmd);
//  Serial.write(pitch);
//  Serial.write(velocity);
    midiByte(0xB0 | channel);
    midiByte(ccNum);
    midiByte(value);
}

//  Sends a MIDI RPN change
void midiRPN(byte channel, byte cc100, byte cc101, byte value) {
    midiByte(0xB0 | channel);
    midiByte(0x64);
    midiByte(cc100);
    //Serial.write(0xB0 | channel);
    midiByte(0x65);
    midiByte(cc101);
    //Serial.write(0xB0 | channel);
    midiByte(0x06);
    midiByte(value);
    // Set RPN to null so that further spuriuous controller messages are ignored
    midiByte(0x64);
    midiByte(0x7F);
    midiByte(0x65);
    midiByte(0x7F);
    // delay(50);
}

//  Sends a MIDI RPN change
void midiNRPN(byte channel, byte msb, byte lsb, byte value) {
    midiByte(0xB0 | channel);
    midiByte(0x63);
    midiByte(msb);
    //Serial.write(0xB0 | channel);
    midiByte(0x62);
    midiByte(lsb);
    //Serial.write(0xB0 | channel);
    midiByte(0x06);
    midiByte(value);
    // Set RPN to null so that further spuriuous controller messages are ignored
    midiByte(0x62);
    midiByte(0x7F);
    midiByte(0x63);
    midiByte(0x7F);
    // delay(50);
}

//  Sends a MIDI control change
void midiPatchSelect(byte bank, byte patch) {
//  Serial.write(cmd);
//  Serial.write(pitch);
//  Serial.write(velocity);
    // Write bank in CC00 and CC32
    midiByte(0xB3);
    midiByte(byte(0));
    midiByte(bank);
    // delay(5);
    midiByte(0xB3);
    midiByte(32);
    midiByte(byte(0));
    // delay(5);
    // Write PC
    midiByte(0xC3);
    midiByte(patch);
    // delay(40);
}


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

void midiByte(byte _b){
    Serial1.write(_b);
}

// enable sound module mode!!!
void soundModuleMode(){
    byte data[] = { 0xF0, 0x41, 0x10, 0x00, 0x03, 0x12, 0x00, 0x40, 0x00, 0x7F, 0x00, 0x3F, 0xF7 };
    for(int i = 0; i < 13; i++){
        midiByte(data[i]);
    }
}
