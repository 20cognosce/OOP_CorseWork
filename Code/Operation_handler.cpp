#include "Operation_handler.h"

Operation_handler::Operation_handler(Base* parent, string name, int class_number, int state_number) : Base(parent, name, class_number, state_number) {}

void Operation_handler::handler_1(string first_operand) {
	this->first_operand = first_operand;
	temp_result = first_operand;
};

void Operation_handler::handler_2(string symbol) {
	this->operation_symbol = symbol[0];
};

void Operation_handler::handler_3(string second_operand) {
	this->second_operand = second_operand;
	first_operand = temp_result;
	switch (operation_symbol) {
	case '+': temp_result = to_string(stoi(temp_result) + stoi(second_operand)); break; //+
	case '-': temp_result = to_string(stoi(temp_result) - stoi(second_operand)); break; //-
	case '*': temp_result = to_string(stoi(temp_result) * stoi(second_operand)); break; //*
	case '%': temp_result = to_string(stoi(temp_result) % stoi(second_operand)); break; //%
	}
	string output = first_operand + " " + operation_symbol + " " + second_operand + " = " + temp_result;
	emit_signal(SIGNAL_D(&Operation_handler::signal_4), output);
};

void Operation_handler::signal_4(string& output) {};
