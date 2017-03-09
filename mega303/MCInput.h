
#ifndef MCInput_h
#define MCInput_h

#include "Arduino.h"
#include "Font.h"
#include "MCConstants.h"
// #include "MC"
// http://forum.arduino.cc/index.php?topic=65095.0
class MCInput {
	public:
		MCInput();
		void update();
		void setLED(uint8_t _index, uint8_t _state);
		bool checkButton(uint8_t _row, uint8_t _col);

		void frequentCheck();
		void displayString(char _str[]);
		void displayBytes(byte _bytes[]);
		// states?
		void setEventCallback(void (*_eventCallback)(int, int));

	private:
		void (*eventCallback)(int,int);


	public: // accesubke members
		uint8_t potValues[8];

	private:
		uint16_t updateCount;
		int tmp;
	// pins and such
	private:
		int columnRowToIndex(uint8_t _row, uint8_t _col);
		void setRow(int _row);
		typedef struct {
		    uint8_t pinA;
		    uint8_t pinB;
		    uint8_t prev;
			uint8_t tmp;
		    int val;
		} Encoder;
		// Pins
		#define dirPin 23
		#define tapButton 45
		Encoder encoder = {41, 43};
		#define beatLEDRed 14
		#define beatLEDGreen 15
		#define xrst 20
		#define footSwitch 21

		#define ROW_COUNT 16
		#define COL_COUNT 8


		uint8_t potPins[8] = {8, 9, 10, 11, 12, 13, 14, 15};
		uint8_t potBuffer[8][8];
		uint8_t previousPotVal[8];
		// pins for columns
		uint8_t columnPins[8] = {25, 27, 29, 31, 33, 35, 37, 39};
		// Pins for row multiplexer
		uint8_t rowMuxPins[4] = {47, 49, 51, 53};
		// row indexs for 7 segments
		uint8_t segmentRows[6] = {6, 3, 12, 13, 10, 15};

		// rows
		byte rowBytes[16] = {
			B00000000, // 000 aka 0
			B00000010, // 100 aka 1
			B00000100, // 010 aka 2
			B00000110, // 110 aka 3
			B00001000, // 001 aka 4
			B00001100, // 011 aka 6
			B00001110, // 111 aka 7
			// same but for second mux chip
			B00000001,
			B00000011,
			B00000101,
			B00000111,
			B00001001,
			B00001010,
			B00001011,
			B00001101,
			B00001111,
		};
		// next circuit version will use port manipulation...

		// LED column states
		byte LEDStates[16];
		byte buttonBuffer[16];
		byte buttonStates[16];
};

#endif
