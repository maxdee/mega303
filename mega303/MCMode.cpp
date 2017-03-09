#include "Arduino.h"
#include "MCMode.h"

MCMode::MCMode(){
	velocity = 100;

}

void MCMode::setInput(MCInput * _input){
	mcInput = _input;
}
void MCMode::setParts(MCPart *_mcParts){
	mcParts = _mcParts;
}

void MCMode::event(int _id, int _val){
	// iterate over parts, call for selected parts
	if(_id > 127){
		_id -= 127;
		_id *= 3;
		if(_val == 0) controlParts(&mcParts[2], PART_NOTE_ON, _id);
		else controlParts(&mcParts[2], PART_NOTE_OFF, _id);
	}
	else {
		controlParts(&mcParts[2], _id, _val);
	}
}

void MCMode::update(){}

void MCMode::controlParts(MCPart * _part, int _param, int _val){

	switch(_param){
		case PART_NOTE_ON:
			_part->noteOn(_val, velocity);
			break;
		case PART_NOTE_OFF:
			_part->noteOff(_val, velocity);
			break;
		default:
			char _buf[12];
			sprintf(_buf, "%03d%03d", _param, _val);
			mcInput->displayString(_buf);
	}

	// for Part : Parts
	//		if part is select
	//			part.control(_param, _val)
}



////////////////////////////////////////////////////////////////

ModeTwo::ModeTwo(){
	velocity = 100;
}
void ModeTwo::update(){}
void ModeTwo::event(int _id, int _val){
	// iterate over parts, call for selected parts
	if(_id > 127){
		_id -= 127;
		_id *= 7;
		if(_val == 0) controlParts(&mcParts[2], PART_NOTE_ON, _id);
		else controlParts(&mcParts[2], PART_NOTE_OFF, _id);
	}
	else {
		controlParts(&mcParts[2], _id, _val);
	}
}
