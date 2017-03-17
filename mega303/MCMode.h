
#ifndef MCMode_h
#define MCMode_h

#include "Arduino.h"
#include "MCConstants.h"
#include "MCInput.h"
#include "MCPart.h"


// #include "MC"
// http://forum.arduino.cc/index.php?topic=65095.0
class MCMode {
	public:
		MCMode();
		virtual void begin(HardwareSerial * _serial);
		virtual void update(uint8_t _step);
		virtual void event(int _id, int _val);

		void setInput(MCInput * _input);
		void setParts(MCPart * _parts);
		void selectMode();
		void unSelectMode();
		void controlParts(int _id, int _val);
		MCInput * mcInput;
		MCPart * mcParts;
		int velocity;
		// locae states that should be in most modes
		byte partSelector;
		bool function;
		bool record;
		uint8_t octave;
		// debug
		HardwareSerial * serial;

	private:
		int currentStep;
		int localLEDState[16];
		uint8_t buttons[256]; // to then deal with buttons[PLAY_BUTTON] == 1;
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
		virtual void event(int _id, int _val);
		virtual void update(uint8_t _step);
};

class ModeTwo : public MCMode {
	public :
		ModeTwo();
		virtual void event(int _id, int _val);
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
		virtual void event(int _id, int _val);
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
