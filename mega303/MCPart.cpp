#include "Arduino.h"
#include "MCPart.h"


MCPart::MCPart(){

}

void MCPart::begin(HardwareSerial * _serial, MCView * _view, uint8_t _chan){
	channel = _chan;
	serial = _serial;
	view = _view;
	memset(steps, 0, sizeof(steps));// * STEP_COUNT * SLOT_COUNT);
	velocity = 100;
	stepLEDs = 0;
	patchIndex = 0;
}

void MCPart::debug(){
	bool clear = true;
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < SLOT_COUNT; j++){
			if(steps[i][j] != 0){
				clear = false;
				view->printf("s%2io%2iv%3i\n", i, j, steps[i][j]);
			}
		}
	}
	if(clear){
		view->printf("clear %i\n", channel);
	}

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
		case PART_CUTOFF:
			cutoff(_val);
			break;
		case PART_RESONANCE:
			resonance(_val);
			break;
		case PART_ATTACK:
			attackTime(_val);
			break;
		case PART_DECAY:
			decayTime(_val);
			break;
		case PART_RELEASE:
			releaseTime(_val);
			break;
		case PART_COARSE_TUNE:
			coarseTune(_val);
			break;
		case PART_FINE_TUNE:
			fineTune(_val);
			break;
		case PART_CHORUS_DEPTH:
			chorusDepth(_val);
			break;
		case PART_REVERB_DEPTH:
			reverbDepth(_val);
			break;

		case PART_VIBRATO_RATE:
			vibratoRate(_val);
			break;
		case PART_VIBRATO_DEPTH:
			vibratoDepth(_val);
			break;
		case PART_VIBRATO_DELAY:
			vibratoRate(_val);
			break;
		case PART_PAN:
			pan(_val);
			break;
		case PART_VOLUME:
			volume(_val);
			break;
		case PART_MODULATION:
			modulation(_val);
			break;
		case PART_PORTAMENTO_TIME:
			portamentoTime(_val);
			break;

		case REVERB_TYPE:
			midiSysEx(REVERB_TYPE_ADDRESS, _val/15);
			break;
		case REVERB_TIME:
			midiSysEx(REVERB_TIME_ADDRESS, _val);
			break;
		case REVERB_FEEDBACK:
			midiSysEx(REVERB_FEEDBACK_ADDRESS, _val);
			break;


		case CHORUS_TYPE:
			midiSysEx(CHORUS_RATE_ADDRESS, _val/15);
			break;

		case CHORUS_RATE:
			midiSysEx(CHORUS_RATE_ADDRESS, _val);
			break;
		case CHORUS_FEEDBACK:
			midiSysEx(CHORUS_FEEDBACK_ADDRESS, _val);
			break;
		// case
		// default:
		// char _buf[12];
		// sprintf(_buf, "%03d%03d", _param, _val);
		// mcInput->displayString(_buf);
	}
}

void MCPart::clearStep(int _step){
	for(int i = 0; i < SLOT_COUNT; i++){
		noteOff(steps[_step][i], 0);
		steps[_step][i] = 0;
		bitClear(stepLEDs, _step);
	}
}

void MCPart::clearAll(){
	for(int i = 0; i < STEP_COUNT; i++){
		clearStep(i);
	}
}

void MCPart::addNote(int _step, uint8_t _pitch, uint8_t _vel){
	// currentSlot = 0;
	previous = _pitch;
	if(steps[_step][currentSlot] > 0) noteOff(steps[_step][currentSlot], 0);
	// check for empty slot?
	steps[_step][currentSlot] = _pitch;
	steps[(_step+1) % STEP_COUNT][currentSlot] = 128 + _pitch; //  adds a note off
	bitClear(stepLEDs, _step);
	bitSet(stepLEDs, _step);
	currentSlot++;
	currentSlot %= SLOT_COUNT;
}

void MCPart::step(int _step){
	// do note offs

	for(int i = 0; i < SLOT_COUNT; i++){
		if(steps[currentStep][i] > 0) {
			noteOff(steps[currentStep][i], 0);
		}
	}
	// do note on!
	currentStep = _step;
	for(int i = 0; i < SLOT_COUNT; i++){
		if(steps[currentStep][i] > 0) {
			// view->printf("s%i c%i v%i \n", _step, channel, steps[currentStep][i]);
			noteOn(steps[currentStep][i], 100);
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
//F0H || 41H 10H 00H 03H 12H || 00H 40H 01H 30H || 06H || checksum 09h || F7H
//
void MCPart::midiSysEx(uint8_t * _addr, uint8_t value){
	byte data[13] = {0xF0, // 0
		 			0x41, 0x10, 0x00, 0x03, 0x12, // 1 2 3 4 5
					0x00, 0x00, 0x00, 0x00, // 6 7 8 9
					0x00, // 10
					0x00, // 11
				 	0xF7}; //12

	data[6] = _addr[0];
	data[7] = _addr[1];
	data[8] = _addr[2];
	data[9] = _addr[3];
	data[10] = value;

	// byte checksum = GetRolandChecksum(data+5, 4);
	byte _checksum = (_addr[0]+_addr[1]+_addr[2]+_addr[3]+value);
	while(_checksum > 0x80) _checksum -= 0x80;
	data[11] = 0x80 - _checksum;

	// Sysex starts wth 0xF0, ends with 0xF7
	for (int i = 0; i < 13; i++){
		serial->write(data[i]);
	}
	// serial->write(0xF7);

	// delay(50);
}

// calculate Roland sysex checksum
byte MCPart::GetRolandChecksum(byte* data, int length){
	// Roland sysex checksum = 128 - (data sum % 128)
	int sum = 0;
	for (int i = 0; i < length; i++)
	sum += data[i];

	int rem = sum % 128;
	int checksum = (128 - rem);
	//int check = sum + checksum;
	return byte(checksum);
}


///////////////////////////////////////////////////////////////////////////////
// RPN
///////////////////////////////////////////////////////////////////////////////

void MCPart::setPatch(uint16_t _index){

}

void MCPart::incrementPatch(int8_t _i){

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
		controlChange(5, _val);
	}
	// controlChange(66, _val);

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

void MCPart::reverbDepth(uint8_t _val){
	controlChange(91, _val);
}
void MCPart::chorusDepth(uint8_t _val){
	controlChange(93, _val);
}

// 00H 40H 01H 30H
// void MCPart::reverbType(uint8_t _val){
// 	midiSysEx(REVERB_TYPE_ADDRESS, _val/15);
// }
//
//
// void MCPart::chorusType(uint8_t _val){
// 	midiSysEx(0x00, 0x40, 0x01, 0x38, _val/15);
// }
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
// SynthPart
///////////////////////////////////////////////////////////////////////////////

SynthPart::SynthPart(){
}


void SynthPart::event(uint8_t _id, uint8_t _val){
	MCPart::event(_id, _val);

}


void SynthPart::incrementPatch(int8_t _i){
	patchIndex += _i;
	if(patchIndex < 0) patchIndex = PATCH_COUNT-1;
	patchIndex %= PATCH_COUNT;
	setPatch(patchIndex);
}

void SynthPart::setPatch(uint16_t _index){
	patchIndex = _index;
	view->printf("SYN%03d", patchIndex);
	controlChange(00, PROGRAM_BANKS[_index][0]);
	controlChange(32, 00);
	programChange(PROGRAM_BANKS[_index][1]);
}






///////////////////////////////////////////////////////////////////////////////
// DrumPart
///////////////////////////////////////////////////////////////////////////////

DrumPart::DrumPart(){

}

void DrumPart::event(uint8_t _id, uint8_t _val){
	MCPart::event(_id, _val);
	switch(_id){
		case PART_DRUM_PITCH:
			drumPitch(previous, _val);
			break;
		case PART_DRUM_TVA:
			drumTVA(previous, _val);
			break;
		case PART_DRUM_PAN:
			drumPan(previous, _val);
			break;
		case PART_DRUM_REVERB:
			drumReverb(previous, _val);
			break;
		case PART_DRUM_CHORUS:
			drumChorus(previous, _val);
			break;

		case REVERB_TYPE:
			midiSysEx(REVERB_TYPE_ADDRESS, _val/15);
			break;
		case REVERB_TIME:
			midiSysEx(REVERB_TIME_ADDRESS, _val);
			break;
		case REVERB_FEEDBACK:
			midiSysEx(REVERB_FEEDBACK_ADDRESS, _val);
			break;
	}
}

void DrumPart::incrementPatch(int8_t _i){
	patchIndex += _i;
	if(patchIndex < 0) patchIndex = DRUM_KIT_COUNT-1;
	patchIndex %= DRUM_KIT_COUNT;
	view->printf("RTM%03d", patchIndex);
	setPatch(patchIndex);
}

void DrumPart::setPatch(uint16_t _pc){
	patchIndex = _pc;
	programChange(DRUM_KITS[_pc]);
}


// NRPN - drum editing

void DrumPart::drumPitch(uint8_t _note, uint8_t _val){
	controlChange(99, 24);
	controlChange(98, _note);
	controlChange(06, _val);
}

void DrumPart::drumTVA(uint8_t _note, uint8_t _val){
	controlChange(99, 26);
	controlChange(98, _note);
	controlChange(06, _val);
}

void DrumPart::drumPan(uint8_t _note, uint8_t _val){
	controlChange(99, 28);
	controlChange(98, _note);
	controlChange(06, _val);
}

void DrumPart::drumReverb(uint8_t _note, uint8_t _val){
	controlChange(99, 29);
	controlChange(98, _note);
	controlChange(06, _val);
}

void DrumPart::drumChorus(uint8_t _note, uint8_t _val){
	controlChange(99, 30);
	controlChange(98, _note);
	controlChange(06, _val);
}
