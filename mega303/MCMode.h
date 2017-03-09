
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
		virtual void update();
		virtual void event(int _id, int _val);

		void setInput(MCInput * _input);
		void setParts(MCPart * _parts);

		void controlParts(MCPart * _part, int _param, int _val);
		MCInput * mcInput;
		MCPart * mcParts;

		int velocity;
	private:
};


class ModeTwo : public MCMode {
	public :
		ModeTwo();
		virtual void event(int _id, int _val);
		virtual void update();
};
#endif
