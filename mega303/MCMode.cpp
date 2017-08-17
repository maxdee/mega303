#include "Arduino.h"
#include "MCMode.h"

// uint8_t MCMode::partSelector;
// bool MCMode::function;
// bool MCMode::record;
uint8_t MCMode::octave;
uint8_t MCMode::selectRadio;

MCMode::MCMode(){
	octave = 0;
	function = false;
	record = false;
}

void MCMode::begin(HardwareSerial * _serial){
	serial = _serial;
	memset(localLEDState, 255, 16);
	octave = 3;
	knobBank = 0;
}

void MCMode::setInput(MCInput * _input){
	mcInput = _input;
}

void MCMode::setParts(MCPart * _mcParts){
	mcParts = _mcParts;
}

void MCMode::event(uint8_t _id, uint8_t _val){
	if(_val){
		// check for part selection
		if(_id >= 64 && _id <= 71){
			int tmp = _id - 64;
			if(bitRead(partSelector, tmp)){
				bitClear(partSelector, tmp);
			}
			else {
				bitSet(partSelector, tmp);
				updateStepLEDs();
			}
			mcInput->setLED(_id, bitRead(partSelector, tmp));
		}
		else if(_id == FWD_BUTTON || _id == BWD_BUTTON){
			if(_id == FWD_BUTTON) knobBank++;
			else knobBank--;
			char _buf[12];
			sprintf(_buf, "knB%03d", knobBank);
			mcInput->displayString(_buf);
		}
		else if(_id == ENCODER_BUTTON){
			if(selectRadio == TONE_LED)	incrementPatch(_val);
			// else if(selectRadio == TEMPO_LED) incrementTempo(_val);
		}
		else if(_id == OCTAVE_UP_BUTTON || _id == OCTAVE_DOWN_BUTTON){
			if(_id == OCTAVE_UP_BUTTON) octave++;
			else octave--;
			if(octave > 12) octave = 12;
			else if(octave < 0) octave = 0;
			if(octave == 0) mcInput->setLED(OCTAVE_DOWN_LED, 1);
			else if(octave == 12) mcInput->setLED(OCTAVE_UP_LED, 1);
			else {
				mcInput->setLED(OCTAVE_DOWN_LED, 0);
				mcInput->setLED(OCTAVE_UP_LED, 0);
			}
			char _buf[12];
			sprintf(_buf, "OCT%03d", octave);
			mcInput->displayString(_buf);
		}
		else if(!mcInput->checkButton(SHIFT_BUTTON) && _id == SELECT_RIGHT_BUTTON || _id == SELECT_LEFT_BUTTON){
			mcInput->setLED(selectRadio, 0);
			if(_id == SELECT_RIGHT_BUTTON) selectRadio++;
			else selectRadio--;
			if(selectRadio > 92) selectRadio = 92;
			else if(selectRadio < 88) selectRadio = 88;
			mcInput->setLED(selectRadio, 1);
		}
		else {
			switch(_id){
				case FUNC_BUTTON:
					function = !function;
					mcInput->setLED(FUNC_LED, function);
					break;
				case REC_BUTTON:
					record = !record;
					mcInput->setLED(REC_LED, record);
					break;
				case SELECT_PART_BUTTON:
					partSelect = !partSelect;
					mcInput->setLED(SELECT_PART_LED, partSelect);
					break;
				case MUTE_PART_BUTTON:
					partMute = !partMute;
					mcInput->setLED(MUTE_PART_LED, partMute);
					break;
				case RHYTHM_MUTE_BUTTON:
					rhythmMute = !rhythmMute;
					mcInput->setLED(RHYTHM_MUTE_LED, rhythmMute);
					break;
			}
		}

	}
}

void MCMode::incrementPatch(int _v){
	if(_v == 1){
		patchIndex--;
	}
	else if(_v == 2){
		patchIndex++;
	}
	if(patchIndex < 0) patchIndex = PATCH_COUNT;
	patchIndex %= PATCH_COUNT;

	char _buf[12];
	sprintf(_buf, "PGM%03d", patchIndex);
	mcInput->displayString(_buf);
	for(int i = 1; i < PART_COUNT; i++){
		if(bitRead(partSelector, i)){
			// serial->println(i);
			(&mcParts[i])->setPatch(patchIndex);
		}
	}
}

void MCMode::updateStepLEDs(){
	// if(selectRadio == TONE_LED){
		for(int i = 0; i < PART_COUNT; i++){
			if(bitRead(partSelector, i)){
				mcInput->setStepLEDs((&mcParts[i])->stepLEDs);
			}
		}
	// }
}

// void MCMode::incrementTempo(int _v){
// 	patchIndex += _v;
// 	patchIndex %= PATCH_COUNT;
// 	if(patchIndex < 0) patchIndex = PATCH_COUNT - 1;
//
// 	char _buf[12];
// 	sprintf(_buf, "PGM%03d", patchIndex);
// 	mcInput->displayString(_buf);
// 	for(int i = 1; i < PART_COUNT; i++){
// 		if(bitRead(partSelector, i)){
// 			// serial->println(i);
// 			(&mcParts[i])->setPatch(patchIndex);
// 		}
// 	}
// }

uint8_t MCMode::getKey(uint8_t _key){
	if(_key < 127 || _key > 143) return 0;
	else return (_key-127) + octave * 8;
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

void MCMode::controlParts(uint8_t _id, uint8_t _val){
	for(int i = 0; i < PART_COUNT; i++){
		if(bitRead(partSelector, i)){
			// serial->println(i);
			// char _buf[12];
			// sprintf(_buf, "%03d%03d", _id, _val);
			// mcInput->displayString(_buf);

			(&mcParts[i])->event(_id, _val);
		}
	}
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

ModeOne::ModeOne(){
}

void ModeOne::update(uint8_t _step){
	MCMode::update(_step);
}

void ModeOne::event(uint8_t _id, uint8_t _val){
	MCMode::event(_id, _val);
	// char _buf[12];
	// sprintf(_buf, "%03d%03d", _id, _val);
	// mcInput->displayString(_buf);
	// iterate over parts, call for selected parts
	// if(function) return;
	int _key = getKey(_id);
	if(_key > 0){
		if(_val == 1) {
			// controlParts(PART_ADD_NOTE, _id);
			if(mcInput->checkButton(SHIFT_BUTTON) && _key != 0){
				controlParts(PART_CLEAR_STEP, _id-128);
				updateStepLEDs();
			}
			else if(function){
				if(!record){
					controlParts(PART_NOTE_ON, _key);
					selectedKey = _key;
				}
				else {
					controlParts(PART_ADD_NOTE, selectedKey);
					updateStepLEDs();
				}
			}
			else {
				controlParts(PART_NOTE_ON, _key);
				if(record) {
					controlParts(PART_ADD_NOTE, _key);
					updateStepLEDs();
				}
			}
		}
		else controlParts(PART_NOTE_OFF, _key);
	}
	else if(_id == TRANSPOSE_BUTTON) controlParts(PART_CLEAR_ALL, 0);
	else {
		// char _buf[12];
		// sprintf(_buf, "%03d%03d", _id, _val);
		// mcInput->displayString(_buf);
		knobBanks(_id, _val);
		// controlParts(_id, _val);
	}
}



void MCMode::knobBanks(uint8_t _id, uint8_t _val){
	if(knobBank == 0){
		switch(_id){
			case POT_0:
				controlParts(PART_DECAY, _val);
				break;
			case POT_1:
				controlParts(PART_ATTACK, _val);
				break;
			case POT_2:
				controlParts(PART_FINE_TUNE, _val);
				break;
			case POT_3:
				controlParts(PART_COARSE_TUNE, _val);
				break;
			case POT_4:
				controlParts(PART_CUTOFF, _val);
				break;
			case POT_5:
				controlParts(PART_RESONANCE, _val);
				break;
			case POT_6:
				controlParts(PART_RELEASE, _val);
				break;
		}
	}
	else if(knobBank == 1){
		switch(_id){
			case POT_0:
				controlParts(PART_ATTACK, _val);
				break;
			case POT_1:
				controlParts(PART_VIBRATO_RATE, _val);
				break;
			case POT_2:
				controlParts(PART_VIBRATO_DEPTH, _val);
				break;
			case POT_3:
				controlParts(PART_VIBRATO_DELAY, _val);
				break;
			case POT_4:
				controlParts(PART_MODULATION, _val);
				break;
			case POT_5:
				controlParts(PART_PAN, _val);
				break;
			case POT_6:
				controlParts(PART_VOLUME, _val);
				break;
		}
	}
	else if(knobBank == 2){
		switch(_id){
			case POT_0:
				controlParts(PART_ATTACK, _val);
				break;
			case POT_1:
				controlParts(PART_VIBRATO_RATE, _val);
				break;
			case POT_2:
				controlParts(PART_VIBRATO_DEPTH, _val);
				break;
			case POT_3:
				controlParts(PART_VIBRATO_DELAY, _val);
				break;
			case POT_4:
				controlParts(PART_MODULATION, _val);
				break;
			case POT_5:
				controlParts(PART_CHORUS_DEPTH, _val);
				break;
			case POT_6:
				controlParts(PART_REVERB_DEPTH, _val);
				break;
		}
	}
	else if(knobBank == 3){
		switch(_id){
			case POT_0:
				controlParts(PART_DRUM_PITCH, _val);
				break;
			case POT_1:
				controlParts(PART_DRUM_TVA, _val);
				break;
			case POT_2:
				controlParts(PART_DRUM_PAN, _val);
				break;
			case POT_3:
				controlParts(PART_DRUM_REVERB, _val);
				break;
			case POT_4:
				controlParts(PART_DRUM_CHORUS, _val);
				break;
			case POT_5:
				controlParts(PART_DRUM_PAN, _val);
				break;
			case POT_6:
				controlParts(PART_VOLUME, _val);
				break;
		}
	}
	else if(knobBank == 4){
		char _buf[12];
		sprintf(_buf, "%03d%03d", _id, _val);
		mcInput->displayString(_buf);
	}
}



////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

ModeTwo::ModeTwo(){
}

void ModeTwo::update(uint8_t _step){
	MCMode::update(_step);

}

void ModeTwo::event(uint8_t _id, uint8_t _val){
	MCMode::event(_id, _val);
	// char _buf[12];
	// sprintf(_buf, "%03d%03d", _id, _val);
	// mcInput->displayString(_buf);
	// iterate over parts, call for selected parts
	int _key = getKey(_id);
	if(_key > 0){
		_key *= 3;
		if(_val == 1) controlParts(PART_NOTE_ON, _key);
		else controlParts(PART_NOTE_OFF, _key);
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
void ModeThree::event(uint8_t _id, uint8_t _val){
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
