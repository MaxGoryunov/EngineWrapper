#include <iostream>
#include "Wrapper.h"
#include "Subject.h"
#include "Engine.h"

using std::cout;
using std::endl;
using std::cerr;
using std::unordered_map;
using std::string;

int main() {
	Subject ex;
	Wrapper wrapper(&ex, &Subject::f3, {{"arg1", 0}, {"arg2", 0}, {"arg3", 0}});
	Engine engine;

	engine.register_command(&wrapper, "command1");
	cout << "Expecting 2: ";
	cout << engine.execute("command1", { {"arg1", 3}, {"arg2", 2}, {"arg3", 4} }) << endl;

	cout << "Expecting 10: ";
	cout << engine.execute("command1", { {"arg1", 3}, {"arg3", 2}, {"arg2", 4} }) << endl;

	cout << "Expecting 5: ";
	cout << engine.execute("command1", { {"arg3", 3}, {"arg2", 2}, {"arg1", 4} }) << endl;

	cout << "Expecting exception: ";
	try {
		engine.execute("command1", { {"arg1", 2}, {"arg3", 3} });
	}
	catch (std::runtime_error& e) {
		cerr << e.what() << endl;
	}

	cout << "Expecting exception: ";
	try {
		engine.execute("command1", { {"arg1", 2}, {"arg2", 3}, {"arg4", 10} });
	}
	catch (std::runtime_error& e) {
		cerr << e.what() << endl;
	}

	cout << "Expecting exception: ";
	try {
		engine.execute("command2", { {"arg1", 2}, {"arg2", 3}, {"arg3", 10} });
	}
	catch (std::runtime_error& e) {
		cerr << e.what() << endl;
	}

	Wrapper wrapper2(&ex, &Subject::f4, { {"argument1", 0}, {"arg2", 0} });
	engine.register_command(&wrapper2, "comm2");

	cout << "Expecting 6: ";
	cout << engine.execute("comm2", { {"arg2", 10}, {"argument1", 4} }) << endl;
	return 0;
}