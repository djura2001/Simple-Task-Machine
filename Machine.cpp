#include "Machine.h"
#include <fstream>
Machine::Machine()
{
	v = new Variable();
}

void Machine::loadProgram(const string& filepath)
{

	ifstream input(filepath);
	string curr;

	while (getline(input, curr)) 
	{
		string commandName = getCommandName(curr);

		//posto switch ne radi sa stringovima, koristimo if-ove
		
		if(commandName == "SET")
		{
			Set* command = new Set(v, curr);
			commands.push_back(command);
		}
		else if (commandName == "ADD")
		{
			Add* command = new Add(v, curr);
			commands.push_back(command);
		}
		else if (commandName == "SUB")
		{
			Sub* command = new Sub(v, curr);
			commands.push_back(command);
		}
		else if (commandName == "MUL")
		{
			Mul* command = new Mul(v, curr);
			commands.push_back(command);

		}
		else if (commandName == "DIV")
		{
			Div* command = new Div(v, curr);
			commands.push_back(command);
		}
		else if (commandName == "GOTO")
		{
			Goto* command = new Goto(v, curr);
			commands.push_back(command);
		}
		else if (commandName == "IFGR")
		{
			Ifgr* command = new Ifgr(v, curr);
			commands.push_back(command);
		}
		else if (commandName == "IFEQ")
		{
			Ifeq* command = new Ifeq(v, curr);
			commands.push_back(command);
		}
		else if (commandName == "ELSE")
		{
			Else* command = new Else(v, curr);
			commands.push_back(command);
		}
		else if (commandName == "ENDIF")
		{
			Endif* command = new Endif(v, curr);
			commands.push_back(command);
		}
		else if (commandName == "LOOP")
		{
			Loop* command = new Loop(v, curr);
			commands.push_back(command);
		}
		else if (commandName == "ENDLOOP")
		{
			Endloop* command = new Endloop(v, curr);
			commands.push_back(command);
		}
		
		
	}
	vector<Operation> commandOrder;
	for (int i = 0; i < commands.size(); i++)
	{
		commandOrder.push_back(commands[i]->getType());
	}
	for (int i = 0; i < commands.size(); i++)
	{
		commands[i]->setAllCommand(commandOrder);
		commands[i]->setId(i);
	}
	

}

void Machine::execute(const string& filepath)
{
	int i = 0;
	while (i < commands.size())
	{
		commands[i]->execute();
		i = commands[i]->getNextId();
	}
	v->Print(filepath);
}

string Machine::getCommandName(string curr)
{
	istringstream ss(curr);
	getline(ss, curr, ' ');
	return curr;
}
