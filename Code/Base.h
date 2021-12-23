#pragma once
#ifndef BASE_H
#define BASE_H
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <tuple>
#define SIGNAL_D(  signal_f  ) ( ( void ( Base::* ) ( string & ) ) ( ( signal_f  ) ) )
#define HANDLER_D( handler_f ) ( ( void ( Base::* ) ( string ) ) ( ( handler_f ) ) )
using namespace std;
class Base;
typedef void (Base::* ptr_s)(string&);
typedef void (Base::* ptr_h)(string);

class Base {
	static int i;
	string name;
	Base* parent;
	int state_number;
	string path; 
	vector<Base*> children;
	vector<Base*>::iterator children_iterator;

	struct o_sh {
		ptr_s p_signal;
		Base* p_Base;
		ptr_h p_handler;
	};
	vector<o_sh*> connections; 
	vector<o_sh*>::iterator connections_iterator;

public:
	static Base* root;
	int class_number;
	Base(Base*, string, int class_number, int state_number);
	string getPath();
	string getName();
	Base* getParent();
	Base* search_by_name(string);
	Base* search_by_path(string);
	void OutputTree();

	void show_all_connections();
	void set_connection(ptr_s, Base* p_ob_handler, ptr_h);
	void delete_connection(ptr_s, Base* p_ob_handler, ptr_h);
	void emit_signal(ptr_s, string& s_command);

protected:
	string tabulation(int);
	void setName(string);
	void setPath();
	void setParent(Base*);
	Base* search(string);
	void read_base_data();
	string segmentation(string&);
};

#endif