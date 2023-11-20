#include "Command.h"

Command::Command(Variable* v, string commandText) : v(v), commandText(commandText)
{
	id = 0;
	nextId = 0;
	istringstream ss(commandText);
	string curr;
	// command is in format: COM_NAME OP1 OP2 .. 
	bool first = true;
	while (getline(ss, curr, ' '))
	{
		if (first) // skip the command name
		{
			first = false;
			continue;
		}
		operands.push_back(curr);

	}
}
void Command::setId(int x)
{
	id = x;
}
int Command::getNextId()
{
	return nextId;
}
void Command::setAllCommand(vector<Operation> commands)
{
	for (int i = 0; i < commands.size(); i++)
	{
		allCommands.push_back(commands[i]);
	}
}
Add::Add(Variable* v, string commandText) : Command(v, commandText)
{

}
Set::Set(Variable* v, string commandText) : Command(v, commandText)
{
}
void Set::execute()
{
	v->AddVariable(operands[0], v->getValue(operands[1]));
	nextId = id + 1;
}
Operation Set::getType()
{
	
	return SET;
}
void Add::execute()
{
	int n = v->getValue(operands[1]) + v->getValue(operands[2]);
	v->AddVariable(operands[0], n);
	nextId = id + 1;
}
Operation Add::getType()
{
	return ADD;
}
Sub::Sub(Variable* v, string commandText) : Command(v, commandText)
{
}
void Sub::execute()
{
	int n = v->getValue(operands[1]) - v->getValue(operands[2]);
	v->AddVariable(operands[0], n);
	nextId = id + 1;
}
Operation Sub::getType()
{
	return SUB;
}
Mul::Mul(Variable* v, string commandText) : Command(v, commandText)
{
}
void Mul::execute()
{
	int n = v->getValue(operands[1]) * v->getValue(operands[2]);
	v->AddVariable(operands[0], n);
	nextId = id + 1;
}
Operation Mul::getType()
{
	return MUL;
}
Div::Div(Variable* v, string commandText) : Command(v, commandText)
{
}
void Div::execute()
{
	int n = v->getValue(operands[1]) / v->getValue(operands[2]);
	v->AddVariable(operands[0], n);
	nextId = id + 1;
}

Operation Div::getType()
{
	return DIV;
}

Goto::Goto(Variable* v, string commandText ): Command(v, commandText)
{
}

void Goto::execute()
{
	nextId = id + stoi(operands[0]);
}

Operation Goto::getType()
{
	return GOTO;
}

Ifgr::Ifgr(Variable* v, string commandText) : Command(v, commandText)
{
}

void Ifgr::execute()
{
	if (v->getValue(operands[0]) > v->getValue(operands[1]))
	{
		nextId = id + 1;
		return;
	}

	int stackPointer = 0;
	for (int i = id; i < allCommands[i]; i++)
	{
		if (allCommands[i] == IFGR || allCommands[i] == IFEQ) stackPointer++;
		else if (allCommands[i] == ENDIF && stackPointer > 0) stackPointer--;
		else if (allCommands[i] == ELSE && stackPointer == 0)
		{
			nextId = i + 1;
			return;
		}
	}
}

Operation Ifgr::getType()
{
	return IFGR;
}

Ifeq::Ifeq(Variable* v, string commandText) : Command(v, commandText)
{
}

void Ifeq::execute()
{	
	if (v->getValue(operands[0]) == v->getValue(operands[1]))
	{
		nextId = id + 1;
		return;
	}

	int stackPointer = 0;
	for (int i = id; i < allCommands[i]; i++)
	{
		if (allCommands[i] == IFGR || allCommands[i] == IFEQ) stackPointer++;
		else if (allCommands[i] == ENDIF && stackPointer > 0) stackPointer--;
		else if (allCommands[i] == ELSE && stackPointer == 0)
		{
			nextId = i + 1;
			return;
		}
	}
}

Operation Ifeq::getType()
{
	return IFEQ;
}

Else::Else(Variable* v, string commandText) : Command(v, commandText)
{
}

void Else::execute()
{
	int stackPointer = 0;
	for (int i = id; i < allCommands.size(); i++) 
	{
		if (allCommands[i] == IFGR || allCommands[i] == IFEQ) stackPointer++;
		else if (allCommands[i] == ENDIF && stackPointer > 0) stackPointer--;
		else if (allCommands[i] == ENDIF)
		{
			nextId = i;
			return;
		}
	}
}
Operation Else::getType()
{
	return ELSE;
}

Endif::Endif(Variable* v, string commandText) : Command(v, commandText)
{
}

void Endif::execute()
{
	nextId = id + 1;
}

Operation Endif::getType()
{
	return ENDIF;
}

Loop::Loop(Variable* v, string commandText) : Command(v, commandText)
{
	if (!operands.size()) operand = 0;
	else operand = stoi(operands[0]);
	
	
}

void Loop::execute()
{
	int endLoopId;//dobicu iz steka posle
	vector<Operation> loopsAndEndloops;
	vector<int> loopId;
	stack<Operation> stack;
	for (int i = id; i <allCommands.size(); i++)
	{
		if (allCommands[i] == LOOP || allCommands[i]== ENDLOOP) 
		{
			loopsAndEndloops.push_back(allCommands[i]);
			loopId.push_back(i);
		}
	}
	int i = 0;
	while (!stack.empty())
	{
		if (loopsAndEndloops[i]==LOOP)
		{
			stack.push(LOOP);
		}
		else
		{
			stack.pop();
		}
		endLoopId = loopId[i];
		i++;
	}
	if (operands.empty()) nextId = id + 1;
	else if(operand>0)
	{
		operand--;
		nextId = id + 1;

	}
	else {
		nextId = endLoopId + 1;
	}
}

Operation Loop::getType()
{
	return LOOP;
}

Endloop::Endloop(Variable* v, string commandText) : Command(v, commandText)
{
}

void Endloop::execute()
{
	int loopId;//dobicu iz steka posle
	vector<Operation> loopsAndEndloops;
	vector<int> endLoopId;
	stack<Operation> stack;
	for (int i = id; i > 0; i--)
	{
		if (allCommands[i] == LOOP || allCommands[i] == ENDLOOP)
		{
			loopsAndEndloops.push_back(allCommands[i]);
			endLoopId.push_back(i);
		}
	}
	int i = 0;
	while (!stack.empty())
	{
		if (loopsAndEndloops[i] == ENDLOOP)
		{
			stack.push(ENDLOOP);
		}
		else
		{
			stack.pop();
		}
		loopId = endLoopId[i];
		i++;
	}
	nextId = loopId;
}

Operation Endloop::getType()
{
	return ENDLOOP;
}
