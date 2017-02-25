
#ifndef MCPart_h
#define MCPart_h

#include "Arduino.h"

class MCPart {
	public:
		MCPart();
		uint8_t channel;
		HardwareSerial * serial;
	public:
		void begin(HardwareSerial * _serial, uint8_t _chan);
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



	private:
};






#endif
