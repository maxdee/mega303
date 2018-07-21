#include "Arduino.h"
#include "MCMode.h"

// uint8_t MCMode::selectedParts;
// bool MCMode::functionToggle;
// bool MCMode::recordToggle;
uint8_t MCMode::octave;
uint8_t MCMode::selectRadio;

MCMode::MCMode(){
	octave = 0;
	functionToggle = false;
	recordToggle = false;
	pressedKeys = 0;
}

void MCMode::begin(MCView * _view){
	view = _view;
	memset(localLEDState, 255, 16);
	octave = 3;
	knobBank = 0;
}

void MCMode::setInput(MCInput * _input){
	mcInput = _input;
}

void MCMode::setParts(MCPart ** _mcParts){
	mcParts = _mcParts;
}

void MCMode::setDrumPart(DrumPart * _drums){
	drumPart = _drums;
}

void MCMode::partSelecting(uint8_t _id){
	int tmp = _id - ID_MIN_PART;
	if(partSelectToggle){
		selectedParts ^= 1 << tmp;
		mcInput->setPartSelectLEDs(selectedParts);
	}
	else if(partMuteToggle){
		mutedParts ^= 1 << tmp;
		mcInput->setPartSelectLEDs(mutedParts);
		for(int i = 0; i < 8; i++){
			mcParts[i]->event(PART_MUTE, bitRead(mutedParts, i));
		}
	}
	else if(rhythmMuteToggle){
		rhythmMute ^= 1 << tmp;
		mcInput->setPartSelectLEDs(rhythmMute);
	}
}

void MCMode::event(uint8_t _id, uint8_t _val){
	if(_val){
		// check for part selection
		if(_id >= ID_MIN_PART && _id <= ID_MAX_PART){
			partSelecting(_id);
		}
		// knob bank selection
		else if(_id == FWD_BUTTON || _id == BWD_BUTTON){
			if(_id == FWD_BUTTON) knobBank++;
			else knobBank--;
			view->printf("knB%03d", knobBank);
		}
		// encoder
		else if(_id == ENCODER_BUTTON){
			if(selectRadio == TONE_LED)	incrementPatch(_val);
			// else if(selectRadio == TEMPO_LED) incrementTempo(_val);
		}
		// octave selection
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
			view->printf("OCT%03d", octave);
		}
		// select radio section
		else if(!mcInput->checkButton(SHIFT_BUTTON) && _id == SELECT_RIGHT_BUTTON || _id == SELECT_LEFT_BUTTON){
			mcInput->setLED(selectRadio, 0);
			if(_id == SELECT_RIGHT_BUTTON) selectRadio++;
			else selectRadio--;
			if(selectRadio > 92) selectRadio = 92;
			else if(selectRadio < 88) selectRadio = 88;
			mcInput->setLED(selectRadio, 1);
		}
		// toggles
		else {
			switch(_id){
				case FUNC_BUTTON:
					functionToggle = !functionToggle;
					mcInput->setLED(FUNC_LED, functionToggle);
					break;
				case REC_BUTTON:
					recordToggle = !recordToggle;
					mcInput->setLED(REC_LED, recordToggle);
					break;
				case SELECT_PART_BUTTON:
					partSelectToggle = true;
					mcInput->setPartSelectLEDs(selectedParts);

					partMuteToggle = false;
					rhythmMuteToggle = false;
					mcInput->setLED(SELECT_PART_LED, partSelectToggle);
					mcInput->setLED(MUTE_PART_LED, partMuteToggle);
					mcInput->setLED(RHYTHM_MUTE_LED, rhythmMuteToggle);
					break;
				case MUTE_PART_BUTTON:
					partSelectToggle = false;
					partMuteToggle = true;
					mcInput->setPartSelectLEDs(mutedParts);

					rhythmMuteToggle = false;
					mcInput->setLED(SELECT_PART_LED, partSelectToggle);
					mcInput->setLED(MUTE_PART_LED, partMuteToggle);
					mcInput->setLED(RHYTHM_MUTE_LED, rhythmMuteToggle);
					break;
				case RHYTHM_MUTE_BUTTON:
					partSelectToggle = false;
					partMuteToggle = false;
					rhythmMuteToggle = true;
					mcInput->setPartSelectLEDs(rhythmMute);
					mcInput->setLED(SELECT_PART_LED, partSelectToggle);
					mcInput->setLED(MUTE_PART_LED, partMuteToggle);
					mcInput->setLED(RHYTHM_MUTE_LED, rhythmMuteToggle);
					break;
				// case SELECT_PART_BUTTON:
				// 	partSelectToggle = !partSelectToggle;
				// 	mcInput->setLED(SELECT_PART_LED, partSelectToggle);
				// 	break;
				// case MUTE_PART_BUTTON:
				// 	partMuteToggle = !partMuteToggle;
				// 	mcInput->setLED(MUTE_PART_LED, partMuteToggle);
				// 	break;
				// case RHYTHM_MUTE_BUTTON:
				// 	rhythmMuteToggle = !rhythmMuteToggle;
				// 	mcInput->setLED(RHYTHM_MUTE_LED, rhythmMuteToggle);
				// 	break;
			}
		}
	}
}

void MCMode::incrementPatch(int _v){
	uint16_t _patchIndex = 0;
	for(int i = 0; i < PART_COUNT; i++){
		if(bitRead(selectedParts, i)){
			if(_v == 1){
				mcParts[i]->incrementPatch(-1);
			}
			else if(_v == 2){
				mcParts[i]->incrementPatch(1);
			}
		}
	}
}


// void MCMode::incrementTempo(int _v){
// 	patchIndex += _v;
// 	patchIndex %= PATCH_COUNT;
// 	if(patchIndex < 0) patchIndex = PATCH_COUNT - 1;
//
// 	view->printf("PGM%03d", patchIndex);
// 	for(int i = 1; i < PART_COUNT; i++){
// 		if(bitRead(selectedParts, i)){
// 			// serial->println(i);
// 			mcParts[i]->setPatch(patchIndex);
// 		}
// 	}
// }

uint8_t MCMode::getKey(uint8_t _key){
	if(_key < 127 || _key > 143) return 0;
	else return (_key-127) + octave * 8;
}

void MCMode::update(uint8_t _step){
	currentStep = _step;

	for(int j = 0; j < PART_COUNT; j++){
		if(bitRead(selectedParts, j)){
			for(int i = 0; i < 16; i++){
				if(bitRead(pressedKeys, i)){
					bitWrite(mcParts[i]->patterns[getKey(i+127)], _step, 1);
					view->printf("%3i%3i",_step, getKey(i+127));
				}
			}
		}
	}
}

void MCMode::unSelectMode(){
	memcpy(localLEDState, (*mcInput).LEDStates, 16);
}

void MCMode::selectMode(){
	memcpy((*mcInput).LEDStates, localLEDState, 16);
}

void MCMode::controlParts(uint8_t _id, uint8_t _val){
	for(int i = 0; i < PART_COUNT; i++){
		if(bitRead(selectedParts, i)){
			// serial->println(i);
			// view->printf("%03d%03d", _id, _val);
			mcParts[i]->event(_id, _val);
		}
	}
}

void MCMode::sequenceEdit(uint8_t _id, uint8_t _val){
	int _key = getKey(_id);
	if(_key > 0){
		// view->printf("%3i%3i", _id, _val);
		if(_val == 1) {
			controlParts(PART_NOTE_ON, _key);
			if(recordToggle){
				bitWrite(pressedKeys, _id-127, 1);
				partToggleStepPitch(currentStep, _key, 1);
			}
		}
		else {
			controlParts(PART_NOTE_OFF, _key);
			if(recordToggle){
				bitWrite(pressedKeys, _id-127, 0);
				partToggleStepPitch(currentStep, _key, 0);
			}
		}
	}
	else if(_id == TRANSPOSE_BUTTON) {
		for(int i = 0; i < PART_COUNT; i++){
			if(bitRead(selectedParts, i)){
				// do note off
				for(int j = 0; j < 127; j++){
					for(int k = 0; k < 16; k++){
						if(bitRead(mcParts[i]->patterns[j], k)){
							mcParts[i]->noteOff(i,100);
						}
					}
				}
				memset(mcParts[i]->patterns, 0, sizeof(mcParts[i]->patterns));
			}
		}
	}
}


void MCMode::partToggleStepPitch(uint8_t _step, uint8_t _pitch, uint8_t _state){
	for(int i = 0; i < PART_COUNT; i++){
		if(bitRead(selectedParts, i)){
			bitWrite(mcParts[i]->patterns[_pitch], _step, _state);
		}
	}
}


void MCMode::drumSequenceEdit(uint8_t _id, uint8_t _val){
	int _key = getKey(_id);
	if(_key > 0){
		if(!recordToggle){
			if(_val == 1) {
				view->printf("P-E%3i", _key);
				drumPart->selectedPitch = _key;
				selectedPitch = _key;

				uint16_t _pat = drumPart->patterns[selectedPitch];
				mcInput->setStepLEDs(_pat);

				controlParts(PART_NOTE_ON, _key);

			}
			else {
				controlParts(PART_NOTE_OFF, _key);
			}
		}
		else {
			if(_val == 1) {

				if(_id >= 127 || _id <= 143){
					uint16_t _pat = drumPart->patterns[selectedPitch];
					bitWrite(_pat, _id-128, !bitRead(_pat, _id-128));
					drumPart->patterns[selectedPitch] = _pat;
					mcInput->setStepLEDs(_pat);
				}
			}
		}
	}
	else if(_id == TRANSPOSE_BUTTON) {
		memset(drumPart->patterns, 0, sizeof(drumPart->patterns));
		// if(){
		//
		// }
	}
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

ModeOne::ModeOne(){
	drumEditMode = PATTERN_EDIT;
}

void ModeOne::update(uint8_t _step){
	MCMode::update(_step);
}

void ModeOne::event(uint8_t _id, uint8_t _val){
	uint8_t _i = _id;
	MCMode::event(_i, _val);
	// view->printf("%03d%03d", _id, _val);

	if(_id == ENTER_BUTTON){
		drumEditMode = STEP_REC;
	}
	else if(_id == EXIT_BUTTON){
		drumEditMode = PATTERN_EDIT;
	}
	if(selectedParts == 1){
		drumSequenceEdit(_id, _val);
	}
	else {
		sequenceEdit(_id, _val);
	}


	knobBanks(_id, _val);

	// iterate over parts, call for selected parts
	// if(functionToggle) return;
	//
	// else {
	//
	// 	// view->printf("%03d%03d", _id, _val);
	//
	// 	// controlParts(_id, _val);
	// }
}



void ModeOne::knobBanks(uint8_t _id, uint8_t _val){
	if(knobBank == 0){
		switch(_id){
			case POT_0:
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
				// controlParts(PART_ATTACK, _val);
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
			case POT_1:
				controlParts(CHORUS_TYPE, _val);
				break;
			case POT_2:
				controlParts(CHORUS_RATE, _val);
				break;
			case POT_3:
				controlParts(CHORUS_FEEDBACK, _val);
				break;
			case POT_4:
				controlParts(PART_PORTAMENTO_TIME, _val);
				break;
			case POT_5:
				break;
			case POT_6:
				controlParts(PART_CHORUS_DEPTH, _val);
				break;
		}
	}
	else if(knobBank == 3){
		switch(_id){
			case POT_1:
				controlParts(REVERB_TYPE, _val);
				break;
			case POT_2:
				controlParts(REVERB_TIME, _val);
				break;
			case POT_3:
				controlParts(REVERB_FEEDBACK, _val);
				break;
			case POT_4:
				break;
			case POT_5:
				controlParts(PART_DECAY, _val);
				break;
			case POT_6:
				controlParts(PART_REVERB_DEPTH, _val);
				break;
		}
	}
	else if(knobBank == 4){
		switch(_id){
			case POT_0:
				// controlParts(PART_DRUM_PITCH, _val);
				break;
			case POT_1:
				controlParts(PART_DRUM_TVA, _val);
				break;
			case POT_2:
				controlParts(PART_DRUM_PITCH, _val);
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
	else if(knobBank == 5){
		view->printf("%03d%03d", _id, _val);
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
	// view->printf("%03d%03d", _id, _val);

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
	// view->printf("%03d%03d", low, high);

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
