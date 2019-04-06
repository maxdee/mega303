
#ifndef MCPart_h
#define MCPart_h

#include "Arduino.h"
#include "MCView.h"
#include "SynthMap.h"
#include "LEDMap.h"

///////////////////////////////////////////////////////////////////////////////
// Parameters
///////////////////////////////////////////////////////////////////////////////
enum PartStuff{
 PART_NOTE_OFF,
 PART_NOTE_ON,
 PART_CONTROL_CHANGE,
 PART_PROGRAM_CHANGE,
 PART_PATCH,
 PART_KIT,
 PART_COARSE_TUNE,
 PART_FINE_TUNE,
 PART_CUTOFF,
 PART_RESONANCE,
 PART_PORTAMENTO_TIME,
 PART_VIBRATO_RATE,
 PART_VIBRATO_DEPTH,
 PART_VIBRATO_DELAY,
 PART_ATTACK,
 PART_DECAY,
 PART_RELEASE,
 PART_DRUM_PITCH,
 PART_DRUM_TVA,
 PART_DRUM_PAN,
 PART_DRUM_REVERB,
 PART_DRUM_CHORUS,
 PART_PAN,
 PART_VOLUME,
 PART_MODULATION,
 PART_EXPRESSION,
 PART_SUSTAIN,
 PART_REVERB_DEPTH,
 PART_CHORUS_DEPTH,
 PART_MUTE,

 REVERB_TYPE,
 REVERB_TIME,
 REVERB_FEEDBACK,
 CHORUS_TYPE,
 CHORUS_RATE,
 CHORUS_FEEDBACK,
 PART_ADD_NOTE,
 PART_CLEAR_STEP,
 PART_CLEAR_ALL
};



// something like this?
// typedef struct {
// 	int steps[16]; // notes 1-127
// 	int changed; // changes if any step modified
// } sixteenStep;

// const uint8_t PROGRAM_BANKS[] = {20, 15, 20, 20, 9, 8, 20, 13, 13, 12, 11, 12, 17, 16, 13, 10, 20, 11, 19, 12, 11, 14};


///////////////////////////////////////////////////////////////////////////////
// Notes
///////////////////////////////////////////////////////////////////////////////
/**
 * MCInput produces events with a ID and a value
 * MCMode takes these ID and produces and parameter change for parts.
 * ID 127 to 142 step buttons
 * ID 143 to 149 pots
 *
 */

#define STEP_COUNT 16
#define SLOT_COUNT 8
#define PART_COUNT 8

class MCPart {
	public:
		MCPart();
		uint8_t channel;
		uint8_t previous;
		HardwareSerial * serial;
		MCView * view;
		bool mute;

	public:
		virtual void begin(HardwareSerial * _serial, MCView * _view, uint8_t _chan);

		virtual void event(uint8_t _id, uint8_t _val);
		// midi events
		void noteOn(uint8_t _pitch, uint8_t _vel);
		void noteOff(uint8_t _pitch, uint8_t _vel);
		void controlChange(uint8_t _cc, uint8_t _val);
		void programChange(uint8_t _val);
		void midiSysEx(const uint8_t * _addr, uint8_t value);
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
		// uint16_t stepLEDs;
		uint8_t currentStep;
		uint8_t velocity;
		uint32_t patterns[127];

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

			void selectPitch(uint8_t _pitch);


			void drumPitch(uint8_t _note, uint8_t _val);
			void drumTVA(uint8_t _note, uint8_t _val);
			void drumPan(uint8_t _note, uint8_t _val);
			void drumReverb(uint8_t _note, uint8_t _val);
			void drumChorus(uint8_t _note, uint8_t _val);
};




#endif
