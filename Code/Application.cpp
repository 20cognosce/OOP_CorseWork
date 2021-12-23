#include "Application.h"

using namespace std;

Application::Application(Base* parent, int class_number, int state_number) : Base(parent,"",class_number,state_number) {
}

void Application::buildTree() {
	setName("app");
	Base* obj_op_handler = new Operation_handler(this, "obj_op_handler", 2, 1);
	Base* obj_out = new Output_device(this, "obj_out", 3, 1);

	this->set_connection(SIGNAL_D(&Application::signal_1), obj_op_handler, HANDLER_D(&Operation_handler::handler_1));
	this->set_connection(SIGNAL_D(&Application::signal_2), obj_op_handler, HANDLER_D(&Operation_handler::handler_2));
	this->set_connection(SIGNAL_D(&Application::signal_3), obj_op_handler, HANDLER_D(&Operation_handler::handler_3));
	obj_op_handler->set_connection(SIGNAL_D(&Operation_handler::signal_4), obj_out, HANDLER_D(&Output_device::handler_4));
};


int Application::read_data() {
	if (this->getName() != "endtree") {
		cout << endl << "Test result" << endl;
		cout << "The object " << this->getName() << " is ready";
		this->read_base_data();
	}
	return 0;
}

void Application::start_emitting_signals() {
	cout << endl << "Emit signals";
	while (true) {
		string object_signal_name;
		string text;
		cin >> object_signal_name;
		if (object_signal_name == "endsignals") {
			break;
		}
		cin >> text;
		Base* signal = root->search_by_name(object_signal_name);
		ptr_s ptr_this_s = 0;

		/*switch (signal->class_number) {
		case 1:	ptr_this_s = SIGNAL_D(&Derived::send_signal); break;
		case 2: ptr_this_s = SIGNAL_D(&Derived2::send_signal); break;
		case 3: ptr_this_s = SIGNAL_D(&Derived3::send_signal); break;
		}*/
		signal->emit_signal(ptr_this_s, text);
	};
}

void Application::execute() {
	string number1, number2, symbol;
	string expression;
	getline(cin, expression);
	number1 = segmentation(expression); //определение первого операнда
	emit_signal(SIGNAL_D(&Application::signal_1), number1); //send_signal-1

	while (expression != "") {
		symbol = segmentation(expression); //определение очередной операции
		emit_signal(SIGNAL_D(&Application::signal_2), symbol); //send_signal-2
		number2 = segmentation(expression); //определение очередного операнда
		emit_signal(SIGNAL_D(&Application::signal_3), number2); //send_signal-3
	}
};
