#include "Arduino.h"
#include "MCPart.h"

MCPart::MCPart(){

}
void MCPart::begin(HardwareSerial * _serial, uint8_t _chan){
	channel = _chan;
	serial = _serial;
}

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
		controlChange(126, 00); // mono off
		controlChange(65, 00); // portamento off
	}
	else {
		controlChange(126, 01); // mono on
		controlChange(65, 127); // portamento on
	}
	controlChange(5, _val);
}
