#include<vector>
#include<string>
#include<stdio.h>
#include<iostream>
#include<map>
#include"Source.h"
using namespace std;

#ifndef _CLASS_H_
#define _CLASS_H_

class singleWord
{
public:
	string content;
	string name;
	int raw_num;
	bool noRSingle;
	bool noRDouble;
};

class Unit
{
public:
	bool isConst = false;
	string midName;
	string name;
	string type;
	string content;
	void setMidName(string midName)
	{
		this->midName = midName;
	}
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
	bool var = false;
	int size = 4;
	Variable(string _name) {
		name = _name;
	}
	Variable() {
		name = "";
	}
};

class Factor : public Unit
{
public:
	bool haha = true;
};

class Function : public Unit
{
public:
	int size = 0;
	bool hasReturn = false;
	//bool returnError = false;
	bool existReturn = false;
	vector<Factor> factors;
	vector<Variable> vars;
	vector<Variable> consts;
	map<string, Unit> name2Unit;
	map<string, Factor> name2Factor;
	map<string, int> name2Reg;

	void addFactor(Factor factor)
	{
		factors.push_back(factor);
		name2Factor.insert(make_pair(factor.name, factor));
		name2Unit.insert(make_pair(factor.name, (Unit)factor));
		size = size + 4;
	}
	void addVar(Variable variable)
	{
		vars.push_back(variable);
		name2Unit.insert(make_pair(variable.name, (Unit)variable));
		size = size + variable.size;
	}
	void setExistReturn()
	{
		existReturn = true;
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

class Program
{
public:
	map<string, Function> name2Func;
	map<string, Unit> name2Unit;
	vector<Variable> vars;
	void addVar(Variable var)
	{
		vars.push_back(var);
	}
};

class Expression
{
public:
	bool empty = false;
	string name;
	string type;
	void setType(string s)
	{
		type = s;
	}
	void setName(string name)
	{
		this->name = name;
	}
};

class MidCode
{
public:
	string op = "";
	string x = "";
	string y = "";
	string z = "";
	bool opt = true;
	void setOp(string op)
	{
		this->op = op;
	}
	void setX(string x)
	{
		this->x = x;
	}
	void setY(string y)
	{
		this->y = y;
	}
	void setZ(string z)
	{
		this->z = z;
	}
	void setOpt() 
	{
		opt = false;
	}

	MidCode(string _op, string _x, string _y, string _z) {
		op = _op;
		x = _x;
		y = _y;
		z = _z;
	}

	MidCode() {
		op = "";
		x = "";
		y = "";
		z = "";
	}
};

#endif	_CLASS_H_