#include "Arduino.h"
#include "MCMode.h"

MCMode::MCMode(){
	velocity = 100;
}

void MCMode::begin(HardwareSerial * _serial){
	serial = _serial;
	memset(localLEDState, 255, 16);
}

void MCMode::setInput(MCInput * _input){
	mcInput = _input;
}

void MCMode::setParts(MCPart *_mcParts){
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
	}
}

void MCMode::update(){
	// push ledState to mcInput?
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

void ModeOne::update(){

}

void ModeOne::event(int _id, int _val){
	MCMode::event(_id, _val);
	// char _buf[12];
	// sprintf(_buf, "%03d%03d", _id, _val);
	// mcInput->displayString(_buf);
	// iterate over parts, call for selected parts
	if(_id > 127 && _id < 143){
		_id -= 127;
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

ModeTwo::ModeTwo(){
	velocity = 100;
}

void ModeTwo::update(){

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

void ModeThree::update(){
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
