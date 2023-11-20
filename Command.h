#pragma once
#include "Variable.h"
#include <stack>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
enum Operation { SET, ADD, MUL, DIV, SUB, GOTO, IFGR, IFEQ, ELSE, ENDIF, LOOP, ENDLOOP };
class Command {

public:
	Command(Variable* v, string commandText);
	virtual void execute() = 0;
	virtual Operation getType() = 0;
	void setId(int x);
	int getNextId();
	void setAllCommand(vector<Operation> commands);

protected:
	Variable* v;
	string commandText;
	vector<string> operands;
	int id; //index trenutne komande
	int nextId; //index komande koja se sledeca izvrsava
	vector<Operation> allCommands;
	
};
class Set : public Command
{
public:
	Set(Variable* v, string commandText);
	void execute();
	Operation getType();



private:

};
class Add : public Command
{
public:
	Add(Variable* v, string commandText);
	void execute();
	Operation getType();
private:

};
class Sub : public Command
{
public:
	Sub(Variable* v, string commandText);
	void execute();
	Operation getType();
private:


};
class Mul : public Command
{
public:
	Mul(Variable* v, string commandText);
	void execute();
	Operation getType();
private:

};
class Div : public Command
{
public:
	Div(Variable* v, string commandText);
	void execute();
	Operation getType();
private:


};
class Goto : public Command
{
public:
	Goto(Variable* v, string commandText);
	void execute();
	Operation getType();
private:


};
class Ifgr : public Command
{
public:
	Ifgr(Variable* v, string commandText);
	void execute();
	Operation getType();
private:


};
class Ifeq : public Command
{
public:
	Ifeq(Variable* v, string commandText);
	void execute();
	Operation getType();
private:

};
class Else : public Command
{
public:
	Else(Variable* v, string commandText);
	void execute();
	Operation getType();
	
private:
	
};
class Endif : public Command
{
public:
	Endif(Variable* v, string commandText);
	void execute();
	Operation getType();
private:



};
class Loop : public Command
{
public:
	Loop(Variable* v, string commandText);
	void execute();
	Operation getType();
private:
	int operand;

};
class Endloop : public Command
{
public:
	Endloop(Variable* v, string commandText);
	void execute();
	Operation getType();
private:


};
