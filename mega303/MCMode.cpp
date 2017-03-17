#include "Arduino.h"
#include "MCMode.h"

MCMode::MCMode(){
	velocity = 100;
	octave = 0;
	function = false;
	record = false;
}

void MCMode::begin(HardwareSerial * _serial){
	serial = _serial;
	memset(localLEDState, 255, 16);
}

void MCMode::setInput(MCInput * _input){
	mcInput = _input;
}

void MCMode::setParts(MCPart * _mcParts){
	mcParts = _mcParts;
}

void MCMode::event(int _id, int _val){
	if(_val){
		// check for part selection
		if(_id >= 64 && _id <= 71){
			int tmp = _id - 64;
			if(bitRead(partSelector, tmp)){
				bitClear(partSelector, tmp);
			}
			else {
				bitSet(partSelector, tmp);
			}
			mcInput->setLED(_id, bitRead(partSelector, tmp));
		}
		else if(_id == FUNC_BUTTON){
			function = !function;
			mcInput->setLED(FUNC_LED, function);
		}
		else if(_id == REC_BUTTON){
			record = !record;
			mcInput->setLED(REC_LED, record);
		}
		else if(_id == OCTAVE_UP_BUTTON || _id == OCTAVE_DOWN_BUTTON){
			if(_id == OCTAVE_UP_BUTTON) octave++;
			else octave--;
			if(octave > 6) octave = 6;
			else if(octave < 0) octave = 0;
			if(octave == 0) mcInput->setLED(OCTAVE_DOWN_LED, 1);
			else if(octave == 6) mcInput->setLED(OCTAVE_UP_LED, 1);
			else {
				mcInput->setLED(OCTAVE_DOWN_LED, 0);
				mcInput->setLED(OCTAVE_UP_LED, 0);
			}
		}
	}
}

void MCMode::update(uint8_t _step){
	// push ledState to mcInput?
	currentStep = _step;
}
void MCMode::unSelectMode(){
	memcpy(localLEDState, (*mcInput).LEDStates, 16);
}
void MCMode::selectMode(){
	memcpy((*mcInput).LEDStates, localLEDState, 16);
}

void MCMode::controlParts(int _id, int _val){
	for(int i = 0; i < PART_COUNT; i++){
		if(bitRead(partSelector, i)){
			// serial->println(i);
			(&mcParts[i])->event(_id, _val);
		}
	}
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

ModeOne::ModeOne(){
	velocity = 100;
}

void ModeOne::update(uint8_t _step){
	MCMode::update(_step);
}

void ModeOne::event(int _id, int _val){
	MCMode::event(_id, _val);
	// char _buf[12];
	// sprintf(_buf, "%03d%03d", _id, _val);
	// mcInput->displayString(_buf);
	// iterate over parts, call for selected parts
	if(function) return;
	if(_id >= 127 && _id <= 143){
		_id -= 127;
		_id += octave*16;
		if(_val == 1) {
			controlParts(PART_ADD_NOTE, _id);
			controlParts(PART_NOTE_ON, _id);
		}
		else controlParts(PART_NOTE_OFF, _id);
	}
	else if(_id == TRANSPOSE_BUTTON) controlParts(PART_CLEAR_ALL, 0);
	else {
		// controlParts(_id, _val);
	}
}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

ModeTwo::ModeTwo(){
	velocity = 100;
}

void ModeTwo::update(uint8_t _step){
	MCMode::update(_step);

}

void ModeTwo::event(int _id, int _val){
	MCMode::event(_id, _val);
	// char _buf[12];
	// sprintf(_buf, "%03d%03d", _id, _val);
	// mcInput->displayString(_buf);
	// iterate over parts, call for selected parts
	if(_id >= 127 && _id < 143){
		_id -= 127;
		_id *= 3;
		if(_val == 1) controlParts(PART_NOTE_ON, _id);
		else controlParts(PART_NOTE_OFF, _id);
	}
	else {
		controlParts(_id, _val);
	}
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

ModeThree::ModeThree(){
	velocity = 100;
}

void ModeThree::update(uint8_t _step){
	MCMode::update(_step);

	cnt++;
	if(cnt % (div+1) == 0){
		controlParts(PART_NOTE_OFF, note);
		note = random(low, high);
		controlParts(PART_NOTE_ON, note);
	}
}
// random little drummer
void ModeThree::event(int _id, int _val){
	MCMode::event(_id, _val);
	// char _buf[12];
	// sprintf(_buf, "%03d%03d", low, high);
	// mcInput->displayString(_buf);
	switch(_id){
		case POT_0:
			div = _val;
			break;
		case POT_1:
			high = _val;
			break;
		case POT_2:
			low = _val;
			break;
	}
}
