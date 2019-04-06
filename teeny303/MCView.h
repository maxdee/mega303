#ifndef MCView_h
#define MCView_h
#include "Font.h"
#include "Shared.h"


class MCView : public Print {
    public:
        MCView();
        size_t write(uint8_t c);
        bool useSerial;

        #define ROW_COUNT 16
		#define COL_COUNT 8
        uint8_t LEDStates[16];
        uint8_t LEDOutput[16];
        void setLED(uint8_t _index, uint8_t _state);
		void setStepLEDs(uint16_t _v);
		void setPartSelectLEDs(uint8_t);
        bool ledUpdate;

        void displayString(uint8_t * _str);
        void displayBytes(uint8_t * _bytes);
        void pushDigit(uint8_t _c);

        bool doLEDupdate(uint8_t _step);
    private:

};

#endif
