#include "Arduino.h"
#include "MCPart.h"

MCPart::MCPart(){

}

void MCPart::begin(HardwareSerial * _serial, uint8_t _chan){
	channel = _chan;
	serial = _serial;
	memset(steps, 0, sizeof(steps[0][0]) * STEP_COUNT * SLOT_COUNT);
}

void MCPart::event(uint8_t _id, uint8_t _val){
	switch(_id){
		case PART_NOTE_ON:
			noteOn(_val, velocity);
			break;
		case PART_NOTE_OFF:
			noteOff(_val, velocity);
			break;
		case PART_ADD_NOTE:
			addNote(currentStep, _val, velocity);
			break;
		case PART_CLEAR_ALL:
			clearAll();
			break;
		case PART_CLEAR_STEP:
			clearStep(_val);
			break;
		// default:
		// char _buf[12];
		// sprintf(_buf, "%03d%03d", _param, _val);
		// mcInput->displayString(_buf);
	}
}

void MCPart::clearStep(int _step){
	for(int i = 0; i < 127; i++){
		steps[_step][i] = 0;
	}
}

void MCPart::clearAll(){
	for(int i = 0; i < STEP_COUNT; i++){
		clearStep(i);
	}
}

void MCPart::addNote(int _step, uint8_t _pitch, uint8_t _vel){
	steps[_step][currentSlot] = _pitch;
	steps[(_step+1) % STEP_COUNT][currentSlot] = 128 + _pitch;
	currentSlot++;
	currentSlot %= SLOT_COUNT;
}

void MCPart::step(int _step){
	currentStep = _step;
	for(int i = 0; i < SLOT_COUNT; i++){
		if(steps[_step][i] >= 128) {
			noteOff(steps[_step][i]-128, 0);
		}
		else if(steps[_step][i] > 0) {
			noteOn(steps[_step][i], 100);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// MIDI
///////////////////////////////////////////////////////////////////////////////

void MCPart::noteOn(uint8_t _pitch, uint8_t _vel){
	serial -> write(0x90 | channel);
	serial -> write(_pitch);
	serial -> write(_vel);
}

void MCPart::noteOff(uint8_t _pitch, uint8_t _vel){
	serial -> write(0x80 | channel);
	serial -> write(_pitch);
	serial -> write(_vel);
}

void MCPart::controlChange(uint8_t _cc, uint8_t _val){
	serial -> write(0xB0 | channel);
	serial -> write(_cc);
	serial -> write(_val);
}

void MCPart::programChange(uint8_t _val){
	serial -> write(0xC0 | channel);
	serial -> write(_val);
}

///////////////////////////////////////////////////////////////////////////////
// RPN
///////////////////////////////////////////////////////////////////////////////

void MCPart::setPatch(uint8_t _bank, uint8_t _pc){
	controlChange(00, _bank);
	controlChange(32, 00);
	programChange(_pc);
}

void MCPart::setKit(uint8_t _pc){
	programChange(_pc);
}

void MCPart::coarseTune(uint8_t _val){
	controlChange(101, 0);
	controlChange(100, 2);
	controlChange(6, _val);
}

void MCPart::fineTune(uint8_t _val){
	controlChange(101, 0);
	controlChange(100, 1);
	controlChange(6, _val);
}

void MCPart::cutoff(uint8_t _val){
	controlChange(99, 1);
	controlChange(98, 32);
	controlChange(6, _val);
}

void MCPart::resonance(uint8_t _val){
	controlChange(99, 1);
	controlChange(98, 33);
	controlChange(6, _val);
}

void MCPart::portamentoTime(uint8_t _val){
	if(_val == 0){
		controlChange(126, 0); // mono off
		controlChange(65, 0); // portamento off
	}
	else {
		controlChange(126, 1); // mono on
		controlChange(65, 127); // portamento on
	}
	controlChange(5, _val);
}

void MCPart::pan(uint8_t _val){
	controlChange(10, _val);
}

void MCPart::volume(uint8_t _val){
	controlChange(7, _val);
}

void MCPart::modulation(uint8_t _val){
	controlChange(1, _val);
}

void MCPart::expression(uint8_t _val){
	controlChange(11, _val);
}

void MCPart::sustain(uint8_t _val){
	controlChange(64, _val);
}

///////////////////////////////////////////////////////////////////////////////
// NRPN - patch editing
///////////////////////////////////////////////////////////////////////////////

void MCPart::vibratoRate(uint8_t _val){
	controlChange(99, 1);
	controlChange(98, 8);
	controlChange(06, _val);
}

void MCPart::vibratoDepth(uint8_t _val){
	controlChange(99, 1);
	controlChange(98, 9);
	controlChange(06, _val);
}

void MCPart::vibratoDelay(uint8_t _val){
	controlChange(99, 1);
	controlChange(98, 10);
	controlChange(06, _val);
}

void MCPart::attackTime(uint8_t _val){
	controlChange(99, 1);
	controlChange(98, 99);
	controlChange(06, _val);
}

void MCPart::decayTime(uint8_t _val){
	controlChange(99, 1);
	controlChange(98, 100);
	controlChange(06, _val);
}

void MCPart::releaseTime(uint8_t _val){
	controlChange(99, 1);
	controlChange(98, 102);
	controlChange(06, _val);
}

///////////////////////////////////////////////////////////////////////////////
// NRPN - drum editing
///////////////////////////////////////////////////////////////////////////////

void MCPart::drumPitch(uint8_t _note, uint8_t _val){
	controlChange(99, 24);
	controlChange(98, _note);
	controlChange(06, _val);
}

void MCPart::drumTVA(uint8_t _note, uint8_t _val){
	controlChange(99, 26);
	controlChange(98, _note);
	controlChange(06, _val);
}

void MCPart::drumPan(uint8_t _note, uint8_t _val){
	controlChange(99, 28);
	controlChange(98, _note);
	controlChange(06, _val);
}

void MCPart::drumReverb(uint8_t _note, uint8_t _val){
	controlChange(99, 29);
	controlChange(98, _note);
	controlChange(06, _val);
}

void MCPart::drumChorus(uint8_t _note, uint8_t _val){
	controlChange(99, 30);
	controlChange(98, _note);
	controlChange(06, _val);
}
