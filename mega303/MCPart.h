
#ifndef MCPart_h
#define MCPart_h

#include "Arduino.h"
#include "MCConstants.h"
#include "MCView.h"



class MCPart {
	public:
		MCPart();
		uint8_t channel;
		uint8_t previous;
		HardwareSerial * serial;
		MCView * view;

	public:
		virtual void begin(HardwareSerial * _serial, MCView * _view, uint8_t _chan);

		virtual void event(uint8_t _id, uint8_t _val);
		// midi events
		void noteOn(uint8_t _pitch, uint8_t _vel);
		void noteOff(uint8_t _pitch, uint8_t _vel);
		void controlChange(uint8_t _cc, uint8_t _val);
		void programChange(uint8_t _val);
		void midiSysEx(uint8_t * _addr, uint8_t value);
		byte GetRolandChecksum(byte * data, int length);

		// void setPatch(uint8_t _bank, uint8_t _pc);
		virtual void setPatch(uint16_t _index);
		virtual void incrementPatch(int8_t _i);

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

		void pan(uint8_t _val);
		void volume(uint8_t _val);
		void modulation(uint8_t _val);
		void expression(uint8_t _val);
		void sustain(uint8_t _val);
		void reverbDepth(uint8_t _val);
		void chorusDepth(uint8_t _val);

		// void reverbType(uint8_t _val);
		// void chorusType(uint8_t _val);
		uint16_t patchIndex;



		uint8_t selectedPitch;

		// steps
		uint16_t stepLEDs;
		uint8_t currentStep;
		uint8_t velocity;
		//
		// void clearStep(int _step);
		// void clearAll();
		// void addNote(int _step, uint8_t _pitch, uint8_t _vel);

		virtual void step(int _step);
		virtual void debug();
	private:
};


///////////////////////////////////////////////////////////////////////////////
// SynthPart
///////////////////////////////////////////////////////////////////////////////

class SynthPart : public MCPart {
	public :
		SynthPart();
		virtual void begin(HardwareSerial * _serial, MCView * _view, uint8_t _chan);
		virtual void step(int _step);
		// uint8_t steps[STEP_COUNT][SLOT_COUNT];
		// uint8_t currentSlot;

		virtual void event(uint8_t _id, uint8_t _val);
		virtual void setPatch(uint16_t _index);
		virtual void incrementPatch(int8_t _i);
		virtual void debug();

		uint8_t steps[STEP_COUNT][SLOT_COUNT];
		uint8_t currentSlot;
};

///////////////////////////////////////////////////////////////////////////////
// DrumPart
///////////////////////////////////////////////////////////////////////////////

class DrumPart : public MCPart {
		public :
			DrumPart();
			virtual void step(int _step);
			virtual void event(uint8_t _id, uint8_t _val);
			virtual void setPatch(uint16_t _index);
			virtual void incrementPatch(int8_t _i);
			virtual void debug();

			uint32_t patterns[127];

			void selectPitch(uint8_t _pitch);


			void drumPitch(uint8_t _note, uint8_t _val);
			void drumTVA(uint8_t _note, uint8_t _val);
			void drumPan(uint8_t _note, uint8_t _val);
			void drumReverb(uint8_t _note, uint8_t _val);
			void drumChorus(uint8_t _note, uint8_t _val);
};




#endif
