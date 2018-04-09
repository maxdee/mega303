
#ifndef MCMode_h
#define MCMode_h

#include "Arduino.h"
#include "MCConstants.h"
#include "MCInput.h"
#include "MCPart.h"
#include "MCView.h"



// #include "MC"
// http://forum.arduino.cc/index.php?topic=65095.0
class MCMode {
	public:
		MCMode();
		setParts(MCPart * _part, uint8_t _index);
		MCPart * mcParts[PART_COUNT];

		virtual void begin(MCView * _view);
		virtual void update(uint8_t _step);
		virtual void event(uint8_t _id, uint8_t _val);
		virtual uint8_t getKey(uint8_t _key);
		void setInput(MCInput * _input);
		void setParts(MCPart * _parts);
		void selectMode();
		void unSelectMode();
		void controlParts(uint8_t _id, uint8_t _val);
		void updateStepLEDs();
		void keyEvent(uint8_t _key);
		void knobBanks(uint8_t _id, uint8_t _val);


		void incrementPatch(int _v);
		void drumSequenceEdit(uint8_t _id, uint8_t _val);
		void sequenceEdit(uint8_t _id, uint8_t _val);


		MCInput * mcInput;

		uint8_t selectedParts;
		// locale states that should be in most modes
		bool functionToggle;
		bool recordToggle;
		bool partMuteToggle;
		bool partSelectToggle;
		bool rhythmMuteToggle;

		static uint8_t octave;
		static uint8_t selectRadio;
		// debug
		MCView * view;

		uint8_t currentStep;
		uint8_t knobBank;
		uint8_t selectedKey;

	private:
		uint8_t localLEDState[16];
		// uint8_t buttons[256]; // to then deal with buttons[PLAY_BUTTON] == 1;
		// state could be initialized as
		// 0 for unused
		// 1 for pushbutton, would be 2 if pressed
		// or 3 / 4 for toggle on off
		// or b10011011 ?
		// state change would be reflected in leds

		// event -> process _id, return if unused
		// then do action in a switch case?

};


class ModeOne : public MCMode {
	public :
		ModeOne();
		virtual void event(uint8_t _id, uint8_t _val);
		virtual void update(uint8_t _step);
		virtual void knobBanks(uint8_t _id, uint8_t _val);
};

class ModeTwo : public MCMode {
	public :
		ModeTwo();
		virtual void event(uint8_t _id, uint8_t _val);
		virtual void update(uint8_t _step);
};

class ModeThree : public MCMode {
	private:

	public :
		uint8_t low;
		uint8_t high;
		uint8_t div;
		uint8_t note;
		uint16_t cnt;

		ModeThree();
		virtual void event(uint8_t _id, uint8_t _val);
		virtual void update(uint8_t _step);
};


// class DrumMode : public MCMode {
// 	private:
//
// 	public :
// 		uint8_t note;
// 		uint8_t step;
//
// 		DrumMode();
// 		virtual void event(int _id, int _val);
// 		virtual void update(uint8_t _step);
// };
#endif
