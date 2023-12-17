#include <iostream>
#include "Wrapper.h"
#include "Subject.h"
#include "Engine.h"

using std::cout;
using std::endl;
using std::unordered_map;
using std::variant;
using std::string;

int main() {
	Subject ex;
	Wrapper wrapper(&ex, &Subject::f3, {{"arg1", 0}, {"arg2", 0}, {"arg3", 0}});
	Engine engine;

	engine.register_command(&wrapper, "command1");
	cout << engine.execute("command1", { {"arg1", 3}, {"arg3", 2}, {"arg2", 4} }) << endl;
	return 0;
}