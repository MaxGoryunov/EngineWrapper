#include <iostream>
#include "Wrapper.h"
#include "MathExample.h"

using std::cout;
using std::endl;
using std::unordered_map;
using std::variant;
using std::string;

int main() {
	MathExample ex;
	Wrapper wrapper(&ex, &MathExample::f3, {{"arg1", 0}, {"arg2", 0}, {"arg3",0 } });
	cout << wrapper.execute({ {"arg1", 3}, {"arg3", 2}, {"arg2", 4} }) << endl;
	return 0;
}