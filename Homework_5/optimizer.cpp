#include "Optimizer.h"
using namespace std;

map<int, BasicBlock> num2Block;
map<string, int> label2Num;
extern vector<MidCode> midCode;
vector<MidCode> versionOne;

void createBlocks() {
	int count = 0;		// used to count the basicBlock and label these blocks
	BasicBlock temp;
	MidCode curMid;
	bool busy = false;		// to record whether there is a basicBlock or not
	for (int i = 0; i < midCode.size(); i++) {
		curMid = midCode[i];
		if (!busy) {			// when busy is false, create a new BasicBlock, and won't insert this basiBlock until next block is created
			temp.init();
			temp.setNum(count);
			if (curMid.op == "label") {
				label2Num.insert(make_pair(curMid.x, count));
				temp.setLabel(curMid.x);
			}
			else if (curMid.op == "function") {
				label2Num.insert(make_pair(curMid.y, count));
				temp.setLabel(curMid.y);
			}
			temp.addMidCode(curMid);
			busy = true;
		}
		else {
			if (curMid.op == "label" || curMid.op == "function") {
				num2Block.insert(make_pair(count, temp));
				count++;
				temp.init();
				temp.setNum(count);
				if (curMid.op == "label") {
					temp.setLabel(curMid.x);
					label2Num.insert(make_pair(curMid.x, count));
				}
				else if (curMid.op == "function") {
					temp.setLabel(curMid.y);
					label2Num.insert(make_pair(curMid.y, count));
				}
				temp.addMidCode(curMid);
			}
			else if (curMid.op == "call" || curMid.op == "return" 
				|| curMid.op == "BZ" || curMid.op == "BNZ" || curMid.op == "GOTO") {
				temp.addMidCode(curMid);
				num2Block.insert(make_pair(count, temp));
				count++;
				busy = false;
			}
			else {
				temp.addMidCode(curMid);
			}
		}
	}
	if (busy) {
		num2Block.insert(make_pair(count, temp));
	}
}

void connectBlock() {
	string label;
	MidCode begin, end;
	BasicBlock curBlock, labelBlock;
	for (int i = 0; i < num2Block.size(); i++) {
		curBlock = num2Block[i];
		begin = curBlock.midCodes.front();
		end = curBlock.midCodes.back();
		if (end.op == "call" || end.op == "GOTO"
			|| end.op == "BZ" || end.op == "BNZ") {
			label = end.x;
			labelBlock = num2Block[label2Num[label]];
			num2Block[labelBlock.num].addIn(i);		// update the Ins of labelBlock in num2Blocks
			num2Block[i].addOut(labelBlock.num);	// update the Outs of curBlock in num2Blocks
			if (end.op == "BZ" || end.op == "BNZ") {
				num2Block[i].addOut(i + 1);			// BZ or BNZ block could reach the block after it
				num2Block[i + 1].addOut(i);		
			}
		}
		else if (end.op == "return") {
			label = end.y;
			for (int j = 0; j < num2Block.size(); j++) {
				begin = num2Block[j].midCodes.front();
				if ((begin.op == "call" || begin.op == "GOTO" || begin.op == "BZ" || begin.op == "BNZ") && begin.x == label) {
					num2Block[j].addIn(i);			// j means the block that curBlock return to, so i before j
					num2Block[i].addOut(j);			// update the Outs of the return Block
				}
			}
		}
	}
	cout << num2Block.size() << endl;
	cout << label2Num.size() << endl;
	return;
}

bool isOp(MidCode mid) {
	string op = mid.op;
	if (op == "+" || op == "-" || op == "*" || op == "/" || op == "=") {
		return true;
	}
	else {
		return false;
	}
}

int judgeMidCode(MidCode tmp) {			// 二进制 前一位为x是否为常量，后一位为y是否为常量
	int num = 0;
	if (isNum(tmp.x) || tmp.x[0] == '\'') {
		num = num + 2;
	}
	if (isNum(tmp.y) || tmp.y[0] == '\'') {
		num = num + 1;
	}
	return num;
}

int compute(string op, int a, int b) {
	if (op == "*") {
		return a * b;
	}
	else if (op == "/") {
		return a / b;
	}
	else if (op == "+") {
		return a + b;
	}
	else if (op == "-") {
		return a - b;
	}
	else {
		return 0;
	}
}

void constOpt() {
	BasicBlock curBlock;
	MidCode tmp;
	valueOpt var1, var2, var3;
	int value;
	//vector<valueOpt> values;		
	map<string, valueOpt> name2Var;		// the variable appears in this block
	vector<MidCode> newMidcodes;
	for (int i = 0; i < num2Block.size(); i++) {
		newMidcodes.clear();
		name2Var.clear();
		curBlock = num2Block[i];
		for (int j = 0; j < curBlock.midCodes.size(); j++) {
			value = 0;
			var1.init();
			var2.init();
			var3.init();
			tmp = curBlock.midCodes[j];
			if (isOp(tmp)) {
				if (tmp.op == "=" && (isNum(tmp.y) || tmp.y[0] == '\'')) {
					var1.setName(tmp.x);
					var1.setConst();
					if (isNum(tmp.y)) {
						var1.setValue(stoi(tmp.y)); 
					}				// set its value
					else { 
						var1.setValue(int(tmp.y[1])); 
						var1.setChar();
					}
					name2Var.insert(make_pair(var1.name, var1));					// insert the var into name2Var
					newMidcodes.push_back(tmp);
				}
				else if (tmp.op == "=") {
					var1.setName(tmp.x);
					var2.setName(tmp.y);
					if (name2Var.count(var2.name) > 0) {
						var2 = name2Var[var2.name];
						var1 = var2;
						var1.setName(tmp.x);
					}
					else {
						name2Var.insert(make_pair(var2.name, var2));
					}
					name2Var.insert(make_pair(var1.name, var1));
					if (var1.isConst) {
						if (var1.isChar) {						// isChar is used to print the Midcode which need char instead of int
							string str;
							str[0] = char(var1.value);
							tmp.setY(str);
						}
						else {
							tmp.setY(to_string(var1.value));
						}
					}
					newMidcodes.push_back(tmp);
				}
				else {
					if ((isNum(tmp.x) || tmp.x[0] == '\'') 
						&& (isNum(tmp.y) || tmp.y[0] == '\'')) {
						if (isNum(tmp.x)) { value = stoi(tmp.x); }
						else { value = int(tmp.x[1]); }	
						if (isNum(tmp.y)) { 
							value = compute(tmp.op, value, stoi(tmp.y));
						} 
						else { 
							value = compute(tmp.op, value, int(tmp.y[1]));
						}
						var3.setName(tmp.z);
						var3.setConst();
						var3.setValue(value);
						tmp.setOp("=");
						tmp.setX(var3.name);
						tmp.setY(to_string(var3.value));
						tmp.setZ("");
					}
					else if (isNum(tmp.x) || tmp.x[0] == '\'') {			// x is const but y not
						if (isNum(tmp.x)) { value = stoi(tmp.x); }	
						else { value = int(tmp.x[1]); }	
						if (name2Var.count(tmp.y) > 0 && name2Var[tmp.y].isConst) {
							value = compute(tmp.op, value, name2Var[tmp.y].value);
							var3.setConst();
							var3.setValue(value);
							var3.setName(tmp.z);
							tmp.setOp("=");
							tmp.setX(var3.name);
							tmp.setY(to_string(var3.value));
							tmp.setZ("");
						}
						else if (!(name2Var.count(tmp.y) > 0)) {
							var2.setName(tmp.y);
							name2Var.insert(make_pair(var2.name, var2));
							var3.setName(tmp.z);
						}
					}
					else if (isNum(tmp.y) || tmp.y[0] == '\'') {			// y is const but x not
						if (isNum(tmp.y)) { value = stoi(tmp.y); }
						else { value = int(tmp.y[1]); }
						if (name2Var.count(tmp.x) > 0 && name2Var[tmp.x].isConst) {
							value = compute(tmp.op, name2Var[tmp.x].value, value);
							var3.setConst();
							var3.setValue(value);
							var3.setName(tmp.z);
							tmp.setOp("=");
							tmp.setX(var3.name);
							tmp.setY(to_string(var3.value));
							tmp.setZ("");
						}
						else if (!(name2Var.count(tmp.y) > 0)) {
							var2.setName(tmp.y);
							name2Var.insert(make_pair(var2.name, var2));
							var3.setName(tmp.z);
						}
					}
					else {													// 
						if ((name2Var.count(tmp.x) > 0 && name2Var[tmp.x].isConst)
							&& (name2Var.count(tmp.y) > 0 && name2Var[tmp.y].isConst)) {
							value = compute(tmp.op, name2Var[tmp.x].value, name2Var[tmp.y].value);
							var3.setConst();
							var3.setValue(value);
							var3.setName(tmp.z);
							tmp.setOp("=");
							tmp.setX(var3.name);
							tmp.setY(to_string(var3.value));
							tmp.setZ("");
						}
						else {
							if (name2Var.count(tmp.x) > 0 && name2Var[tmp.x].isConst) {
								var1.setName(tmp.y);
								name2Var.insert(make_pair(var1.name, var1));
							}
							else if (name2Var.count(tmp.y) > 0 && name2Var[tmp.y].isConst) {
								var1.setName(tmp.x);
								name2Var.insert(make_pair(var1.name, var1));
							}
							else {
								var1.setName(tmp.x);
								name2Var.insert(make_pair(var1.name, var1));
								var2.setName(tmp.y);
								name2Var.insert(make_pair(var2.name, var2));
							}
						}
					}
					name2Var.insert(make_pair(var3.name, var3));
					newMidcodes.push_back(tmp);
				}
			}
			else {
				newMidcodes.push_back(tmp);
			}
		}
		num2Block[i].setVerOne(newMidcodes);
	}
}

void outVerOne() {
	ofstream verone;
	verone.open("verOne.txt", ios::out);
	verone.close();
	verone.open("verOne.txt", ios::app);
	versionOne.clear();
	int cnt = 0;
	for (int i = 0; i < num2Block.size(); i++) {
		for (int j = 0; j < num2Block[i].verOne.size(); j++) {
			verone << num2Block[i].verOne[j].op << " " << num2Block[i].verOne[j].x
				<< " " << num2Block[i].verOne[j].y << " " << num2Block[i].verOne[j].z << " " << endl;
			versionOne.push_back(num2Block[i].verOne[j]);
			cnt++;
		}
	}
	cout << cnt << endl;
	verone.close();
}