#ifndef OPERATION_HANDLER_H
#define OPERATION_HANDLER_H
#include "Base.h"

class Operation_handler : public Base {
	char operation_symbol;
	string first_operand;
	string second_operand;
	string temp_result;
public:
	Operation_handler(Base*, string, int, int);
	void handler_1(string);
	void handler_2(string);
	void handler_3(string);
	void signal_4(string&);
};
#endif