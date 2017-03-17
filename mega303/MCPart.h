
#ifndef MCPart_h
#define MCPart_h

#include "Arduino.h"
#include "MCConstants.h"


class MCPart {
	public:
		MCPart();
		uint8_t channel;
		HardwareSerial * serial;
	public:
		void begin(HardwareSerial * _serial, uint8_t _chan);

		void event(uint8_t _id, uint8_t _val);
		// midi events
		void noteOn(uint8_t _pitch, uint8_t _vel);
		void noteOff(uint8_t _pitch, uint8_t _vel);
		void controlChange(uint8_t _cc, uint8_t _val);
		void programChange(uint8_t _val);

		void setPatch(uint8_t _bank, uint8_t _pc);
		void setKit(uint8_t _pc);

		void coarseTune(uint8_t _val);
		void fineTune(uint8_t _val);
		void cutoff(uint8_t _val);
		void resonance(uint8_t _val);
		void portamentoTime(uint8_t _val);

		void vibratoRate(uint8_t _val);
		void vibratoDepth(uint8_t _val);
		void vibratoDelay(uint8_t _val);

		void attackTime(uint8_t _val);
		void decayTime(uint8_t _val);
		void releaseTime(uint8_t _val);

		void drumPitch(uint8_t _note, uint8_t _val);
		void drumTVA(uint8_t _note, uint8_t _val);
		void drumPan(uint8_t _note, uint8_t _val);
		void drumReverb(uint8_t _note, uint8_t _val);
		void drumChorus(uint8_t _note, uint8_t _val);

		void pan(uint8_t _val);
		void volume(uint8_t _val);
		void modulation(uint8_t _val);
		void expression(uint8_t _val);
		void sustain(uint8_t _val);


		// steps
		uint8_t steps[STEP_COUNT][SLOT_COUNT];
		int currentStep;
		int currentSlot;
		//
		void clearStep(int _step);
		void clearAll();
		void addNote(int _step, uint8_t _pitch, uint8_t _vel);

		void step(int _step);
	private:
};






#endif
