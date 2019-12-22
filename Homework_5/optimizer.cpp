#include "Optimizer.h"
using namespace std;

#define K 16

map<int, BasicBlock> num2Block;
map<string, int> label2Num;
extern vector<MidCode> midCode;
extern Program program;
vector<MidCode> versionOne;
vector<MidCode> versionTwo;
vector<MidCode> versionThree;
vector<MidCode> versionFour;
vector<MidCode> versionFive;
map<string, vector<int>> funcName2Nums;


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
			num2Block[label2Num[label]].addIn(i);		// update the Ins of labelBlock in num2Blocks
			num2Block[i].addOut(label2Num[label]);	// update the Outs of curBlock in num2Blocks
			if (end.op == "BZ" || end.op == "BNZ" || end.op == "call") {
				num2Block[i].addOut(i + 1);			// BZ or BNZ block could reach the block after it
				num2Block[i + 1].addIn(i);		
			}
		}
		else if (end.op == "return") {
			label = end.y;
			for (int j = 0; j < num2Block.size(); j++) {
				end = num2Block[j].midCodes.back();
				if ((end.op == "call" || end.op == "GOTO" || end.op == "BZ" || end.op == "BNZ") && end.x == label) {
					num2Block[j].addIn(i);			// j means the block that curBlock return to, so i before j
					num2Block[i].addOut(j);			// update the Outs of the return Block
				}
			}
		}
		if (begin.op == "label" && num2Block[i - 1].midCodes.back().op != "GOTO") {
			num2Block[i].addIn(i - 1);
			num2Block[i - 1].addOut(i);
		}
	}
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

string replaceSub(string str, string old_str, string new_str) {
	if (new_str.size() > 0 && new_str.back() == ']' && str.size() > 0 && str.back() == ']') {
		return str;
	}
	if (str.find(old_str) != str.npos) {
		if (str == old_str) {
			str = new_str;
		}
		else if (str.find("[" + old_str + "]") != str.npos) {
			str.replace(str.find(old_str), old_str.length(), new_str);
		}
	} 
	return str;

	if (str.find(old_str) != str.npos) {
		str.replace(str.find(old_str), old_str.length(), new_str);
	}
	return str;
}

void constOpt() {
	BasicBlock curBlock;
	MidCode tmp, temp;
	int cnt = 0;
	valueOpt var1, var2, var3;
	int value;
	vector<valueOpt> values;		
	map<string, valueOpt> name2Var;		// the variable appears in this block
	vector<MidCode> newMidcodes;
	for (int i = 0; i < num2Block.size(); i++) {
		newMidcodes.clear();
		name2Var.clear();
		curBlock = num2Block[i];
		for (int j = 0; j < curBlock.midCodes.size(); j++) {
			cnt++;
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
							str[0] = '\'';
							str[2] = '\'';
							str[1] = char(var1.value);
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
								if (name2Var[tmp.x].isChar) {
									string x;
									x[0] = '\'';
									x[2] = '\'';
									x[1] = char(name2Var[tmp.x].value);
									tmp.setX(x);
								}
								else {
									tmp.setX(to_string(name2Var[tmp.x].value));
								}
								var1.setName(tmp.y);
								name2Var.insert(make_pair(var1.name, var1));
							}
							else if (name2Var.count(tmp.y) > 0 && name2Var[tmp.y].isConst) {
								if (name2Var[tmp.y].isChar) {
									string y;
									y[0] = '\'';
									y[2] = '\'';
									y[1] = char(name2Var[tmp.x].value);
									tmp.setY(y);
								}
								else {
									tmp.setY(to_string(name2Var[tmp.y].value));
								}
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
			if ((tmp.x[0] == '$') && (tmp.op == "=") && (isNum(tmp.y) || (tmp.y[0] == '\'')))
			{
				for (int t = j + 1; t < curBlock.midCodes.size(); t++) {
					curBlock.midCodes[t].setX(replaceSub(curBlock.midCodes[t].x, tmp.x, tmp.y));
					curBlock.midCodes[t].setY(replaceSub(curBlock.midCodes[t].y, tmp.x, tmp.y));
					curBlock.midCodes[t].setZ(replaceSub(curBlock.midCodes[t].z, tmp.x, tmp.y));
				}
				for (int t = i + 1; t < num2Block.size(); t++) {
					for (int k = 0; k < num2Block[t].midCodes.size(); k++) {
						num2Block[t].midCodes[k].setX(replaceSub(num2Block[t].midCodes[k].x, tmp.x, tmp.y));
						num2Block[t].midCodes[k].setY(replaceSub(num2Block[t].midCodes[k].y, tmp.x, tmp.y));
						num2Block[t].midCodes[k].setZ(replaceSub(num2Block[t].midCodes[k].z, tmp.x, tmp.y));
					}
				}
			}
		}
		for (int j = 0; j < newMidcodes.size(); j++) {
			tmp = newMidcodes[j];
			if ((tmp.x[0] == '$') && (tmp.op == "=") && (isNum(tmp.y) || (tmp.y[0] == '\''))) {
				continue;
			}
			else {
				num2Block[i].addVerOne(tmp);
			}
		}
	}
}

void outVersion() {
	ofstream verone, vertwo, verthree, verfour, verfive;
	verone.open("verOne.txt", ios::out);
	verone.close();
	verone.open("verOne.txt", ios::app);
	versionOne.clear();

	for (int i = 0; i < num2Block.size(); i++) {
		for (int j = 0; j < num2Block[i].verOne.size(); j++) {
			versionOne.push_back(num2Block[i].verOne[j]);
			verone << num2Block[i].verOne[j].op << " " << num2Block[i].verOne[j].x
				<< " " << num2Block[i].verOne[j].y << " " << num2Block[i].verOne[j].z << " " << endl;
		}
	}

	verone.close();
	removeExtraZero();

	vertwo.open("verTwo.txt", ios::out);
	vertwo.close();
	vertwo.open("verTwo.txt", ios::app);

	for (int i = 0; i < versionOne.size(); i++) {
		if (versionOne[i].opt) {
			versionTwo.push_back(versionOne[i]);
			vertwo << versionOne[i].op << " " << versionOne[i].x
				<< " " << versionOne[i].y << " " << versionOne[i].z << " " << endl;
		}
	}
	vertwo.close();	
	removeExtraAssign();

	verthree.open("verThree.txt", ios::out);
	verthree.close();
	verthree.open("verThree.txt", ios::app);

	for (int i = 0; i < versionTwo.size(); i++) {
		if (versionTwo[i].opt) {
			versionThree.push_back(versionTwo[i]);
			verthree << versionTwo[i].op << " " << versionTwo[i].x
				<< " " << versionTwo[i].y << " " << versionTwo[i].z << " " << endl;
		}
	}

	verthree.close();
	handleReturnAssign();

	verfour.open("verFour.txt", ios::out);
	verfour.close();
	verfour.open("verFour.txt", ios::app);

	for (int i = 0; i < versionThree.size(); i++) {
		versionFour.push_back(versionThree[i]);
		verfour << versionThree[i].op << " " << versionThree[i].x
			<< " " << versionThree[i].y << " " << versionThree[i].z << " " << endl;
	}

	verfour.close();
	removeExtraLabel();
	verfive.open("verFive.txt", ios::out);
	verfive.close();
	verfive.open("verFive.txt", ios::app);

	for (int i = 0; i < versionFour.size(); i++) {
		if (versionFour[i].opt) {
			versionFive.push_back(versionFour[i]);
			verfive << versionFour[i].op << " " << versionFour[i].x
				<< " " << versionFour[i].y << " " << versionFour[i].z << " " << endl;
		}
	}

	verfive.close();

	releaseFunc();
	removeExtraGoto();

	verfive.open("verFive.txt", ios::out);
	verfive.close();
	verfive.open("verFive.txt", ios::app);

	for (int i = 0; i < versionFive.size(); i++) {
		if (versionFive[i].opt) {
			verfive << versionFive[i].op << " " << versionFive[i].x
				<< " " << versionFive[i].y << " " << versionFive[i].z << " " << endl;
		}
	}

	verfive.close();
	createBlocks2();
	distributeReg();
}

void removeExtraGoto() {
	vector<MidCode> tempCode;
	int record = 0;
	int i;
	do {
		tempCode.clear();
		record = 0;
		for (i = 0; i < versionFive.size() - 1; i++) {
			if (versionFive[i].op == "GOTO" && versionFive[i + 1].op == "label"
				&& versionFive[i].x == versionFive[i + 1].x) {
				bool dele = true;
				for (int j = 0; j < versionFive.size(); j++) {
					if (versionFive[j].x == versionFive[i].x && j != i && j != i + 1) {
						dele = false;
						break;
					}
				}
				if (dele) {
					i++;
					record++;
				}
				else {
					tempCode.push_back(versionFive[i]);
				}
			}
			else if (versionFive[i].op == "=" && versionFive[i + 1].op == "=" && versionFive[i].x == versionFive[i + 1].y
				&& versionFive[i].x.size() > 3 && versionFive[i].x.substr(versionFive[i].x.size() - 3, 3) == "RET") {
				versionFive[i].x = versionFive[i + 1].x;
				tempCode.push_back(versionFive[i]);
				i++;
				record++;
			}
			else {
				tempCode.push_back(versionFive[i]);
			}
		}
		if (i < versionFive.size()) {
			tempCode.push_back(versionFive[i]);
		}
		versionFive.clear();
		for (int j = 0; j < tempCode.size(); j++) {
			versionFive.push_back(tempCode[j]);
		}
	} while (record != 0);
}

//void removeExtraGoto() {
//	vector<MidCode> tempCode;
//	int record = 0;
//	do {
//		record = 0;
//		for (int i = 0; i < versionFive.size() - 1; i++) {
////			if (versionFive[i].op == "GOTO" && versionFive[i + 1].op == "label"
////				&& versionFive[i + 1].x == versionFive[i].x) {
////				bool dele = true;
////				for (int j = 0; j < versionFive.size(); j++) {
////					if (versionFive[j].x == versionFive[i].x && j != i) {
////						dele = false;
////						break;
////					}
////				}
////				if (dele) {
////					record++;
//////					cout << versionFive[i].op << " " << versionFive[i].x << " " << versionFive[i].y << versionFive[i].z << endl;
////					i++;
////				}
////				else {
////					tempCode.push_back(versionFive[i]);
////				}
////			}
////			else 
//			if (versionFive[i + 1].x.size() > 3 && versionFive[i + 1].x.substr(versionFive[i + 1].x.size() - 3, 3) == "RET" && versionFive[i + 1].op == "=") {
//				if (versionFive[i].z == versionFive[i + 1].y) {
//					versionFive[i].z = versionFive[i + 1].x;
//					tempCode.push_back(versionFive[i]);
////					cout << versionFive[i].op << " " << versionFive[i].x << " " << versionFive[i].y << versionFive[i].z << endl;
//					i++;
//					record++;
//				}
//				else {
//					tempCode.push_back(versionFive[i]);
//				}
//			}
//			else if (versionFive[i + 1].y.size() > 3 && versionFive[i + 1].y.substr(versionFive[i + 1].y.size() - 3, 3) == "RET" && versionFive[i + 1].op == "=") {
//				if (versionFive[i + 1].y == versionFive[i].z) {
//					versionFive[i].z = versionFive[i + 1].x;
//					tempCode.push_back(versionFive[i]);
////					cout << versionFive[i].op << " " << versionFive[i].x << " " << versionFive[i].y << versionFive[i].z << endl;
//					i++;
//					record++;
//				}
//				else {
//					tempCode.push_back(versionFive[i]);
//				}
//			}
//			else {
//				tempCode.push_back(versionFive[i]);
//			}
//		}
//		tempCode.push_back(versionFive[versionFive.size() - 1]);
//		versionFive.clear();
//		for (int i = 0; i < tempCode.size(); i++) {
//			versionFive.push_back(tempCode[i]);
//		}
//		tempCode.clear();
//	} while (record != 0);
//}

void removeExtraZero() {
	MidCode temp;
	string new_name, old_name;
	for (int i = 0; i < versionOne.size(); i++) {
		temp = versionOne[i];
		if (temp.op == "+" && temp.x == "0" && temp.y != "RET") {
//			versionOne[i].setOpt();
			new_name = temp.y;
			old_name = temp.z;
			for (int j = i + 1; j < versionOne.size(); j++) {
				versionOne[j].setX(replaceSub(versionOne[j].x, old_name, new_name));		// 1,157,779.0
				versionOne[j].setY(replaceSub(versionOne[j].y, old_name, new_name));
				versionOne[j].setZ(replaceSub(versionOne[j].z, old_name, new_name));
				if (versionOne[j].x == temp.z) {		// 1,157,779.0
					versionOne[j].setX(temp.y);
				}
				if (versionOne[j].y == temp.z) {
					versionOne[j].setY(temp.y);
				}
				if (versionOne[j].z == temp.z) {
					versionOne[j].setZ(temp.y);
				}
			}
		}
	}

	for (int i = 0; i < versionOne.size(); i++) {
		temp = versionOne[i];
		if (temp.op == "+" && temp.x == "0" && temp.y != "RET") {
			if (temp.y.size() > 0 && temp.y.back() != ']') {
				versionOne[i].setOpt();
			}
		}
	}
}

void removeExtraAssign() {
	MidCode former, current;
	for (int i = 1; i < versionTwo.size(); i++) {
		former = versionTwo[i - 1]; 
		current = versionTwo[i];
		if (isOp(former) && current.op == "=" && former.z == current.y && former.z[0] == '$') {
			versionTwo[i].setOpt();
			versionTwo[i - 1].setZ(current.x);
		}
	}
}

void handleReturnAssign() {			// change + 0 RET a -> = a RET
	MidCode temp;
	for (int i = 0; i < versionThree.size(); i++) {
		temp = versionThree[i];
		if (isOp(temp) && temp.op != "=" && temp.x == "0" && temp.y == "RET") {
			versionThree[i].setOp("=");
			versionThree[i].setX(temp.z);
			versionThree[i].setY("RET");
			versionThree[i].setZ("");
		}
	}
}

void removeExtraLabel() {
	string new_name;
	string old_name;
	for (int i = 1; i < versionFour.size(); i++) {
		if (versionFour[i - 1].op == "label" && versionFour[i].op == "label") {
			new_name = versionFour[i - 1].x;
			old_name = versionFour[i].x;
			versionFour[i].setOpt();
			for (int j = 0; j < versionFour.size(); j++) {
				versionFour[j].setX(replaceSub(versionFour[j].x, old_name, new_name));
				versionFour[j].setY(replaceSub(versionFour[j].y, old_name, new_name));
				versionFour[j].setZ(replaceSub(versionFour[j].z, old_name, new_name));
			}
		}
	}
}

void createBlocks2() {
	int count = 0;		// used to count the basicBlock and label these blocks
	string curName = "";
	BasicBlock temp;
	MidCode curMid;
	bool busy = false;		// to record whether there is a basicBlock or not
	num2Block.clear();
	label2Num.clear();
	for (int i = 0; i < versionFive.size(); i++) {
		curMid = versionFive[i];
		if (!busy) {			// when busy is false, create a new BasicBlock, and won't insert this basiBlock until next block is created
			temp.init();
			temp.setFuncName(curName);
			temp.setNum(count);
			if (curMid.op == "label") {
				label2Num.insert(make_pair(curMid.x, count));
				temp.setLabel(curMid.x);
			}
			else if (curMid.op == "function") {
				label2Num.insert(make_pair(curMid.y, count));
				curName = curMid.y;
				temp.setLabel(curMid.y);
				temp.setFuncName(curName);
			}
			temp.addMidCode(curMid);
			busy = true;
		}
		else {
			temp.setFuncName(curName);
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
					curName = curMid.y;
					temp.setFuncName(curName);
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
		temp.setFuncName(curName);
		num2Block.insert(make_pair(count, temp));
	}

//	outBlocks();
	connectBlock();

	buildInAndOUt();

}

bool contain(vector<string> strs, string str) {
	for (int i = 0; i < strs.size(); i++) {
		if (str == strs[i]) {
			return true;
		}
	}
	return false;
}

bool containNum(vector<int> nums, int num) {
	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] == num) {
			return true;
		}
	}
	return false;
}

vector<string> minusVector(vector<string> a, vector<string> b) {
	vector<string> result;
	for (int i = 0; i < a.size(); i++) {
		if (!contain(b, a[i])) {
			result.push_back(a[i]);
		}
	}
	return result;
}

string getContent(string name) {
	int i;
	if (name == "") {
		return name;
	}
	if (name[name.size() - 1] != ']') {
		return name;
	}
	else {
		for (i = 0; i < name.size(); i++) {
			if (name[i] == '[') {
				break;
			}
		}
		return getContent(name.substr(i + 1, name.size() - i - 2));
	}
}

void buildInAndOUt() {
	vector<string> useNames;
	vector<string> defNames;

	MidCode temp;
	string funcName;
	for (int i = 0; i < num2Block.size(); i++) {
		useNames.clear();
		defNames.clear();
		for (int j = 0; j < num2Block[i].midCodes.size(); j++) {
			temp = num2Block[i].midCodes[j];
			if (temp.op == "=") {
				if (!contain(defNames, temp.y) && !contain(useNames, temp.y)
					&& !isNum(temp.y) && temp.y[0] != '\'' && temp.y != "RET") {
					useNames.push_back(temp.y);
				}
				if (!contain(defNames, temp.x) && !contain(useNames, temp.x) 
					&& !isNum(temp.x) && temp.x[0] != '\'' && temp.x != "RET") {
					defNames.push_back(temp.x);
				}
			}
			else if (isOp(temp)) {
				if (!contain(defNames, temp.x) && !contain(useNames, temp.x)
					&& !isNum(temp.x) && temp.x[0] != '\'' && temp.x != "RET") {
					useNames.push_back(temp.x);
				}
				if (!contain(defNames, temp.y) && !contain(useNames, temp.y)
					&& !isNum(temp.y) && temp.y[0] != '\'' && temp.y != "RET") {
					useNames.push_back(temp.y);
				}
				if (!contain(defNames, temp.z) && !contain(useNames, temp.z)
					&& !isNum(temp.z) && temp.z[0] != '\'' && temp.z != "RET") {
					defNames.push_back(temp.z);
				}
			}
			else if (temp.op == "cmp") {
				if (!contain(defNames, temp.x) && !contain(useNames, temp.x)
					&& !isNum(temp.x) && temp.x[0] != '\'' && temp.x != "RET") {
					useNames.push_back(temp.x);
				}
				if (!contain(defNames, temp.z) && !contain(useNames, temp.z)
					&& !isNum(temp.z) && temp.z[0] != '\'' && temp.z != "RET") {
					useNames.push_back(temp.z);
				}
			}
			else if (temp.op == "printf") {
				if (!contain(defNames, temp.z) && !contain(useNames, temp.z)
					&& !isNum(temp.z) && temp.z[0] != '\'' && temp.z != "" && temp.z != "RET") {
					useNames.push_back(temp.z);
				}
			}
			else if (temp.op == "scanf") {
				if (!contain(defNames, temp.x) && !contain(useNames, temp.x)
					&& !isNum(temp.x) && temp.x[0] != '\'' && temp.x != "" && temp.x != "RET") {
					defNames.push_back(temp.x);
				}
			}
			else if (temp.op == "push") {
				if (!contain(defNames, temp.x) && !contain(useNames, temp.x)
					&& !isNum(temp.x) && temp.x[0] != '\'' && temp.x != "RET") {
					useNames.push_back(temp.x);
				}
			}
			else if (temp.op == "para") {
				if (!contain(defNames, temp.y) && !contain(useNames, temp.y)
					&& !isNum(temp.y) && temp.y[0] != '\'' && temp.y != "RET") {
					defNames.push_back(temp.y);
				}
			}
		}
		num2Block[i].addDef(defNames);
		num2Block[i].addUse(useNames);
	}

	// Step 1, init all inVars
	for (int i = 0; i < num2Block.size(); i++) {		
		num2Block[i].inVars.clear();
		funcName = num2Block[i].funcName;
		if (funcName2Nums.count(funcName)) {
			funcName2Nums[funcName].push_back(i);
		}
		else {
			vector<int> tmp;
			tmp.push_back(i);
			funcName2Nums.insert(make_pair(funcName, tmp));
		}
	}

	// Step 2, 
	
	map<string, vector<int>>::iterator iter;
	int record = 0;
	vector<int> nums;
	int curNum, afterNum;
	MidCode begin, end;
	ofstream blocks;
	blocks.open("blocks.txt", ios::out);
	blocks.close();
	blocks.open("blocks.txt", ios::app);
		
	for (iter = funcName2Nums.begin(); iter != funcName2Nums.end(); iter++) {
		funcName = iter->first;
		nums = iter->second;
		if (funcName != "") {
			do {
				record = 0;
				for (int i = nums.size() - 1; i >= 0; i--) {
					curNum = nums[i];
					for (int j = 0; j < num2Block[curNum].outs.size(); j++) {
						afterNum = num2Block[curNum].outs[j];					
						if (containNum(nums, afterNum)) {		// find whether this funcBlock contain the after Block of num2Block[i]
							record += num2Block[curNum].addOutVar(num2Block[afterNum].inVars);		// out[B] = all in[after B]
						}
					}
					record += num2Block[curNum].addInVar(num2Block[curNum].useVars);			// add use[B] to in[B]
					record += num2Block[curNum].addInVar(minusVector(num2Block[curNum].outVars, num2Block[curNum].defVars));		// add out[B] - def[B] to in[B]
				}
			} while (record != 0);
			blocks << funcName << endl;
			for (int i = 0; i < nums.size(); i++) {
				curNum = nums[i];
				begin = num2Block[curNum].midCodes[0];
				end = num2Block[curNum].midCodes[num2Block[curNum].midCodes.size() - 1];
				blocks << "block" << curNum << endl;
				blocks << "out:	";
				for (int j = 0; j < num2Block[curNum].outVars.size(); j++) {
					blocks << num2Block[curNum].outVars[j] << " ";
				}
				blocks << "" << endl;
				blocks << "in:		";
				for (int j = 0; j < num2Block[curNum].inVars.size(); j++) {
					blocks << num2Block[curNum].inVars[j] << " ";
				}
				blocks << "" << endl;
				blocks << "def:	";
				for (int j = 0; j < num2Block[curNum].defVars.size(); j++) {
					blocks << num2Block[curNum].defVars[j] << " ";
				}
				blocks << "" << endl;
				blocks << "use:	";
				for (int j = 0; j < num2Block[curNum].useVars.size(); j++) {
					blocks << num2Block[curNum].useVars[j] << " ";
				}
				blocks << "" << endl;
				blocks << "in_blocks:	";
				for (int j = 0; j < num2Block[curNum].ins.size(); j++) {
					blocks << num2Block[curNum].ins[j] << " ";
				}
				blocks << "" << endl;
				blocks << "out_blocks:	";
				for (int j = 0; j < num2Block[curNum].outs.size(); j++) {
					blocks << num2Block[curNum].outs[j] << " ";
				}
				blocks << "" << endl;
				for (int j = 0; j < num2Block[curNum].midCodes.size(); j++) {
					blocks << num2Block[curNum].midCodes[j].op << " " << num2Block[curNum].midCodes[j].x 
						<< " " << num2Block[curNum].midCodes[j].y << " " << num2Block[curNum].midCodes[j].z << endl;
				}
				blocks << "" << endl;
				blocks << "" << endl;
			}
		}
	}
	blocks.close();
}

int containNode(vector<Node> nodes, Node node) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].name == node.name) {
			return i;
		}
	}
	return -1;
}

int findReg(vector<int> colors) {
	for (int i = 0; i < colors.size(); i++) {
		if (colors[i] == 0) {
			return i;
		}
	}
	return -1;
}

void distributeReg() {
	BasicBlock curBlock;
	map<string, vector<int>>::iterator iter;
	string funcName;
	vector<int> nums;
	vector<Node> nodes;
	vector<bool> vis;
	vector<int> stack;
	int record = 0;
	int cnt = 0;
	vector<int> color;
	set<int>::iterator nodeIter;
	Variable var;
	Factor factor;

	ofstream regFile;
	regFile.open("regs.txt", ios::out);
	regFile.close();
	regFile.open("regs.txt", ios::app);

	for (iter = funcName2Nums.begin(); iter != funcName2Nums.end(); iter++) {
		funcName = iter->first;
		nums = iter->second;
		nodes.clear();
		vis.clear();
		stack.clear();
		Function curFunc = program.name2Func[funcName];

		// build nodes
		for (int i = 0; i < nums.size(); i++) {
			num2Block[nums[i]].initVars();
			curBlock = num2Block[nums[i]];
			for (int j = 0; j < curBlock.vars.size(); j++) {
				Node temp = Node(curBlock.vars[j]);
				if (containNode(nodes, temp) == -1) {
					nodes.push_back(temp);
					vis.push_back(true);
				}
			}
		}

		// build edges

		set<string> groups;
		for (int t = 0; t < nums.size(); t++) {
			groups.clear();
			for (int i = 0; i < num2Block[nums[t]].inVars.size(); i++) {
				groups.insert(num2Block[nums[t]].inVars[i]);
			}
			for (int i = 0; i < num2Block[nums[t]].defVars.size(); i++) {
				groups.insert(num2Block[nums[t]].defVars[i]);
			}
			for (int i = 0; i < nodes.size(); i++) if (groups.find(nodes[i].name) != groups.end()) {
				for (int j = i + 1; j < nodes.size(); j++) {
					if (groups.find(nodes[j].name) != groups.end()) {
						nodes[i].nodes.insert(j);
						nodes[j].nodes.insert(i);
					}
				}
			}
		}

		//for (int i = 0; i < nodes.size(); i++) {
		//	for (int j = i + 1; j < nodes.size(); j++) {
		//		if (i != j) {
		//			for (int t = 0; t < nums.size(); t++) {
		//				bool flag1 = (contain(num2Block[nums[t]].inVars, nodes[i].name) || contain(num2Block[nums[t]].defVars, nodes[i].name));
		//				bool flag2 = (contain(num2Block[nums[t]].inVars, nodes[j].name) || contain(num2Block[nums[t]].defVars, nodes[j].name));
		//				if (flag1 && flag2) {
		//					nodes[i].nodes.insert(j);
		//					nodes[j].nodes.insert(i);	
		//				}
		//			}
		//			cout << i << " " << j << endl;
		//		}
		//	}
		//}

		do {
			do {
				for (int i = 0; i < nodes.size(); i++) {
					record = 0;
					cnt = 0;
					if (!vis[i]) { continue; }
					for (nodeIter = nodes[i].nodes.begin(); nodeIter != nodes[i].nodes.end(); nodeIter++) {
						if (vis[*nodeIter]) { cnt++; }
					}
					if (cnt < K) {
						vis[i] = false;
						stack.push_back(i);
						record = 1;
						break;
					}
				}
			} while (record != 0);

			int minNum = 999999, minI = -1;

			for (int i = 0; i < nodes.size(); i++) {
				if (vis[i]) {
					int cout = 0;
					for (set<int>::iterator iter = nodes[i].nodes.begin(); iter != nodes[i].nodes.end(); iter++) {
						if (vis[*iter] == true && nodes[*iter].flag == true) { cout++; }
					}
					if (cout < minNum) { 
						minI = i; 
						minNum = cout;
					}
				}
			}
			if (minI != -1) {
				vis[minI] = false;
				stack.push_back(minI);
				nodes[minI].flag = false;
			}

			//for (int i = nodes.size() - 1; i >= 0; i--) {
			//	if (vis[i]) {
			//		vis[i] = false;
			//		stack.push_back(i);
			//		nodes[i].flag = false;
			//	}
			//}

			cnt = 0;
			for (int i = 0; i < vis.size(); i++) {
				if (vis[i]) { cnt++; }
			}
		} while (cnt > 1);

		// color the last node
		for (int i = 0; i < vis.size(); i++) {
			if (vis[i] == true && nodes[i].flag == true) {
				nodes[i].color = 0;
				break;
			}
		}

		// color other nodes
		for (int i = stack.size() - 1; i >= 0; i--) {
			if (!nodes[i].flag) { continue; }
			vis[i] = true;
			color.clear();
			for (int j = 0; j < K; j++) {
				color.push_back(0);
			}
			for (nodeIter = nodes[i].nodes.begin(); nodeIter != nodes[i].nodes.end(); nodeIter++) {
				if (vis[*nodeIter] == true && nodes[*nodeIter].color != -1) {
					color[nodes[*nodeIter].color] = 1;
				}
			}
			nodes[i].color = findReg(color);
		}

		for (int i = 0; i < program.name2Func[funcName].vars.size(); i++) {
			var = program.name2Func[funcName].vars[i];
			program.name2Func[funcName].name2Reg.insert(make_pair(var.name, -1));
		}

		for (int i = 0; i < program.name2Func[funcName].factors.size(); i++) {
			factor = program.name2Func[funcName].factors[i];
			program.name2Func[funcName].name2Reg.insert(make_pair(factor.name, -1));
		}


		regFile << funcName << ":" << endl;
		for (int i = 0; i < nodes.size(); i++) {
			program.name2Func[funcName].name2Reg[nodes[i].name] = nodes[i].color;
			regFile << nodes[i].name << " " << getReg(nodes[i].color) << endl;
		}
		regFile << "" << endl;
	}

//	cout << "hello" << endl;
}

MidCode changeVarName(string funcName, MidCode temp, int count) {
	if (temp.x.substr(0, 8) != "_GLOBAL_" && !isNum(temp.x) && temp.x[0] != '\'' && temp.x != "" && temp.x != "int" && temp.x != "char") {
		temp.x = newName("_" + funcName + "_" + to_string(count) + "_", temp.x);
	}
	if (temp.y.substr(0, 8) != "_GLOBAL_" && !isNum(temp.y) && temp.y[0] != '\'' && temp.y != "" && temp.y != "int" && temp.y != "char") {
		if (temp.op != "cmp") {
			temp.y = newName("_" + funcName + "_" + to_string(count) + "_", temp.y);
		}
	}
	if (temp.z.substr(0, 8) != "_GLOBAL_" && !isNum(temp.z) && temp.z[0] != '\'' && temp.z != "" && temp.z != "int" && temp.z != "char") {
		temp.z = newName("_" + funcName + "_" + to_string(count) + "_", temp.z);
	}
	return temp;
}

string newName(string head, string name) {
	int begin = 0, end = 0;
	string be, en;
	if (isNum(name) || name[0] == '\'' || name.substr(0, 8) == "_GLOBAL_") {
		return name;
	}
	if (name != "" && name[name.size() - 1] == ']') {
		for (int i = 0; i < name.size(); i++) {
			if (name[i] == '[') { begin = i; }
		}
		end = name.size() - 1;
		be = name.substr(0, begin + 1);
		return head + be + newName(head, name.substr(begin + 1, end - begin - 1)) + "]";
	}
	else {
		return head + name;
	}
}

void releaseFunc() {
	int record = 0;
	map<string, int> name2Begin;
	map<string, int> name2End;
	map<string, bool> name2Able;
	vector<MidCode> tempCode;
	MidCode temp;
	string funcName = "";
	string curFuncName = "";
	int count = 0, tempI;
	do {
		funcName = "";
		curFuncName = "";
		name2Begin.clear();
		name2End.clear();
		name2Able.clear();
		count = 0;
		record = 0;
		for (int i = 0; i < versionFive.size(); i++) {
			temp = versionFive[i];
			if (temp.op == "function") {
				funcName = temp.y;
				name2Begin.insert(make_pair(funcName, i));
			}
			else if (temp.op == "return" && (versionFive[i + 1].op == "function" || versionFive[i + 1].op == "end")) {
				name2End.insert(make_pair(temp.y, i));
				if (!name2Able.count(temp.y)) {
					name2Able.insert(make_pair(temp.y, true)); 
				}
			}
			else if (temp.op == "call") {
//				cout << funcName << endl;
				name2Able.insert(make_pair(funcName, false));
			}
		}
		funcName = "";
		curFuncName = "";
		for (int i = 0; i < versionFive.size(); i++) {
			temp = versionFive[i];
			if (temp.op == "call" && name2Able[temp.x]) {
				tempI = i;
				record = 1;
				Variable var;
				Factor factor;
				funcName = temp.x;
				for (int j = 0; j < program.name2Func[funcName].vars.size(); j++) {
					var = program.name2Func[funcName].vars[j];
					var.setName(newName("_" + funcName + "_" + to_string(count) + "_", var.name));
					program.name2Func[curFuncName].addVar(var);
				}
				for (int j = 0; j < program.name2Func[funcName].factors.size(); j++) {
					factor = program.name2Func[funcName].factors[j];
					factor.setName(newName("_" + funcName + "_" + to_string(count) + "_", factor.name));
					program.name2Func[curFuncName].addVar(Variable(factor.name));
				}
				while (versionFive[tempI - 1].op == "push") {
					tempI = tempI - 1;
				}
				for (int j = name2Begin[funcName]; j <= name2End[funcName]; j++) {
					if (versionFive[j].op == "para") {
						tempCode.push_back(MidCode("=", newName("_" + funcName + "_" + to_string(count) + "_", versionFive[j].y), versionFive[tempI].x, ""));
						tempI++;
					}
					else if (versionFive[j].op == "return") {
						if (versionFive[j].x != "") {
							tempCode.push_back(MidCode("=", "_" + funcName + "_" + to_string(count) + "_" + "RET", newName("_" + funcName + "_" + to_string(count) + "_", versionFive[j].x), ""));
							program.name2Func[curFuncName].addVar(Variable("_" + funcName + "_" + to_string(count) + "_" + "RET"));
						}
						tempCode.push_back(MidCode("GOTO", "_" + funcName + "_" + to_string(count), "", ""));
					}
					else if (versionFive[j].op == "function") {
						continue;
					}
					else {
						temp = changeVarName(funcName, versionFive[j], count);
						tempCode.push_back(temp);
					}
				}
				tempCode.push_back(MidCode("label", "_" + funcName + "_" + to_string(count), "", ""));
				if (versionFive[i + 1].x == "RET") {
					versionFive[i + 1].x = "_" + funcName + "_" + to_string(count) + "_" + "RET";
				}
				if (versionFive[i + 1].y == "RET") {
					versionFive[i + 1].y = "_" + funcName + "_" + to_string(count) + "_" + "RET";
				}
				if (versionFive[i + 1].z == "RET") {
					versionFive[i + 1].z = "_" + funcName + "_" + to_string(count) + "_" + "RET";
				}
				count++;
			}
			else if (temp.op == "call" && !name2Able[temp.x]) {
				tempI = i;
				while (versionFive[tempI - 1].op == "push") {
					tempI--;
				}
				for (; tempI < i; tempI++) tempCode.push_back(versionFive[tempI]);
				tempCode.push_back(temp);
			}
			else if (temp.op == "push" || (temp.op == "use" && name2Able[temp.x])) {
				continue;
			}
			else if (versionFive[i].op == "function" && versionFive[i].y[0] == '_') {
				continue;
			}
			else {
				if (versionFive[i].op == "function") {
					curFuncName = versionFive[i].y;
				}
				tempCode.push_back(versionFive[i]);
			}
		}
		versionFive.clear();
		for (int i = 0; i < tempCode.size(); i++) {
			versionFive.push_back(tempCode[i]);
		}
		tempCode.clear();
	} while (record != 0);
//	cout << "hello" << endl;
}



 