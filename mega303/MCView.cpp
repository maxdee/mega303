#include "MCView.h"

MCView::MCView(){
    useSerial = true;
}

void MCView::begin(MCInput * _input){
    mcInput = _input;
}

size_t MCView::write(uint8_t _c){
    mcInput->pushDigit(_c);
    if(useSerial) Serial.write(_c);
}
