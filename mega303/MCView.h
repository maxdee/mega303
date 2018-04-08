#ifndef MCView_h
#define MCView_h
#include "MCInput.h"

class MCView : public Print {
    public:
        MCView();
        MCInput * mcInput;
        void begin(MCInput * _input);
        size_t write(uint8_t c);
        bool useSerial;
    private:

};

#endif
