#include"Class.h"
#include"Source.h"
#include"mips.h"

vector<string> lines;
int num = -1;
MidCode mid;
extern vector<MidCode> midCode;
extern Program program;
extern Function globalFunc;
extern map<int, string>num2Chars;
int layer = 0;				// 函数调用层数，主函数为第0层
int extra = 0;				// 目前调用所有函数的栈大小之和，包括全局的栈
Function currFunc;
map<string, int> name2position;
map<string, int> globalName2position;
vector<string> orders;

int pushNum = 0;

int nextMidcode()
{
	num++;
	if (num < midCode.size())
	{
		mid = midCode[num];
		return 1;
	}
	else {
		return 0;
	}
}

void mkGlobalOffset()			// 全局变量的偏移是相对于栈顶的偏移
{
	int temp = 0;
	for (int i = 0; i < globalFunc.vars.size(); i++)
	{
		Variable var = globalFunc.vars[i];
		temp = temp + var.size;
		globalName2position.insert(make_pair(var.name, temp));
	}
	string str = "sub $sp, $sp, " + to_string(temp);
	orders.push_back(str);
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

// 使用$t7记录栈顶
// 数组从栈向上叠加，即符号表中记录的是a[0]的位置，a[0] + 4 = a[1]

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

//读取内存时，若是全局变量，存下的绝对位置为栈的上界，因此算offset时，需要t7 - offset，且符号表中为下界，因此数组情况需将offset - i * 4
//若不是全局变量，则绝对位置为sp，即下界，因此offset，sp + offset, 数组的话直接offset + 4 * i

void lwData(string name, string regName)
{
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
			lwData(tmp, "$t5");
			lwData("4", "$t3");
			Mult("$t3", "$t3", "$t5");
			sp = 1;
		}
		name = name.substr(0, i);
	}
	if (currFunc.name2Unit.count(name))
	{
		if (sp == 0) {
			offset = name2position[name] + 4 * temp;
			str = "lw " + regName + ", " + to_string(offset) + "($sp)";
			orders.push_back(str);
		}
		else {
			Add("$t3", "$t3", to_string(name2position[name]));
			Add("$t3", "$t3", "$sp");
			str = "lw " + regName + ", ($t3)";
			orders.push_back(str);
		}
	}
	else if (globalFunc.name2Unit.count(name)) {
		if (sp == 0) {
			offset = globalName2position[name] - 4 * temp;
			str = "lw " + regName + ", -" + to_string(offset) + "($t7)";
			orders.push_back(str);
		}
		else {
			str = "li $t4, " + to_string(globalName2position[name]);
			orders.push_back(str);
			Minus("$t3", "$t4", "$t3");
			Minus("$t3", "$t7", "$t3");
			str = "lw " + regName + ", ($t3)";
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
			lwData(tmp, "$t5");
			lwData("4", "$t3");
			Mult("$t3", "$t3", "$t5");
			sp = 1;
		}
		name = name.substr(0, i);
	}
	if (currFunc.name2Unit.count(name))
	{
		if (sp == 0) {
			offset = name2position[name] + 4 * temp;
			str = "sw " + regName + ", " + to_string(offset) + "($sp)";
			orders.push_back(str);
		}
		else {
			Add("$t3", "$t3", to_string(name2position[name]));
			Add("$t3", "$t3", "$sp");
			str = "sw " + regName + ", ($t3)";
			orders.push_back(str);
		}
	}
	else if (globalFunc.name2Unit.count(name)) {
		if (sp == 0) {
			offset = globalName2position[name] - 4 * temp;
			str = "sw " + regName + ", -" + to_string(offset) + "($t7)";
			orders.push_back(str);
		}
		else {
			str = "li $t4, " + to_string(globalName2position[name]);
			orders.push_back(str);
			Minus("$t3", "$t4", "$t3");
			Minus("$t3", "$t7", "$t3");
			str = "sw " + regName + ", ($t3)";
			orders.push_back(str);
		}
	}
}

bool isNum(string str)
{
	try {
		int n = stoi(str);
		return true;
	}
	catch(exception e) {
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
		Add("$t0", "$0", to_string(x));
		swData(mid.z, "$t0");
		return;
	}
	else if (mid.x == "0") {
		name2 = "$0";
		if (mid.y == "RET") {
			name3 = "$t6";
		}
		else {
			lwData(mid.y, "$t0");
			name3 = "$t0";
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
			name2 = "$t6";
		}
		else {
			lwData(mid.y, "$t0");
			name2 = "$t0";
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
			name2 = "$t6";
		}
		else {
			lwData(mid.x, "$t0");
			name2 = "$t0";
		}
		name3 = to_string(x);
	}
	else {
		if (mid.x == "RET") {
			name2 = "$t6";
		}
		else {
			lwData(mid.x, "$t0");
			name2 = "$t0";
		}
		if (mid.y == "RET") {
			name3 = "$t6";
		}
		else {
			lwData(mid.y, "$t1");
			name3 = "$t1";
		}
	}
	switch (mid.op[0]) {
	case '+':
		Add("$t0", name2, name3);
		break;
	case '-':
		Minus("$t0", name2, name3);
		break;
	case '*':
		if (isNum(name3) || name3.size() == 1) {
			str = "la $t1, " + name3;
			orders.push_back(str);
			name3 = "$t1";
		}
		Mult("$t0", name2, name3);
		break;
	case '/':
		if (isNum(name3) || name3.size() == 1) {
			str = "la $t1, " + name3;
			orders.push_back(str);
			name3 = "$t1";
		}
		Div("$t0", name2, name3);
		break;
	}
	swData(mid.z, "$t0");
}

void controller()		// $sp
{
	int offset;
	string str;
	str = ".data";
	orders.push_back(str);
	for (int i = 0; i < num2Chars.size(); i++) {
		string chars = num2Chars[i];
		str = "string_" + to_string(i) + ": .asciiz \"" + chars + "\"";
		orders.push_back(str);
	}
	str = ".text";
	orders.push_back(str);
	str = "la $t7, ($sp)";
	orders.push_back(str);
	mkGlobalOffset();
	str = "j main";
	orders.push_back(str);
	while (nextMidcode()) {
		string str = mid.op;
		if (str == "=") {			// 赋值语句
			lwData(mid.y, "$t0");
			swData(mid.x, "$t0");
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
		else if (str == "var") {
			continue;
		}
		else if (str == "function") {
			currFunc = program.name2Func[mid.y];
			str = mid.y + ":";
			orders.push_back(str);
			//if (mid.y == "main") {
			//	str = "sub $sp, $sp, " + to_string(globalFunc.size);
			//}
			//else {
			//	mkFuncOffset(program.name2Func[mid.y]);
			//	str = "sub $sp, $sp, " + to_string(currFunc.size);
			//}
			mkFuncOffset(program.name2Func[mid.y]);
			str = "sub $sp, $sp, " + to_string(currFunc.size + 4);
			orders.push_back(str);
			str = "sw $ra, " + to_string(currFunc.size) + "($sp)";
			orders.push_back(str);
		}
		else if (str == "para") {
			continue;
		}
		else if (str == "cmp") {
			lwData(mid.x, "$t0");
			lwData(mid.z, "$t1");
			Minus("$t2", "$t0", "$t1");
			string cmp = mid.y;
			nextMidcode();
			if ((cmp == "<" && mid.op == "BNZ") || (cmp == ">=" && mid.op == "BZ"))
			{
				str = "bltz $t2, " + mid.x;
			}
			else if ((cmp == "<=" && mid.op == "BNZ") || (cmp == ">" && mid.op == "BZ"))
			{
				str = "blez $t2, " + mid.x;
			}
			else if ((cmp == "==" && mid.op == "BNZ") || (cmp == "!=" && mid.op == "BZ"))
			{
				str = "beq $t2, $0, " + mid.x;
			}
			else if ((cmp == "<" && mid.op == "BZ") || (cmp == ">=" && mid.op == "BNZ"))
			{
				str = "bgez $t2, " + mid.x;
			}
			else if ((cmp == "<=" && mid.op == "BZ") || (cmp == ">" && mid.op == "BNZ"))
			{
				str = "bgtz $t2, " + mid.x;
			}
			else if ((cmp == "==" && mid.op == "BZ") || (cmp == "!=" && mid.op == "BNZ"))
			{
				str = "bne $t2, $0, " + mid.x;
			}
			orders.push_back(str);
		}
		else if (str == "label") {
			str = mid.x + ":";
			orders.push_back(str);
		}
		else if (str == "BZ") {
			continue;
		}
		else if (str == "GOTO") {
			str = "j " + mid.x;
			orders.push_back(str);
		}
		else if (str == "BNZ") {
			continue;
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
						str = "li, $a0, " + mid.z;
						orders.push_back(str);
					}
					else {
						lwData(mid.z, "$a0");
					}
					str = "li $v0, 11";
					orders.push_back(str);
					str = "syscall";
					orders.push_back(str);
				}
				else if (mid.y == "int") {
					if (isNum(mid.z)) {
						str = "li, $a0, " + mid.z;
						orders.push_back(str);
					}
					else {
						lwData(mid.z, "$a0");
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
			swData(mid.y, "$v0");
		}
		else if (str == "return") {
			if (mid.x != "") {
				lwData(mid.x, "$t6");
			}
			if (currFunc.name != "main") {
				str = "lw $ra, " + to_string(currFunc.size) + "($sp)";
				orders.push_back(str);
				str = "add $sp, $sp, " + to_string(currFunc.size + 4);
				orders.push_back(str);
				str = "jr $ra";
				orders.push_back(str);
			}
		}
		else if (str == "push") {			// 将所有的形参的值放入正确的地方
			pushNum++;
			lwData(mid.x, "$t0");
			str = "sw $t0, " + to_string(pushNum * -4 - 4) + "($sp)";
			orders.push_back(str);				// 首先将形参放入栈下，然后才开栈
		}
		else if (str == "call") {			// 调用函数
			str = "jal " + mid.x;
			orders.push_back(str);
			pushNum = 0;
		}
		else if (str == "end") {
			str = "li $v0, 10";
			orders.push_back(str);
			str = "syscall";
			orders.push_back(str);
		}
		else if (str == "use") {			// 先给出调用函数名，划分好该函数的栈空间大小			
//			mkCurrFuncVars(currFunc.size - currFunc.factors.size() * 4);
		}
		else {
			continue;
		}
	}
}