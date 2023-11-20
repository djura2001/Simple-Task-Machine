#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
class Variable {
public:
	
	void AddVariable(string s,int v);
	int getValue(string s);
	void Sort();
	void Print(string foutput);
private:
	vector<int> values;
	vector<string> names;
	void change(int i, int j);
};