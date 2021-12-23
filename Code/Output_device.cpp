#include "Output_device.h"

Output_device::Output_device(Base* parent, string name, int class_number, int state_number) : Base(parent, name, class_number, state_number) {}

void Output_device::handler_4(string temp_result) {
	if (line_break) {
		cout << endl;
	}
	cout << temp_result;
	line_break = true;
};