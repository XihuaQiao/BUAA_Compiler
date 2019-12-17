#include"Class.h"
#include"Source.h"
#include"mips.h"
#include"Optimizer.h"

extern vector<MidCode> versionFive;
extern Program program;
extern Function globalFunc;
extern map<int, string>num2Chars;

map<int, string> reg2Name;

vector<string> orders;
map<string, int> name2position;
map<string, int> globalName2position;

int num = -1;
MidCode mid;
Function curFunc;
int pushNum = 0;

string getReg(int i) {
	switch (i) {
	case 0:
		return "$t4";
	case 1:
		return "$t5";
	case 2:
		return "$t6";
	case 3:
		return "$t7";
	case 4:
		return "$t8";
	case 5:
		return "$t9";
	case 6:
		return "$s0";
	case 7:
		return "$s1";
	case 8:
		return "$s2";
	case 9:
		return "$s3";
	case 10:
		return "$s4";
	case 11:
		return "$s5";
	case 12:
		return "$s6";
	case 13:
		return "$s7";
	case 14:
		return "$a2";
	case 15:
		return "$a3";
	default:
		return "-1";
	}
}

int nextMidCode() {
	num++;
	if (num < versionFive.size()) {
		mid = versionFive[num];
		return 1;
	}
	else {
		return 0;
	}
}

void mkGlobalOffset()			// 全局变量的偏移是相对于栈顶的偏移
{
	string str;

	for (int i = 0; i < globalFunc.vars.size(); i++)
	{
		Variable var = globalFunc.vars[i];
		if (var.size == 4) {
			str = var.name + ": .word " + "0";
			orders.push_back(str);
		}
		else if (var.size > 4) {
			str = var.name + ": .space " + to_string(var.size);
			orders.push_back(str);
		}
	}
}

void mkFuncOffset(Function func)
{
	name2position.clear();
	int temp = func.size;
	for (int i = 0; i < func.factors.size(); i++)
	{
		Factor factor = func.factors[i];
		temp = temp - 4;
		name2position.insert(make_pair(factor.name, temp));
	}
	for (int i = 0; i < func.vars.size(); i++)
	{
		Variable var = func.vars[i];
		temp = temp - var.size;
		name2position.insert(make_pair(var.name, temp));
	}
}

void Add(string name1, string name2, string name3)
{
	string str = "add " + name1 + ", " + name2 + ", " + name3;
	orders.push_back(str);
}

void Minus(string name1, string name2, string name3)
{
	string str = "sub " + name1 + ", " + name2 + ", " + name3;
	orders.push_back(str);
}

void Mult(string name1, string name2, string name3)		// name1 = name2 * name3
{
	string str = "mult " + name2 + ", " + name3;
	orders.push_back(str);
	str = "mflo " + name1;
	orders.push_back(str);
}

void Div(string name1, string name2, string name3)		// name1 = name2 % name3
{
	string str = "div " + name2 + ", " + name3;
	orders.push_back(str);
	str = "mflo " + name1;
	orders.push_back(str);
}

void lwData(string name, string regName)
{
//	cout << mid.op << mid.x << mid.y << mid.z << endl;
	vector<string> strs;
	string str;
	int offset, i;
	int temp = 0;
	int sp = 0;
	if (isNum(name) || name[0] == '\'') {
		str = "li " + regName + ", " + name;
		orders.push_back(str);
		return;
	}
	if (name == "RET") {
		str = "move " + regName + ", $v0";
		orders.push_back(str);
		return;
	}
	if (name[name.size() - 1] == ']')
	{
		for (i = 0; i < name.size(); i++)
		{
			if (name[i] == '[')
			{
				break;
			}
		}
		string tmp = name.substr(i + 1, name.size() - i - 2);
		if (isNum(tmp)) {
			temp = stoi(tmp);
		}
		else {
			if (curFunc.name2Reg.count(tmp) > 0 && curFunc.name2Reg[tmp] != -1) {
				str = "sll $t2, " + getReg(curFunc.name2Reg[tmp]) + ", 2";
				orders.push_back(str);
			}
			else {
				lwData(tmp, "$t2");			// $t5 -> $t2
				str = "sll $t2, $t2, 2";	// $t3 -> $t2, $t5 -> $t2
				orders.push_back(str);
			}
			sp = 1;
		}
		name = name.substr(0, i);
	}
	if (curFunc.name2Unit.count(name))
	{
		if (sp == 0) {
			offset = name2position[name] + 4 * temp;
			str = "lw " + regName + ", " + to_string(offset) + "($sp)";
			orders.push_back(str);
		}
		else {
			Add("$t2", "$t2", to_string(name2position[name]));		// $t3 -> $t2, $t3 -> $t2
			Add("$t2", "$t2", "$sp");								// $t3 -> $t2, $t3 -> $t2
			str = "lw " + regName + ", ($t2)";
			orders.push_back(str);
		}
	}
	else if (globalFunc.name2Unit.count(name)) {
		if (sp == 0) {
			offset = 4 * temp;
			str = "lw " + regName + ", " + name + " + " + to_string(offset);			// 数组地址为最下方的地址，即向上偏移，+，基地址为[0]
			orders.push_back(str);
		}
		else {
			str = "la $t3, " + name;				// $t4 -> $t3
			orders.push_back(str);
			Add("$t2", "$t3", "$t2");				// $t3 -> $t2, $t4 -> $t3, $t3 -> $t2
			str = "lw " + regName + ", ($t2)";
			orders.push_back(str);
		}
	}
}

void swData(string name, string regName)
{
	string str;
	int offset, i;
	int temp = 0;
	int sp = 0;
	if (name[name.size() - 1] == ']')
	{
		for (i = 0; i < name.size(); i++)
		{
			if (name[i] == '[')
			{
				break;
			}
		}
		string tmp = name.substr(i + 1, name.size() - i - 2);
		if (isNum(tmp)) {
			temp = stoi(tmp);
		}
		else {
			if (curFunc.name2Reg.count(tmp) > 0 && curFunc.name2Reg[tmp] != -1) {
				str = "sll $t2, " + getReg(curFunc.name2Reg[tmp]) + ", 2";
				orders.push_back(str); 
			}
			else {
				lwData(tmp, "$t2");			// $t5 -> $t2
				str = "sll $t2, $t2, 2";	// $t5 -> $t2, $t3 -> $t2
				orders.push_back(str);
			}
			sp = 1;
		}
		name = name.substr(0, i);
	}
	if (curFunc.name2Unit.count(name))
	{
		if (sp == 0) {
			offset = name2position[name] + 4 * temp;
			str = "sw " + regName + ", " + to_string(offset) + "($sp)";
			orders.push_back(str);
		}
		else {
			Add("$t2", "$t2", to_string(name2position[name]));	// $t3 -> $t2
			Add("$t2", "$t2", "$sp");							// $t3 -> $t2
			str = "sw " + regName + ", ($t2)";
			orders.push_back(str);
		}
	}
	else if (globalFunc.name2Unit.count(name)) {
		if (sp == 0) {
			offset = 4 * temp;
			str = "sw " + regName + ", " + name + " + " + to_string(offset);			// 数组地址为最下方的地址，即向上偏移，+，基地址为[0]
			orders.push_back(str);
		}
		else {
			str = "la $t3, " + name;		// $t4 -> $t3
			orders.push_back(str);
			Add("$t2", "$t3", "$t2");
			str = "sw " + regName + ", ($t2)";
			orders.push_back(str);
		}
	}
}

bool isNum(string str)
{
	try {
		stoi(str);
		return true;
	}
	catch (exception e) {
		return false;
	}
}

void basicOp()
{
	string str, name2, name3;
	int x, y;
	if ((isNum(mid.x) && isNum(mid.y)) || (isNum(mid.x) && mid.y[0] == '\'') ||
		(isNum(mid.x) && mid.y[0] == '\'') || (mid.x[0] == '\'' && mid.y[0] == '\'')) {
		if (isNum(mid.x)) {
			x = stoi(mid.x);
		}
		else {
			x = mid.x[1];
		}
		if (isNum(mid.y)) {
			y = stoi(mid.y);
		}
		else {
			y = mid.y[1];
		}
		switch (mid.op[0]) {
		case '+':
			x = x + y;
			break;
		case '-':
			x = x - y;
			break;
		case '*':
			x = x * y;
			break;
		case '/':
			x = x / y;
			break;
		}
		if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
			str = "li " + getReg(curFunc.name2Reg[mid.z]) + ", " + to_string(x);
		}
		else {
			Add("$t0", "$0", to_string(x));
			swData(mid.z, "$t0");
		}
		return;
	}
	else if (mid.x == "0") {
		name2 = "$0";
		if (mid.y == "RET") {
			name3 = "$v0";
		}
		else {
			if (curFunc.name2Reg.count(mid.y) > 0 && curFunc.name2Reg[mid.y] != -1) {
				name3 = getReg(curFunc.name2Reg[mid.y]);
			}
			else {
				lwData(mid.y, "$t0");
				name3 = "$t0";
			}
		}
	}
	else if (isNum(mid.x) || mid.x[0] == '\'') {
		if (isNum(mid.x)) {
			x = stoi(mid.x);
		}
		else {
			x = mid.x[1];
		}
		if (mid.y == "RET") {
			name2 = "$v0";
		}
		else {
			if (curFunc.name2Reg.count(mid.y) > 0 && curFunc.name2Reg[mid.y] != -1) {
				name2 = getReg(curFunc.name2Reg[mid.y]);
			}
			else {
				lwData(mid.y, "$t0");
				name2 = "$t0";
			}
		}
		name3 = to_string(x);
	}
	else if (isNum(mid.y) || mid.y[0] == '\'') {
		if (isNum(mid.y)) {
			x = stoi(mid.y);
		}
		else {
			x = mid.y[1];
		}
		if (mid.x == "RET") {
			name2 = "$v0";
		}
		else {
			if (curFunc.name2Reg.count(mid.x) > 0 && curFunc.name2Reg[mid.x] != -1) {
				name2 = getReg(curFunc.name2Reg[mid.x]);
			}
			else {
				lwData(mid.x, "$t0");
				name2 = "$t0";
			}
		}
		name3 = to_string(x);
	}
	else {
		if (mid.x == "RET") {
			name2 = "$v0";
		}
		else {
			if (curFunc.name2Reg.count(mid.x) > 0 && curFunc.name2Reg[mid.x] != -1) {
				name2 = getReg(curFunc.name2Reg[mid.x]);
			}
			else {
				lwData(mid.x, "$t0");
				name2 = "$t0";
			}
		}
		if (mid.y == "RET") {
			name3 = "$v0";
		}
		else {
			if (curFunc.name2Reg.count(mid.y) > 0 && curFunc.name2Reg[mid.y] != -1) {
				name3 = getReg(curFunc.name2Reg[mid.y]);
			}
			else {
				lwData(mid.y, "$t1");
				name3 = "$t1";
			}
		}
	}
	switch (mid.op[0]) {
	case '+':
		if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
			Add(getReg(curFunc.name2Reg[mid.z]), name2, name3);
		}
		else {
			Add("$t0", name2, name3);
		}
		break;
	case '-':
		if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
			Minus(getReg(curFunc.name2Reg[mid.z]), name2, name3);
		}
		else {
			Minus("$t0", name2, name3);
		}
		break;
	case '*':
		if (isNum(name3) || name3.size() == 1) {
			str = "la $t1, " + name3;
			orders.push_back(str);
			name3 = "$t1";
		}
		if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
			Mult(getReg(curFunc.name2Reg[mid.z]), name2, name3);
		}
		else {
			Mult("$t0", name2, name3);
		}
		break;
	case '/':
		if (isNum(name3) || name3.size() == 1) {
			str = "la $t1, " + name3;
			orders.push_back(str);
			name3 = "$t1";
		}
		if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
			Div(getReg(curFunc.name2Reg[mid.z]), name2, name3);
		}
		else {
			Div("$t0", name2, name3);
		}
		break;
	}
	if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
		return;
	}
	else {
		swData(mid.z, "$t0");
	}
}

void controller()
{
	string str;
	str = ".data";
	orders.push_back(str);
	for (int i = 0; i < num2Chars.size(); i++) {
		string chars = num2Chars[i];
		str = "string_" + to_string(i) + ": .asciiz \"" + chars + "\"";
		orders.push_back(str);
	}
	mkGlobalOffset();
	str = ".text";
	orders.push_back(str);
	str = "j main";
	orders.push_back(str);
	while (nextMidCode()) {
		string str = mid.op;
		if (str == "=") {			// 赋值语句
			if ((curFunc.name2Reg.count(mid.y) > 0 && curFunc.name2Reg[mid.y] != -1) 
				&& (curFunc.name2Reg.count(mid.x) > 0 && curFunc.name2Reg[mid.x] != -1)) {
				str = "move " + getReg(curFunc.name2Reg[mid.x]) + ", " + getReg(curFunc.name2Reg[mid.y]);
				orders.push_back(str);
			}
			else if (curFunc.name2Reg.count(mid.x) > 0 && curFunc.name2Reg[mid.x] != -1) {
				lwData(mid.y, getReg(curFunc.name2Reg[mid.x]));
			}
			else if (curFunc.name2Reg.count(mid.y) > 0 && curFunc.name2Reg[mid.y] != -1) {
				swData(mid.x, getReg(curFunc.name2Reg[mid.y]));
			}
			else {
				lwData(mid.y, "$t0");
				swData(mid.x, "$t0");
			}
		}
		else if (str == "[]=") {	// 给数组赋值
			string reg1;
			if (curFunc.name2Reg.count(mid.y) > 0 && curFunc.name2Reg[mid.y] != -1) {
			//	cout << curFunc.name2Reg[mid.y] << endl;
				reg1 = getReg(curFunc.name2Reg[mid.y]); 
			}
			else {
				lwData(mid.y, "$t0");
				reg1 = "$t0";
			}
			swData(mid.z + "[" + mid.x + "]", reg1);
//			cout << reg1 << endl;
		}
		else if (str == "[]") {		// 从数组取值
			string reg1;
			if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
			//	cout << curFunc.name2Reg[mid.z] << endl;
				reg1 = getReg(curFunc.name2Reg[mid.z]);
				lwData(mid.x + "[" + mid.y + "]", reg1);
			}
			else {
				lwData(mid.x + "[" + mid.y + "]", "$t0");
				swData(mid.z, "$t0");
			}
//			cout << reg1 << endl;
		}
		else if (str == "+") {
			basicOp();
		}
		else if (str == "-") {
			basicOp();
		}
		else if (str == "*") {
			basicOp();
		}
		else if (str == "/") {
			basicOp();
		}
		else if (str == "use" || str == "var" || str == "para" || str == "BZ" || str == "BNZ") {
			continue;
		}
		else if (str == "function") {
			str = mid.y + ":";
			orders.push_back(str);
			curFunc = program.name2Func[mid.y];
			mkFuncOffset(program.name2Func[mid.y]);
			str = "sub $sp, $sp, " + to_string(curFunc.size + 4);
			orders.push_back(str);
			str = "sw $ra, " + to_string(curFunc.size) + "($sp)";
			orders.push_back(str);

			for (int i = 0; i < curFunc.factors.size(); i++) {
				if (curFunc.name2Reg[curFunc.factors[i].name] != -1) {
					str = "lw " + getReg(curFunc.name2Reg[curFunc.factors[i].name]) + ", " + to_string(name2position[curFunc.factors[i].name]) + "($sp)";
					orders.push_back(str);
				}
			}
		}
		else if (str == "cmp") {
			string cmp, name1, name2;
			if (mid.x == "0") {
				cmp = mid.y;
				if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
					name1 = getReg(curFunc.name2Reg[mid.z]);
				}
				else {
					lwData(mid.z, "$t0");
					name1 = "$t0";
				}
				nextMidCode();
				if ((cmp == "<" && mid.op == "BNZ") || (cmp == ">=" && mid.op == "BZ"))
				{
					str = "bgtz " + name1 + ", " + mid.x;
				}
				else if ((cmp == "<=" && mid.op == "BNZ") || (cmp == ">" && mid.op == "BZ"))
				{
					str = "bgez " + name1 + ", " + mid.x;
				}
				else if ((cmp == "==" && mid.op == "BNZ") || (cmp == "!=" && mid.op == "BZ"))
				{
					str = "beqz " + name1 + ", " + mid.x;
				}
				else if ((cmp == "<" && mid.op == "BZ") || (cmp == ">=" && mid.op == "BNZ"))
				{
					str = "blez " + name1 + ", " + mid.x;
				}
				else if ((cmp == "<=" && mid.op == "BZ") || (cmp == ">" && mid.op == "BNZ"))
				{
					str = "bltz " + name1 + ", " + mid.x;
				}
				else if ((cmp == "==" && mid.op == "BZ") || (cmp == "!=" && mid.op == "BNZ"))
				{
					str = "bnez " + name1 + ", " + mid.x;
				}
				orders.push_back(str);
			}
			else if (mid.z == "0") {
				cmp = mid.y;
				if (curFunc.name2Reg.count(mid.x) > 0 && curFunc.name2Reg[mid.x] != -1) {
					name1 = getReg(curFunc.name2Reg[mid.x]);
				}
				else {
					lwData(mid.x, "$t0");
					name1 = "$t0";
				}
				nextMidCode();
				if ((cmp == "<" && mid.op == "BNZ") || (cmp == ">=" && mid.op == "BZ"))
				{
					str = "bltz " + name1 + ", " + mid.x;
				}
				else if ((cmp == "<=" && mid.op == "BNZ") || (cmp == ">" && mid.op == "BZ"))
				{
					str = "blez " + name1 + ", " + mid.x;
				}
				else if ((cmp == "==" && mid.op == "BNZ") || (cmp == "!=" && mid.op == "BZ"))
				{
					str = "beqz " + name1 + ", " + mid.x;
				}
				else if ((cmp == "<" && mid.op == "BZ") || (cmp == ">=" && mid.op == "BNZ"))
				{
					str = "bgez " + name1 + ", " + mid.x;
				}
				else if ((cmp == "<=" && mid.op == "BZ") || (cmp == ">" && mid.op == "BNZ"))
				{
					str = "bgtz " + name1 + ", " + mid.x;
				}
				else if ((cmp == "==" && mid.op == "BZ") || (cmp == "!=" && mid.op == "BNZ"))
				{
					str = "bnez " + name1 + ", " + mid.x;
				}
				orders.push_back(str);
			}
			else {
				if (curFunc.name2Reg.count(mid.x) > 0 && curFunc.name2Reg[mid.x] != -1) {
					name1 = getReg(curFunc.name2Reg[mid.x]);
				}
				else {
					lwData(mid.x, "$t0");
					name1 = "$t0";
				}
				if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
					name2 = getReg(curFunc.name2Reg[mid.z]);
				}
				else {
					lwData(mid.z, "$t1");
					name2 = "$t1";
				}
				Minus("$t0", name1, name2);
				cmp = mid.y;
				nextMidCode();
				if ((cmp == "<" && mid.op == "BNZ") || (cmp == ">=" && mid.op == "BZ"))
				{
					str = "bltz $t0, " + mid.x;
				}
				else if ((cmp == "<=" && mid.op == "BNZ") || (cmp == ">" && mid.op == "BZ"))
				{
					str = "blez $t0, " + mid.x;
				}
				else if ((cmp == "==" && mid.op == "BNZ") || (cmp == "!=" && mid.op == "BZ"))
				{
					str = "beqz $t0, " + mid.x;
				}
				else if ((cmp == "<" && mid.op == "BZ") || (cmp == ">=" && mid.op == "BNZ"))
				{
					str = "bgez $t0, " + mid.x;
				}
				else if ((cmp == "<=" && mid.op == "BZ") || (cmp == ">" && mid.op == "BNZ"))
				{
					str = "bgtz $t0, " + mid.x;
				}
				else if ((cmp == "==" && mid.op == "BZ") || (cmp == "!=" && mid.op == "BNZ"))
				{
					str = "bnez $t0," + mid.x;
				}
				orders.push_back(str);
			}
		}
		else if (str == "label") {
			str = mid.x + ":";
			orders.push_back(str);
		}
		else if (str == "GOTO") {
			str = "j " + mid.x;
			orders.push_back(str);
		}
		else if (str == "printf") {
			if (mid.x != "") {
				str = "la $a0, string_" + mid.x;
				orders.push_back(str);
				str = "li $v0, 4";
				orders.push_back(str);
				str = "syscall";
				orders.push_back(str);
			}
			if (mid.z != "") {
				if (mid.y == "char") {
					if (mid.z[0] == '\'') {
						str = "li $a0, " + mid.z;
						orders.push_back(str);
					}
					else {
						if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
							str = "move $a0, " + getReg(curFunc.name2Reg[mid.z]);
							orders.push_back(str);
						}
						else {
							lwData(mid.z, "$a0");
						}
					}
					str = "li $v0, 11";
					orders.push_back(str);
					str = "syscall";
					orders.push_back(str);
				}
				else if (mid.y == "int") {
					if (isNum(mid.z)) {
						str = "li $a0, " + mid.z;
						orders.push_back(str);
					}
					else {
						if (curFunc.name2Reg.count(mid.z) > 0 && curFunc.name2Reg[mid.z] != -1) {
							str = "move $a0, " + getReg(curFunc.name2Reg[mid.z]);
							orders.push_back(str);
						}
						else {
							lwData(mid.z, "$a0");
						}
					}
					str = "li $v0, 1";
					orders.push_back(str);
					str = "syscall";
					orders.push_back(str);
				}
			}
		}
		else if (str == "scanf") {
			string type = mid.x;
			if (type == "int") {
				str = "li $v0, 5";
				orders.push_back(str);
				str = "syscall";
				orders.push_back(str);
			}
			else if (type == "char") {
				str = "li $v0, 12";
				orders.push_back(str);
				str = "syscall";
				orders.push_back(str);
			}
			if (curFunc.name2Reg.count(mid.y) > 0 && curFunc.name2Reg[mid.y] != -1) {
				str = "move " + getReg(curFunc.name2Reg[mid.y]) + ", $v0";
				orders.push_back(str);
			}
			else {
				swData(mid.y, "$v0");
			}
		}
		else if (str == "return") {
			if (mid.x != "") {
				if (curFunc.name2Reg.count(mid.x) > 0 && curFunc.name2Reg[mid.x] != -1) {
					str = "move $v0, " + getReg(curFunc.name2Reg[mid.x]);
					orders.push_back(str);
				}
				else {
					lwData(mid.x, "$v0");
				}
			}
			if (curFunc.name != "main") {
				str = "lw $ra, " + to_string(curFunc.size) + "($sp)";
				orders.push_back(str);
				str = "add $sp, $sp, " + to_string(curFunc.size + 4);
				orders.push_back(str);
				str = "jr $ra";
				orders.push_back(str);
			}
		}
		else if (str == "push") {
			//pushNum++;
			//if (curFunc.name2Reg.count(mid.x) > 0 && curFunc.name2Reg[mid.x] != -1) {
			//	str = "sw " + getReg(curFunc.name2Reg[mid.x]) + ", " + to_string(pushNum * -4 - 4) + "($sp)";
			//	orders.push_back(str);
			//}
			//else {
			//	lwData(mid.x, "$t0");
			//	str = "sw $t0, " + to_string(pushNum * -4 - 4) + "($sp)";
			//	orders.push_back(str);				// 首先将形参放入栈下，然后才开栈
			//}
		}
		else if (str == "call") {
			int j = num;
			while (versionFive[j - 1].op == "push") {
				j--;
			}
			set<int> regs;
			map<string, int>::iterator iter1, iter2;
			for (iter1 = curFunc.name2Reg.begin(); iter1 != curFunc.name2Reg.end(); iter1++) {
				for (iter2 = program.name2Func[mid.x].name2Reg.begin(); iter2 != program.name2Func[mid.x].name2Reg.end(); iter2++) {
					if (iter1->second == iter2->second && iter1->second != -1) {
						regs.insert(iter1->second);
					}
				}
			}
			for (set<int>::iterator iter3 = regs.begin(); iter3 != regs.end(); iter3++) {
				str = "sub $sp, $sp, 4";
				orders.push_back(str);
				str = "sw " + getReg(*iter3) + ", ($sp)";
				orders.push_back(str);
			}

			for (; j < num; j++) {
				pushNum++;
				mid = versionFive[j];
				if (curFunc.name2Reg.count(mid.x) > 0 && curFunc.name2Reg[mid.x] != -1) {
					str = "sw " + getReg(curFunc.name2Reg[mid.x]) + ", " + to_string(pushNum * -4 - 4) + "($sp)";
					orders.push_back(str);
				}
				else {
					lwData(mid.x, "$t0");
					str = "sw $t0, " + to_string(pushNum * -4 - 4) + "($sp)";
					orders.push_back(str);				// 首先将形参放入栈下，然后才开栈
				}
			}

			mid = versionFive[num];
			str = "jal " + mid.x;
			orders.push_back(str);
			pushNum = 0;

			for (set<int>::reverse_iterator iter3 = regs.rbegin(); iter3 != regs.rend(); iter3++) {
				str = "lw " + getReg(*iter3) + ", ($sp)";
				orders.push_back(str);
				str = "add $sp, $sp, 4";
				orders.push_back(str);
			}
		}
		else if (str == "end") {
			str = "li $v0, 10";
			orders.push_back(str);
			str = "syscall";
			orders.push_back(str);
		}
		else {
			continue;
		}
	}
}