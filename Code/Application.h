#ifndef APPLICATION_H
#define APPLICATION_H
#include "Base.h"
#include "Operation_handler.h"
#include "Output_device.h"

class Application : public Base {
	Base* root_parent = 0;
	Base* temp_child = 0;

public:
	Application(Base* parent = 0, int class_number = 1, int state_number = 1);
	void buildTree();
	void execute();
	int read_data();
	void start_emitting_signals();
	void signal_1(string& nothing) {};
	void signal_2(string& nothing) {};
	void signal_3(string& nothing) {};

};

#endif