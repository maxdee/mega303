#include "TimerOne.h"
///////////////////////////////////////////////////////////////////////////////
// Input vars
///////////////////////////////////////////////////////////////////////////////

typedef struct {
    uint8_t pinA;
    uint8_t pinB;
    uint8_t prev;
	uint8_t tmp;
    int val;
} Encoder;

// Pins


#define dirPin 23
#define tapButton 45
Encoder enc = {41, 43};
uint8_t potPins[] = {8, 9, 10, 11, 12, 13, 14, 15};
uint8_t potStates[8];
// pins for columns
uint8_t columnPins[] = {25, 27, 29, 31, 33, 35, 37, 39};
// Pins for row multiplexer
uint8_t rowMuxPins[] = {47, 49, 51, 53};
// rows
byte rowBytes[] = {
	B00000000, // 000 aka 0
	B00000010, // 100 aka 1
	B00000100, // 010 aka 2
	B00000110, // 110 aka 3
	B00001000, // 001 aka 4
	B00001100, // 011 aka 6
	B00001110, // 111 aka 7
	// same but for second mux chip
	B00000001,
	B00000011,
	B00000101,
	B00000111,
	B00001001,
	B00001010,
	B00001011,
	B00001101,
	B00001111,
};
// next circuit version will use port manipulation...

// LED column states
byte LEDStates[16];
byte buttonBuffer[16];
byte buttonStates[16];





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


void setup() {
    // set the data rate for the SoftwareSerial port (MIDI rate)
    Serial1.begin(31250);
	Serial.begin(9600);
    setupInput();
    Timer1.initialize(50000);
    Timer1.attachInterrupt(timed);
    soundModuleMode();
    // midiSysEx(0x7F, 0x00, 0x3F);
    // setInstrument(11,64,2);
}

void loop() {
    updateInput();
    memcpy(LEDStates, buttonBuffer,16);
	// if(cnt%100 == 1) printPots();
}

void timed(){
    cycleCount++;
    if(cycleCount % 25 == 0 ){
        step++;
        step %= 16;
        midiNoteOff(9, 69, 0);
        midiNoteOn(9, 69, 100);
    }
}

void setInstrument(byte _part, byte _i, byte _j){
    midiControlChange(_part, 00, _i); // CC00 64-73
    midiControlChange(_part, 32, 00); // derp
    midiByte(0xC3);
    midiByte(_j);
    // myBus.sendMessage( new ShortMessage(ShortMessage.PROGRAM_CHANGE, _part, _j, 0) ); // PG
}


///////////////////////////////////////////////////////////////////////////////
// IO matrix
///////////////////////////////////////////////////////////////////////////////

void setupInput(){
	pinMode(dirPin, OUTPUT);
	for(int i = 0; i < 8; i++){
		pinMode(columnPins[i], OUTPUT);
	}
	for(int i = 0; i < 4; i++){
		pinMode(rowMuxPins[i], OUTPUT);
	}
	pinMode(enc.pinA, INPUT);
	pinMode(enc.pinB, INPUT);
	pinMode(tapButton, INPUT);
	memset(LEDStates, 0, 16);
	memset(buttonBuffer, 0, 16);
	memset(buttonStates, 0, 16);
}

void updateInput(){
	updateMatrix();
	checkEncoder();
	bufferPots();
}

///////////////////////////////////////////////////////////////////////////////
// IO matrix
///////////////////////////////////////////////////////////////////////////////

// call to update LED states and buffer buttons;
void updateMatrix(){
	for(int i = 0; i < 16; i++){
		setRow(i);
		columnLEDOutput(i);
		delayMicroseconds(100);
		bufferButtons(i);
		clearColumns();
	}
}
// enable the row 0-15
void setRow(int _row){
	for(int i = 0; i < 4; i++){
		digitalWrite(rowMuxPins[i], bitRead(rowBytes[_row], i));
	}
}
// output the column data according to row
void columnLEDOutput(int _row){
	digitalWrite(dirPin, HIGH);
	for(int i = 0; i < 8; i++){
		digitalWrite(columnPins[i], bitRead(LEDStates[_row], i));
	}
}
void clearColumns(){
	for(int i = 0; i < 8; i++){
		digitalWrite(columnPins[i], HIGH);
	}
}
// read the button matrix
void bufferButtons(int _row){
	digitalWrite(dirPin, LOW);
	for(int i = 0; i < 8; i++){
		pinMode(columnPins[i], INPUT);
		bitWrite(buttonBuffer[_row], i, digitalRead(columnPins[i]));
		pinMode(columnPins[i], OUTPUT);
	}
}
// set an led on or off
void setLED(uint8_t _row, uint8_t _col, uint8_t _state){
	bitWrite(LEDStates[_row], _col, _state);
}

///////////////////////////////////////////////////////////////////////////////
// Other input
///////////////////////////////////////////////////////////////////////////////

// check encoder method, increments or decrements the enc.val
void checkEncoder(){
	enc.tmp = digitalRead(enc.pinB);
	if((enc.tmp == HIGH) && (enc.prev == LOW)){
		enc.prev = enc.tmp;
		if(!digitalRead(enc.pinA)){
			enc.val++;
		}
		else {
			enc.val--;
		}
	}
	enc.prev = enc.tmp;
}
void checkTap(){

}
void bufferPots(){
	for(int i = 0; i < 8; i++){
		potStates[i] = analogRead(potPins[i])/8;
	}
}
void printPots(){
	for(int i = 0; i < 8; i++){
		Serial.print(potStates[i]);
		Serial.print(" ");
	}
	Serial.println();
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
