#include "Base.h"

int Base::i;
Base* Base::root;

Base::Base(Base* parent, string name, int class_number, int state_number) {
	i = 0;
	setParent(parent);
	setName(name);
	setPath();
	this->class_number = class_number;
	this->state_number = state_number;

}

void Base::setName(string name) {
	this->name = name;
}

string Base::getName() {
	return this->name;
}

void Base::setPath() {
	if (parent) {
		this->path += parent->getPath();
	}
	if (name != "") {
		this->path += "/" + this->name;
	}
}

string Base::getPath() {
	return this->path;
}

void Base::setParent(Base* parent) {
	this->parent = parent;
	if (parent) {
		parent->children.push_back(this);
	}
}

void Base::OutputTree() {
	if (!i) { //условие при котором "шапка" выводится только один раз
		cout << "Object tree";
		cout << endl << name;
	}
	if (children.empty()) {
		return;
	}
	children_iterator = children.begin();
	while (children_iterator != children.end()) {
		tabulation(1);
		cout << endl << tabulation(0);
		cout << (*children_iterator)->getName();
		(*children_iterator)->OutputTree();
		tabulation(-1);
		children_iterator++;
	}
}

string Base::tabulation(int a) {
	string this_tabulation = "";
	string tab = "    ";
	if (a == 1) {
		++i;
	}
	if (a == -1) {
		--i;
	}
	for (int j = 0; j < i; j++) {
		this_tabulation.append(tab);
	}
	return this_tabulation;
}

Base* Base::getParent() {
	return parent;
};

void Base::read_base_data() {
	children_iterator = children.begin();
	while (children_iterator != children.end()) {
		cout << endl;
		cout << "The object " << (*children_iterator)->getName();
		if ((*children_iterator)->state_number > 0) {
			cout << " is ready";
		}
		else { cout << " is not ready"; }
		(*children_iterator)->read_base_data();
		children_iterator++;
	}
}

string Base::segmentation(string& s) {
	if (s == "") {
		return "";
	}
	string result;
	int difference = 1; //to substract together with space
	const string& start_delimiter = ""; //there has been "/"
	const string& stop_delimiter = " "; //there has been "/"
	unsigned first_delimiter_pos = s.find(start_delimiter); //there has been + 1
	unsigned last_delimiter_pos = s.find_first_of(stop_delimiter, first_delimiter_pos);
	if (last_delimiter_pos == pow(2, 32) - 1) {
		last_delimiter_pos = s.find_last_of(s.back()) + 1;
		difference = 0;
	}
	result = s.substr(first_delimiter_pos, last_delimiter_pos - first_delimiter_pos);
	s = s.substr(last_delimiter_pos + difference);
	return (result);
};

Base* Base::search(string path) {
	if (path.substr(0, 2) == "//") { //если адрес передан через //, то ищем по имени
		string temp = path;
		segmentation(temp); //убираем первый слэш 
		return search_by_name(segmentation(temp)); //убираем второй и вызываем поиск по имени
	};
	string local = segmentation(path); //достаем имя верхней директории
	if (local == this->getName() && path == "") {
		return this;
	}
	if (local == this->getName()) {
		local = segmentation(path);
	}
	children_iterator = children.begin();
	while (children_iterator != children.end()) {
		if (local == (*children_iterator)->getName()) {
			if (path == "") {
				return *children_iterator;
			}
			else {
				return (*children_iterator)->search(path);
			}
		}
		children_iterator++;
	}
	return NULL;
}

Base* Base::search_by_name(string name) {
	if (name == this->getName()) return this;
	children_iterator = children.begin();
	while (children_iterator != children.end()) {
		if (name == (*children_iterator)->getName()) {
			return (*children_iterator);
		}
		if ((*children_iterator)->search_by_name(name) != NULL) {
			return (*children_iterator)->search_by_name(name);
		}
		children_iterator++;
	}
	return NULL;
}

Base* Base::search_by_path(string path) {
	if (search(path)) {
		string temp = "";
		temp = search(path)->getPath() + " " + "Object name: " + search(path)->getName();
		cout << endl << temp;
		return search(path);
	}
	else {
		string temp = "";
		temp = path + " " + "Object not found";
		cout << endl << temp;
		return NULL;
	}
}

void Base::set_connection(ptr_s p_signal, Base* p_ob_handler, ptr_h p_handler) {
	o_sh* new_struct = new o_sh;
	if (connections.size() > 0) {
		connections_iterator = connections.begin();

		while (connections_iterator != connections.end()) {
			if ((*connections_iterator)->p_signal == p_signal && (*connections_iterator)->p_Base == p_ob_handler && (*connections_iterator)->p_handler == p_handler) {
				return;
			}
			connections_iterator++;
		}
	}
	new_struct->p_signal = p_signal;
	new_struct->p_Base = p_ob_handler;
	new_struct->p_handler = p_handler;
	connections.push_back(new_struct);
};

void Base::delete_connection(ptr_s p_signal, Base* p_ob_handler, ptr_h p_handler) {
	if (connections.empty()) return;

	connections_iterator = connections.begin();
	while (connections_iterator != connections.end()) {
		if ((*connections_iterator)->p_signal == p_signal && ((*connections_iterator))->p_Base == p_ob_handler 
			&& ((*connections_iterator))->p_handler == p_handler) {
			connections.erase(connections_iterator);
			break;
		}
		connections_iterator++;
	}
};

void Base::emit_signal(ptr_s s_ignal, string& s_command) {
	if (connections.empty()) return;
	(this->*s_ignal) (s_command); //посылаем строковый сигнал на преобразование
	connections_iterator = connections.begin();

	while (connections_iterator != connections.end()) {
		if ((*connections_iterator)->p_signal == s_ignal) {
			ptr_h p_handler = (*connections_iterator)->p_handler; //метод обработчика
			Base* ob_handler = (*connections_iterator)->p_Base; //указатель на объект-обработчик
			(ob_handler->*p_handler)(s_command); //вызов метода обработчика с параметром в виде уже преобразованного сигнала
		}
		connections_iterator++;
	}
};
