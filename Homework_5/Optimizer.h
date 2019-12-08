#pragma once
#include "Class.h"

using namespace std;

class BasicBlock
{
public:
	vector<int> ins;		// the block that could go to this block
	vector<int> outs;	// the block that could reach from this block
	vector<MidCode> midCodes;
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
	}
};