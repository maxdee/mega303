#include "MCView.h"

MCView::MCView(){
    useSerial = true;
    memset(LEDStates, 255, sizeof(LEDStates));
    ledUpdate = true;
}

size_t MCView::write(uint8_t _c){
    pushDigit(_c);
    if(useSerial) Serial.write(_c);
}

// set an led on or off
void MCView::setLED(uint8_t _index, uint8_t _state){
	bitWrite(LEDStates[_index / COL_COUNT], _index % COL_COUNT, !_state);
}

void MCView::setStepLEDs(uint16_t _step){
	for(int i = 0; i < 16; i++){
		setLED(STEP_LED[i], bitRead(_step, i));
	}
}

void MCView::setPartSelectLEDs(uint8_t _v){
	for(uint8_t i = 0; i < 8; i++){
		setLED(i+ID_MIN_PART, bitRead(_v, i));
	}
}


bool MCView::doLEDupdate(uint8_t _step){
    if(ledUpdate) {
        memcpy(LEDOutput, LEDStates, 16);
        uint8_t _index = STEP_LED[_step];
        bitWrite(LEDOutput[_index / COL_COUNT], _index % COL_COUNT, !bitRead(LEDOutput[_index / COL_COUNT], _index % COL_COUNT));
        ledUpdate = false;
        return true;
    }
    return false;
}

void MCView::displayString(uint8_t * _str){
    ledUpdate = true;
    // byte _segRows[] = {6, 3, 12, 13, 10, 15};
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

void MCView::pushDigit(uint8_t _c){
	// byte _segRows[] = {6, 3, 12, 13, 10, 15};
    ledUpdate = true;

	// catch the dot
	if(_c == '.'){
		LEDStates[segmentRows[5]] ^= 1 << 7;
	}
	else {
		// shift previous characters
		for(int i = 0; i < 5; i++){
			LEDStates[segmentRows[i]] = LEDStates[segmentRows[i+1]];
		}
		LEDStates[segmentRows[5]] = ~FONT_DEFAULT[_c-32];
	}
}

void MCView::displayBytes(uint8_t * _bytes){
    ledUpdate = true;

    for(int i = 0; i < 6; i++){
		LEDStates[segmentRows[i]] = _bytes[i];
    }
}
