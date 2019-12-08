#pragma once
#include "Class.h"
#include "mips.h"

using namespace std;

class BasicBlock
{
public:
	vector<int> ins;		// the block that could go to this block
	vector<int> outs;	// the block that could reach from this block
	vector<MidCode> midCodes;
	vector<MidCode> verOne;
	bool hasLabel = false;
	string label = "";		// each label has a certain BasicBlock, but not every basicBlock has label
	int num = 0;

	void addMidCode(MidCode mid) {
		midCodes.push_back(mid);
	}

	void setLabel(string temp) {
		label = temp;
		hasLabel = true;
	}

	void addIn(int temp) {
		ins.push_back(temp);
	}

	void addOut(int temp) {
		outs.push_back(temp);
	}

	void setNum(int temp) {
		num = temp;
	}

	void init() {
		midCodes.clear();
		hasLabel = false;
		label = "";
		num = 0;
		verOne.clear();
	}

	void addVerOne(MidCode tmp) {
		verOne.push_back(tmp);
	}
};

class valueOpt
{
public:
	bool isConst = false;
	string name;
	int value = 0;
	bool isChar = false;

	void setConst() {
		isConst = true;
	}

	void setName(string name) {
		this->name = name;
	}

	void setValue(int value) {
		this->value = value;
	}

	void setChar() {
		isChar = true;
	}

	void init() {
		isChar = false;
		isConst = false;
		value = 0;
		name = "";
	}
};

void createBlocks();
void connectBlock();
void constOpt();
void outVerOne();