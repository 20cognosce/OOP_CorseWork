#ifndef OUTPUT_DEVICE_H
#define OUTPUT_DEVICE_H
#include "Base.h"

class Output_device : public Base {
	bool line_break = false;
public:
	Output_device(Base*, string, int, int);
	void handler_4(string);
};

#endif