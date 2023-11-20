#pragma once
#include "Command.h"
#include "Variable.h"
#include <sstream>

class Machine {
public:
	Machine();
	void loadProgram(const string& filepath);
	void execute(const string& filepath);
private:
	string getCommandName(string curr);
	Variable* v;
	vector < Command*> commands;
};