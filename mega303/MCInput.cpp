#include "Arduino.h"
#include "MCInput.h"

MCInput::MCInput(){
	pinMode(dirPin, OUTPUT);
	for(int i = 0; i < 8; i++){
		pinMode(columnPins[i], OUTPUT);
	}
	for(int i = 0; i < 4; i++){
		pinMode(rowMuxPins[i], OUTPUT);
	}
	pinMode(encoder.pinA, INPUT);
	pinMode(encoder.pinB, INPUT);
	pinMode(tapButton, INPUT);
	pinMode(beatLEDRed, OUTPUT);
	digitalWrite(beatLEDRed, HIGH);
	memset(LEDStates, 255, 16);
	memset(buttonBuffer, 0, 16);
	memset(buttonStates, 0, 16);
	updateCount = 0;
}

void MCInput::setEventCallback(void (*_eventCallback)(int, int)){
	eventCallback = _eventCallback;
}

void MCInput::update(){
	updateCount++;
	// update the matrix
	for(int _row = 0; _row < 16; _row++){
		// set row
		for(int i = 0; i < 4; i++){
			digitalWrite(rowMuxPins[i], bitRead(rowBytes[_row], i));
		}
		// output the LEDs AND buffer the pots
		digitalWrite(dirPin, HIGH);
		for(int i = 0; i < 8; i++){
			if(i == STEP_LED[step] % COL_COUNT && _row == STEP_LED[step]/COL_COUNT)	digitalWrite(columnPins[i], !bitRead(LEDStates[_row], i));
			else digitalWrite(columnPins[i], bitRead(LEDStates[_row], i));
		}

		frequentCheck();
		delayMicroseconds(100);
		// buffer the buttons
		digitalWrite(dirPin, LOW);
		for(int i = 0; i < 8; i++){
			pinMode(columnPins[i], INPUT);
			tmp = digitalRead(columnPins[i]);
			if(tmp) tmp = 0;
			else tmp = 1;
			if(tmp != bitRead(buttonBuffer[_row], i)){
				bitWrite(buttonBuffer[_row], i, tmp);
				if(_row == 4 || _row == 0){
					eventCallback(STEP_LOOKUP[columnRowToIndex(_row, i)]+127, tmp);
				}
				else {
					eventCallback(columnRowToIndex(_row, i), tmp);
				}
			}
			pinMode(columnPins[i], OUTPUT);
		}
		// clear the columns
		for(int i = 0; i < 8; i++){
			digitalWrite(columnPins[i], HIGH);
		}
		if(encoder.val != 0){
			eventCallback(ENCODER_BUTTON, encoder.val);
			encoder.val = 0;
		}
	}
	// buffer the pots while we are at it
	for(int i = 0; i < 8; i++){
		// buffer the pots while we are at it
		potBuffer[updateCount%8][i] = analogRead(potPins[i])/8;
		tmp = (potBuffer[0][i] +
				potBuffer[1][i] +
				potBuffer[2][i] +
				potBuffer[3][i] +
				potBuffer[4][i] +
				potBuffer[5][i] +
				potBuffer[6][i] +
				potBuffer[7][i]) / 8;
		if(tmp != potValues[i] && tmp != previousPotVal[i]){
			previousPotVal[i] = potValues[i];
			potValues[i] = tmp;
			eventCallback(POTENTIOMETER[i], tmp);
		}
	}
}

void MCInput::setStep(uint8_t _step){
	step = _step;
}
int MCInput::columnRowToIndex(uint8_t _row, uint8_t _col){
    return (_row * COL_COUNT)+_col;
}

// set an led on or off
void MCInput::setLED(uint8_t _index, uint8_t _state){
	bitWrite(LEDStates[_index / COL_COUNT], _index % COL_COUNT, !_state);
}

void MCInput::setStepLEDs(uint16_t _step){
	for(int i = 0; i < 16; i++){
		setLED(STEP_LED[i], bitRead(_step, i));
	}
}

bool MCInput::checkButton(uint8_t _id){
	return bitRead(buttonBuffer[_id / COL_COUNT], _id % COL_COUNT);
}

// check encoder method, increments or decrements the encoder.val
void MCInput::frequentCheck(){
	// check the tap tempo?

	// check the encoder
	encoder.tmp = digitalRead(encoder.pinB);
	if((encoder.tmp == HIGH) && (encoder.prev == LOW)){
		encoder.prev = encoder.tmp;
		if(!digitalRead(encoder.pinA)){
			// encoder.val++;
			encoder.val = 2;
		}
		else {
			// encoder.val--;
			encoder.val = 1;
		}
	}
	encoder.prev = encoder.tmp;
}

void MCInput::displayString(char _str[]){
    byte _segRows[] = {6, 3, 12, 13, 10, 15};
    char _c;
    uint8_t _index = 0;
    for(int i = 0; i < 6; i++){
        _c = _str[_index++];
        if(_c == 46 && i > 0){
            i--;
            LEDStates[segmentRows[i]] ^= 1 << 7;
        }
        else {
            LEDStates[segmentRows[i]] = ~FONT_DEFAULT[_c-32];
        }
    }
}
void MCInput::displayBytes(byte _bytes[]){
    for(int i = 0; i < 6; i++){
		LEDStates[segmentRows[i]] = _bytes[i];
    }
}
