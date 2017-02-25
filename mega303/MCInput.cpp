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
	pinMode(enc.pinA, INPUT);
	pinMode(enc.pinB, INPUT);
	pinMode(tapButton, INPUT);
	pinMode(beatLEDRed, OUTPUT);
	digitalWrite(beatLEDRed, HIGH);
	memset(LEDStates, 255, 16);
	memset(buttonBuffer, 0, 16);
	memset(buttonStates, 0, 16);
	updateCount = 0;
}

void MCInput::setButtonEventCallback(void (*_buttonEventCallback)(int, int, int)){
	buttonEventCallback = _buttonEventCallback;
}
void MCInput::setPotEventCallback(void (*_potEventCallback)(int, int)){
	potEventCallback = _potEventCallback;
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
			digitalWrite(columnPins[i], bitRead(LEDStates[_row], i));
		}
		frequentCheck();
		delayMicroseconds(100);
		// buffer the buttons
		digitalWrite(dirPin, LOW);
		for(int i = 0; i < 8; i++){
			pinMode(columnPins[i], INPUT);
			tmp = digitalRead(columnPins[i]);
			if(tmp != bitRead(buttonBuffer[_row], i)){
				bitWrite(buttonBuffer[_row], i, tmp);
				buttonEventCallback(_row, i, tmp);
			}

			pinMode(columnPins[i], OUTPUT);
		}
		// clear the columns
		for(int i = 0; i < 8; i++){
			digitalWrite(columnPins[i], HIGH);
		}
	}
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
		if(tmp != potValues[i]){
			potValues[i] = tmp;
			potEventCallback(i, tmp);
		}
	}
}

// set an led on or off
void MCInput::setLED(uint8_t _row, uint8_t _col, uint8_t _state){
	bitWrite(LEDStates[_row], _col, !_state);
}

bool MCInput::checkButton(uint8_t _row, uint8_t _col){
	return bitRead(buttonBuffer[_row], _col);
}

// check encoder method, increments or decrements the enc.val
void MCInput::frequentCheck(){
	// check the tap tempo?

	// check the encoder
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
