#include<vector>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include<map>
using namespace std;

class Unit
{
public:
	bool isConst = false;
	string name;
	string type;
	string content;
	void setName(string name)
	{
		this->name = name;
	}
	void setType(string type)
	{
		this->type = type;
	}
	void setContent(string content)
	{
		this->content = content;
	}
	void setConst()
	{
		this->isConst = true;
	}
};

class Variable : public Unit
{
public:
	bool aha = false;
};

class Factor : public Unit
{
public:
	bool haha = true;
};

class Function : public Unit
{
public:
	bool hasReturn = false;
	bool returnError = false;
	bool existReturn = false;
	vector<Factor> factors;
	vector<Variable> vars;
	vector<Variable> consts;
	map<string, Unit> name2Unit;
	map<string, Factor> name2Factor;
	void addFactor(Factor factor)
	{
		factors.push_back(factor);
		name2Factor.insert(make_pair(factor.name, factor));
	}
	void addVar(Variable variable)
	{
		vars.push_back(variable);
		name2Unit.insert(make_pair(variable.name, (Unit)variable));
	}
	void setExistReturn()
	{
		existReturn = true;
	}
	void setReturnError()
	{
		returnError = true;
	}
	void setHasReturn()
	{
		hasReturn = true;
	}
	void addConst(Variable tmp)
	{
		consts.push_back(tmp);
		name2Unit.insert(make_pair(tmp.name, (Unit)tmp));
	}

};

class Expression
{
public:
	bool empty = false;
	string type = "int";
	void setType(string s)
	{
		type = s;
	}
};