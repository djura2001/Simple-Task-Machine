#include "Variable.h"

void Variable::AddVariable(string s, int v)
{
	bool found = false;
	for (int i = 0; i < values.size(); i++)
	{
		if (names[i]==s)
		{
			values[i] = v;
			found = true;
			break;
		}
		
	}
	if (!found)
	{
		names.push_back(s);
		values.push_back(v);

	}
}

int Variable::getValue(string s)
{
	if (!isalpha(s[0])) return stoi(s);

	for (int i = 0; i < names.size(); i++)
	{
		if (names[i] == s)
		{
			return values[i];
		}
	}
	throw 1; //ako nije nadjen exception
}

void Variable::Sort()
{
	for(int i = 0; i < names.size() - 1; i++)
	{
		for (int j = i + 1; j < names.size(); j++)
		{
			if (names[i] > names[j]) change(i, j);
		}
	}
}

void Variable::Print(string foutput)
{
	ofstream output(foutput);
	Sort();

	for (int i = 0; i < names.size(); i++)
	{
		output << names[i] << "=" << values[i];
		if (i < names.size() - 1) output << endl;
	}

}

void Variable::change(int i, int j)
{
	int temp = values[i];
	values[i] = values[j];
	values[j] = temp;
	string tempString = names[i];
	names[i] = names[j];
	names[j] = tempString;
}
