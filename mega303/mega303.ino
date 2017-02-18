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

int cnt = 0;

void setup() {
    // set the data rate for the SoftwareSerial port (MIDI rate)
    Serial1.begin(31250);
	Serial.begin(9600);
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

void loop() {
	cnt++;
	updateMatrix();
	checkEncoder();
	bufferPots();
	if(cnt%100 == 1) printPots();
	memcpy(LEDStates, buttonBuffer,16);
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
    Serial1.write(0x90 | _chanel);
    Serial1.write(_pitch);
    Serial1.write(_vel);
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void midiNoteOff(byte _chan, byte _pitch, byte _vel) {
//  Serial.write(cmd);
//  Serial.write(_pitch);
//  Serial.write(_vel);
    Serial1.write(0x80 | _chan);
    Serial1.write(_pitch);
    Serial1.write(_vel);
}
