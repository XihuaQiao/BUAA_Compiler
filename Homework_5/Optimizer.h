#pragma once
#include "Class.h"
#include "mips.h"
#include "DAG.h"
#include<set>

class BasicBlock;
struct Node;

void createBlocks();
void createBlocks2();
void connectBlock();
int compute(string op, int a, int b);
bool isOp(MidCode mid);
int judgeMidCode(MidCode tmp);
void constOpt();
void outVersion();
void removeExtraZero();
void removeExtraAssign();
void handleReturnAssign();
void outBlocks();
void removeExtraLabel();
bool contain(vector<string> strs, string str);
bool containNum(vector<int> nums, int num);
void buildInAndOUt();
int containNode(vector<Node> nodes, Node node);
int findReg(vector<int> colors);
void distributeReg();
MidCode changeVarName(string funcName, MidCode temp, int count);
void releaseFunc();
string replaceSub(string str, string old_str, string new_str);
string newName(string head, string name);
void removeExtraGoto();

class BasicBlock;


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
	string funcName = "";

	vector<string> inVars;
	vector<string> outVars;
	vector<string> useVars;
	vector<string> defVars;
	vector<string> vars;

	void initVars() {
		vars.clear();
		for (int i = 0; i < inVars.size(); i++) {
			if (!contain(vars, inVars[i]) && inVars[i].substr(0, 8) != "_GLOBAL_") {
				vars.push_back(inVars[i]);
			}
		}
		for (int i = 0; i < outVars.size(); i++) {
			if (!contain(vars, outVars[i]) && outVars[i].substr(0, 8) != "_GLOBAL_") {
				vars.push_back(outVars[i]);
			}
		}
		for (int i = 0; i < useVars.size(); i++) {
			if (!contain(vars, useVars[i]) && useVars[i].substr(0, 8) != "_GLOBAL_") {
				vars.push_back(useVars[i]);
			}
		}
		for (int i = 0; i < defVars.size(); i++) {
			if (!contain(vars, defVars[i]) && defVars[i].substr(0, 8) != "_GLOBAL_") {
				vars.push_back(defVars[i]);
			}
		}
	}

	void addUse(vector<string> uses) {
		useVars = uses;
	}

	void addDef(vector<string> defs) {
		defVars = defs;
	}

	int addInVar(vector<string> names) {
		int cnt = 0;
		for (int i = 0; i < names.size(); i++) {
			if (!contain(inVars, names[i])) {
				inVars.push_back(names[i]);
				cnt++;
			}
		}
		return cnt;
	}

	int addOutVar(vector<string> names) {
		int cnt = 0;
		for (int i = 0; i < names.size(); i++) {
			if (!contain(outVars, names[i])) {
				outVars.push_back(names[i]);
				cnt++;
			}
		}
		return cnt;
	}

	void setFuncName(string funcName) {
		this->funcName = funcName;
	}

	void addMidCode(MidCode mid) {
		midCodes.push_back(mid);
	}

	void setLabel(string temp) {
		label = temp;
		hasLabel = true;
	}

	void addIn(int temp) {
		if (!containNum(ins, temp)) {
			ins.push_back(temp);
		}
	}

	void addOut(int temp) {
		if (!containNum(outs, temp)) {
			outs.push_back(temp);
		}
	}

	void setNum(int temp) {
		num = temp;
	}

	void init() {
		funcName = "";
		midCodes.clear();
		hasLabel = false;
		label = "";
		num = 0;
		verOne.clear();
		ins.clear();
		outs.clear();

		inVars.clear();
		outVars.clear();
		useVars.clear();
		defVars.clear();
		vars.clear();
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

struct Node {
	string name;
	set<int> nodes;
	int color;
	bool flag;
	Node(string name) {
		this->name = name;
		color = -1;
		flag = true;
	}
};



