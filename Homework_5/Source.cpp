#include"Source.h"

vector<singleWord> words;
vector<string> returnFunc;
vector<string> nonReturnFunc;
vector<Function> functions;
vector<MidCode> midCode;
ofstream outfile;
Function globalFunc;



string spWord[13] = { "const", "int", "char", "void", "main",
	"if", "else", "do", "while", "for", "scanf", "printf", "return" };
string spName[13] = { "CONSTTK", "INTTK", "CHARTK", "VOIDTK",
	"MAINTK", "IFTK", "ELSETK", "DOTK", "WHILETK", "FORTK", "SCANFTK", "PRINTFTK", "RETURNTK" };
FILE* in;

int raw = 0;
int now = -1;
singleWord sym;
Program program;

//map<string, Function> name2Func;
//map<string, Unit> name2Unit;

string readUntil(char x, FILE* fp)
{
	string temp;
	char y;
	while ((y = fgetc(fp)) != x) {
		if (y == '\\') {
			temp += y;
			y = fgetc(fp);
			temp += y;
		}
		else {
			temp += y;
		}
	}
	return temp;
}

int isLetter(char x)
{
	if (('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z') || (x == '_'))
		return 1;
	else
		return 0;
}

int isNum(char x)
{
	if ('0' <= x && x <= '9')
		return 1;
	else
		return 0;
}

int isSpWord(string word)
{
	int i;
	for (i = 0; i < 13; i++) {
		if (spWord[i] == word) {
			return i + 1;
		}
	}
	return 0;
}

void isSpace() {
	char ch = fgetc(in);
	while (ch == ' ' || ch == '\t' || ch == '\n') {
		ch = fgetc(in);
	}
	ungetc(ch, in);
}

void getWord()
{
	in = fopen("testfile.txt", "r");
	char ch;
	int i = 0;
	isSpace();
	while ((ch = fgetc(in)) != EOF) {
		singleWord temp;
		if (isLetter(ch)) {
			i = 0;
			temp.content += ch;
			while (isLetter(ch = fgetc(in)) || isNum(ch)) {
				temp.content += ch;
			}
			ungetc(ch, in);
			int id = isSpWord(temp.content);
			if (id > 0) {
				temp.name = spName[id - 1];
			}
			else {
				temp.name = "IDENFR";
			}
			temp.raw_num = raw + 1;
			words.push_back(temp);
		}
		else if (isNum(ch)) {
			i = 0;
			temp.content += ch;
			while (isNum(ch = fgetc(in))) {
				temp.content += ch;
			}
			ungetc(ch, in);
			temp.name = "INTCON";
			temp.raw_num = raw + 1;
			words.push_back(temp);
		}
		else {
			switch (ch) {
			case '\'':
				temp.name = "CHARCON";
				temp.content = fgetc(in);
				if ((ch = fgetc(in)) == '\'') {
					temp.noRSingle = false;
				}
				else {
					ungetc(ch, in);
					temp.noRSingle = true;
				}
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '\"':
				temp.name = "STRCON";
				temp.content = readUntil('\"', in);
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '+':
				temp.name = "PLUS";
				temp.content = "+";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '-':
				temp.name = "MINU";
				temp.content = "-";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '*':
				temp.name = "MULT";
				temp.content = "*";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '/':
				temp.name = "DIV";
				temp.content = "/";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '<':
				if ((ch = fgetc(in)) == '=') {
					temp.name = "LEQ";
					temp.content = "<=";
					temp.raw_num = raw + 1;
					words.push_back(temp);
				}
				else {
					temp.name = "LSS";
					temp.content = "<";
					temp.raw_num = raw + 1;
					words.push_back(temp);
					ungetc(ch, in);
				}
				break;
			case '>':
				if ((ch = fgetc(in)) == '=') {
					temp.name = "GEQ";
					temp.content = ">=";
					temp.raw_num = raw + 1;
					words.push_back(temp);
				}
				else {
					temp.name = "GRE";
					temp.content = ">";
					temp.raw_num = raw + 1;
					words.push_back(temp);
					ungetc(ch, in);
				}
				break;
			case '=':
				if ((ch = fgetc(in)) == '=') {
					temp.name = "EQL";
					temp.content = "==";
					temp.raw_num = raw + 1;
					words.push_back(temp);
				}
				else {
					temp.name = "ASSIGN";
					temp.content = "=";
					temp.raw_num = raw + 1;
					words.push_back(temp);
					ungetc(ch, in);
				}
				break;
			case '!':
				if ((ch = fgetc(in)) == '=') {
					temp.name = "NEQ";
					temp.content = "!=";
					temp.raw_num = raw + 1;
					words.push_back(temp);
				}
				else {
					ungetc(ch, in);
				}
				break;
			case ';':
				temp.name = "SEMICN";
				temp.content = ";";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case ',':
				temp.name = "COMMA";
				temp.content = ",";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '(':
				temp.name = "LPARENT";
				temp.content = "(";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case ')':
				temp.name = "RPARENT";
				temp.content = ")";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '[':
				temp.name = "LBRACK";
				temp.content = "[";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case ']':
				temp.name = "RBRACK";
				temp.content = "]";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '{':
				temp.name = "LBRACE";
				temp.content = "{";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '}':
				temp.name = "RBRACE";
				temp.content = "}";
				temp.raw_num = raw + 1;
				words.push_back(temp);
				break;
			case '\n':
				raw++;
				break;
			default:
				break;
			}
		}
	}
	fclose(in);
}

int nextSym() {
	now++;
	if (now < words.size()) {
		sym = words[now];
		//		outfile << sym.name << " " << sym.content << endl;
		return 1;
	}
	else {
		return 0;
	}
}

int preRead() {
	now++;
	if (now < words.size()) {
		sym = words[now];
		return 1;
	}
	else {
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////////

int checkRepeat(Function& func, string name, int raw)
{
	cout << name << endl;
	if (program.name2Func.count(name) || func.name2Unit.count(name)) {
		errorOutput(raw, 2);
		return 0;
	}
	else {
		return 1;
	}
}

void errorOutput(int raw_num, int code)
{
	switch (code) {
	case 1:
		outfile << raw_num << " a" << endl;
		break;
	case 2:
		outfile << raw_num << " b" << endl;
		break;
	case 3:
		outfile << raw_num << " c" << endl;
		break;
	case 4:
		outfile << raw_num << " d" << endl;
		break;
	case 5:
		outfile << raw_num << " e" << endl;
		break;
	case 6:
		outfile << raw_num << " f" << endl;
		break;
	case 7:
		outfile << raw_num << " g" << endl;
		break;
	case 8:
		outfile << raw_num << " h" << endl;
		break;
	case 9:
		outfile << raw_num << " i" << endl;
		break;
	case 10:
		outfile << raw_num << " j" << endl;
		break;
	case 11:
		outfile << raw_num << " k" << endl;
		break;
	case 12:
		outfile << raw_num << " l" << endl;
		break;
	case 13:
		outfile << raw_num << " m" << endl;
		break;
	case 14:
		outfile << raw_num << " n" << endl;
		break;
	case 15:
		outfile << raw_num << " o" << endl;
		break;
	default:
		outfile << "wrong code" << endl;
		break;
	}
}

int checkSemicn()
{
	if (preRead() && sym.content == ";") {
		now--;
		nextSym();					// ;
		return 1;
	}
	else {
		now--;
		errorOutput(sym.raw_num - 1, 11);
		return 0;
	}
}

int checkRBrack()
{
	if (preRead() && sym.content == "]") {
		now--;
		nextSym();
		return 1;
	}
	else {
		now--;
		errorOutput(sym.raw_num, 13);
		return 0;
	}
}

int checkRParent()
{
	if (preRead() && sym.content == ")") {
		now--;
		nextSym();
		return 1;
	}
	else {
		now--;
		errorOutput(sym.raw_num, 12);
		return 0;
	}
}

int isProgram()
{
	isConstDes(globalFunc);
	isVarDes(globalFunc);
	while (isReturnFuncDef() || isNonReturnFuncDef());
	isMainFunc();
	//	outfile << "<程序>" << endl;
	return 1;
}

int isConstDes(Function& tmp)
{
	int cnt = 0;
	while (preRead() && sym.content == "const") {
		cnt++;
		now--;
		nextSym();				// const
		isConstDef(tmp);
		checkSemicn();
	}
	now--;
	if (cnt != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int isConstDef(Function& tmp)
{
	int rec = 0;
	int rec_1 = 1;
	MidCode temp;
	preRead();
	Variable var;
	if (sym.content == "int") {
		var.setType(sym.content);
		now--;
		nextSym();				// int
		temp.setX(sym.content);
		isIdenti(var);
		temp.setY(sym.content);
		rec = checkRepeat(tmp, var.name, sym.raw_num);
		nextSym();				// =
		temp.setOp(sym.content);
		rec_1 = isSignInt(var);
		temp.setZ(sym.content);
		if (rec_1 == 0) {
			errorOutput(sym.raw_num, 15);
			nextSym();
		}
		var.setConst();
		if (rec) 
		{ 
			tmp.addConst(var); 
			midCode.push_back(temp);
		}
		while (preRead() && sym.content == ",") {
			now--;
			nextSym();			// ,
			isIdenti(var);
			temp.setY(sym.content);
			rec = checkRepeat(tmp, var.name, sym.raw_num);
			nextSym();			// =
			temp.setOp(sym.content);
			rec_1 = isSignInt(var);
			temp.setZ(sym.content);
			if (rec_1 == 0) {
				errorOutput(sym.raw_num, 15);
				nextSym();
			}
			var.setConst();
			if (rec) { 
				tmp.addConst(var); 
				midCode.push_back(temp);
			}
		}
		now--;
		//			outfile << "<常量定义>" << endl;
		return 1;
	}
	else if (sym.content == "char") {
		var.setType(sym.content);
		now--;
		nextSym();				//char
		temp.setX(sym.content);
		isIdenti(var);
		temp.setY(sym.content);
		rec = checkRepeat(tmp, var.name, sym.raw_num);
		nextSym();				//'='
		temp.setOp(sym.content);
		rec_1 = isChar(var);
		temp.setZ(sym.content);
		if (rec_1 == 0)
		{
			errorOutput(sym.raw_num, 15);
			nextSym();
		}
		var.setConst();
		if (rec) { 
			tmp.addConst(var); 
			midCode.push_back(temp);
		}
		while (preRead() && sym.content == ",") {
			now--;
			nextSym();			// ,
			isIdenti(var);
			temp.setY(sym.content);
			rec = checkRepeat(tmp, var.name, sym.raw_num);
			nextSym();			// =
			temp.setOp(sym.content);
			rec_1 = isChar(var);
			temp.setZ(sym.content);
			if (rec_1 == 0)
			{
				errorOutput(sym.raw_num, 15);
				nextSym();
			}
			var.setConst();
			if (rec) { 
				tmp.addConst(var); 
				midCode.push_back(temp);
			}
		}
		now--;
		//			outfile << "<常量定义>" << endl;
		return 1;
	}
	else {
		now--;
		return 0;
	}
}

int isAssignSent(Function& func)
{
	Expression exp;
	MidCode temp;
	Unit unit;
	isIdenti(unit);
	temp.setX = sym.content;
	if (func.name2Unit.count(unit.name) > 0)
	{
		unit = func.name2Unit[unit.name];
		if (unit.isConst)
		{
			errorOutput(sym.raw_num, 10);
		}
	}
	else if (globalFunc.name2Unit.count(unit.name))
	{
		unit = globalFunc.name2Unit[unit.name];
		if (unit.isConst)
		{
			errorOutput(sym.raw_num, 10);
		}
	}
	if (preRead() && sym.content == "[") {
		now--;
		nextSym();			//'['
		temp.x = temp.x + sym.content;
		isExpression(func, exp);
		temp.x = temp.x + exp.name;
		if (exp.type != "int")
		{
			errorOutput(sym.raw_num, 9);
		}
		checkRBrack();			//']'
		temp.x = temp.x + sym.content;
	}
	else {
		now--;
	}
	if (preRead() && sym.content == "=") {
		now--;
		nextSym();
		temp.setOp(sym.content);
		isExpression(func, exp);
		temp.setY(exp.name);
		temp.setZ("");
		midCode.push_back(temp);
		//		outfile << "<赋值语句>" << endl;
		return 1;
	}
	else {
		now--;
		return 0;
	}
}

int isSignInt(Unit& unit)
{
	preRead();
	if (sym.content == "+" || sym.content == "-") {
		now--;
		nextSym();
		unit.setContent(sym.content);
	}
	else {
		now--;
	}
	if (isUnSignInt(unit)) {
		//			outfile << "<整数>" << endl;
		return 1;
	}
	else {
		return 0;
	}
}

int isUnSignInt(Unit& unit)
{
	if (preRead() && sym.name == "INTCON") {
		now--;
		nextSym();
		if (sym.content[0] == '0' && sym.content.length() > 1) {
			errorOutput(sym.raw_num, 1);
			return 0;
		}
		//			outfile << "<无符号整数>" << endl;
		unit.setContent(unit.content + sym.content);
		return 1;
	}
	else {
		now--;
		return 0;
	}
}

int isIdenti(Unit& unit)
{
	if (preRead() && sym.name == "IDENFR") {
		now--;
		nextSym();
		for (int i = 0; i < sym.content.length(); i++) {
			if (!(isLetter(sym.content[i]) | isNum(sym.content[i]))) {
				errorOutput(sym.raw_num, 1);
				return 0;
			}
		}
		unit.setName(sym.content);
		return 1;
	}
	else {
		now--;
		return 0;
	}
}

int isChar(Unit& unit)
{
	if (preRead() && sym.name == "CHARCON") {
		now--;
		nextSym();
		unit.setType(sym.content);
		if (sym.noRSingle) {
			errorOutput(sym.raw_num, 1);
			return 0;
		}
		else if ((sym.content != "*")
			&& (sym.content != "/")
			&& (sym.content != "+")
			&& (sym.content != "-")
			&& !isLetter(sym.content[0])
			&& !isNum(sym.content[0]))
		{
			errorOutput(sym.raw_num, 1);
		}
		return 1;
	}
	else {
		now--;
		return 0;
	}
}

int isVarDes(Function& func)
{
	preRead();
	string str1 = sym.name;
	preRead();
	string str2 = sym.name;
	preRead();
	string str3 = sym.content;
	while ((str1 == "INTTK" || str1 == "CHARTK")
		&& (str2 == "IDENFR")
		&& (str3 == "," || str3 == ";" || str3 == "[")
		) {
		now = now - 3;
		isVarDef(func);
		checkSemicn();
		preRead();
		str1 = sym.name;
		preRead();
		str2 = sym.name;
		preRead();
		str3 = sym.content;
	}
	now = now - 3;
	return 1;
}

int isVarDef(Function& func)
{
	Variable var;
	MidCode temp;
	temp.setOp("var");
	isTypeIdenti(var);
	temp.setX(sym.content);
	isIdenti(var);
	temp.setY(sym.content);
	temp.setZ("");
	if (preRead() && sym.content == "[") {
		now--;
		nextSym();				// [
		temp.y = temp.y + sym.content;
		Unit unit;
		isUnSignInt(unit);
		temp.y = temp.y + sym.content;
		checkRBrack();			// ]
		temp.y = temp.y + sym.content;
	}
	if (checkRepeat(func, var.name, sym.raw_num)) 
	{ 
		func.addVar(var); 
		midCode.push_back(temp);
	}
	else {
		now--;
	}
	while (preRead() && sym.content == ",") {
		now--;
		nextSym();				// ,
		isIdenti(var);
		temp.setY(sym.content);
		if (preRead() && sym.content == "[") {
			now--;
			nextSym();			// [
			temp.y = temp.y + sym.content;
			Unit unit;
			isUnSignInt(unit);
			temp.y = temp.y + sym.content;
			checkRBrack();
			temp.y = temp.y + sym.content;
		}
		if (checkRepeat(func, var.name, sym.raw_num)) 
		{ 
			func.addVar(var); 
			midCode.push_back(temp);
		}
		else {
			now--;
		}
	}
	now--;
	return 1;
}

int isTypeIdenti(Unit& unit)
{
	if (preRead() && (sym.content == "int" || sym.content == "char")) {
		now--;
		nextSym();
		unit.setType(sym.content);
		return 1;
	}
	else {
		now--;
		return 0;
	}
}

int isReturnFuncDef()
{
	int rec = 0;
	if (preRead() && (sym.content == "int" || sym.content == "char")) {
		Function tmp;
		tmp.setHasReturn();
		tmp.setType(sym.content);
		now--;
		isStateHead(tmp);
		rec = checkRepeat(tmp, tmp.name, sym.raw_num);
		nextSym();			// (
		isFactorList(tmp);
		checkRParent();		// )
		nextSym();			// {
		isCompSentenses(tmp);
		nextSym();			// }
		if (!tmp.existReturn)
		{
			errorOutput(sym.raw_num, 8);
		}
		//			outfile << "<有返回值函数定义>" << endl;
		if (rec) {
			functions.push_back(tmp);
			program.name2Func.insert(make_pair(tmp.name, tmp));
		}
		return 1;
	}
	else {
		now--;
		return 0;
	}
}

int isNonReturnFuncDef()
{
	int rec;
	preRead();
	string str1 = sym.content;
	preRead();
	string str2 = sym.content;
	if (str1 == "void" && str2 != "main") {
		Function tmp;
		now = now - 2;
		nextSym();			//void
		isIdenti(tmp);
		rec = checkRepeat(tmp, tmp.name, sym.raw_num);
		nextSym();			//'('
		isFactorList(tmp);
		checkRParent();			//')'
		nextSym();			//'{'
		isCompSentenses(tmp);
		nextSym();			//'}'
//			outfile << "<无返回值函数定义>" << endl;
		if (rec) {
			functions.push_back(tmp);
			program.name2Func.insert(make_pair(tmp.name, tmp));
		}
		return 1;
	}
	else {
		now = now - 2;
		return 0;
	}
}

int isFactorList(Function& func)
{
	int rec;
	Factor tmp;
	isTypeIdenti(tmp);
	isIdenti(tmp);
	rec = checkRepeat(func, tmp.name, sym.raw_num);
	if (rec && tmp.name != "") { func.addFactor(tmp); }
	while (preRead() && sym.content == ",") {
		now--;
		nextSym();				// ,
		isTypeIdenti(tmp);
		isIdenti(tmp);
		rec = checkRepeat(func, tmp.name, sym.raw_num);
		if (rec) { func.addFactor(tmp); }
	}
	now--;
	//		outfile << "<参数表>" << endl;
	return 1;
}

int isCompSentenses(Function& func)
{
	isConstDes(func);
	isVarDes(func);
	isSentenses(func);
	//	outfile << "<复合语句>" << endl;
	return 1;
}

int isSentenses(Function& func)
{
	while (isSentense(func));
	//	outfile << "<语句列>" << endl;
	return 1;
}

int isValueList(Function& func)
{
	preRead();
	vector<Unit> values;
	Unit unit;
	Expression exp;
	if (sym.content == ")") {
		now--;
	}
	else {
		now--;
		isExpression(func, exp);
		unit.setType(exp.type);
		values.push_back(unit);
		while (preRead() && sym.content == ",") {
			now--;
			nextSym();		//','
			isExpression(func, exp);
			unit.setType(exp.type);
			values.push_back(unit);
		}
		now--;
	}
	//	outfile << "<值参数表>" << endl;
	if (values.size() != func.factors.size()) {
		errorOutput(sym.raw_num, 4);
	}
	else {
		for (int i = 0; i < values.size(); i++) {
			if (values[i].type != func.factors[i].type) {
				errorOutput(sym.raw_num, 5);
				break;
			}
		}
	}
	return 1;
}

int isSentense(Function& func)
{
	int needSemicn = 1;
	preRead();
	if (sym.content == "}") {				//读到语句列后的}
		now--;
		return 0;
	}
	else if (sym.content == ";") {			//空语句
		now--;
	}
	else if (sym.content == "return") {		//返回语句
		now--;
		func.setExistReturn();
		isReturnSent(func);
	}
	else if (sym.content == "scanf") {		//读语句
		now--;
		isScanfSent(func);
	}
	else if (sym.content == "printf") {		//写语句
		now--;
		isPrintfSent(func);
	}
	else if (sym.content == "if") {			//条件语句
		now--;
		isIfSent(func);
		needSemicn = 0;
	}
	else if (sym.content == "while" || sym.content == "for" || sym.content == "do") {
		now--;								//循环语句
		isLoopSent(func);
		needSemicn = 0;
	}
	else if (sym.content == "{") {
		now--;
		nextSym();		// "{"
		isSentenses(func);
		nextSym();		// "}"
		needSemicn = 0;
	}
	else if (sym.name == "IDENFR") {		//函数调用语句 || 赋值语句 
		preRead();
		needSemicn = 1;
		if (sym.content == "=" || sym.content == "[") {		//赋值语句
			now = now - 2;
			isAssignSent(func);
			needSemicn = 1;
		}
		else if (sym.content == "(") {		//函数调用语句
			now = now - 2;
			isReturnFuncSent();
		}
		else {
			now = now - 2;
			return 0;
		}
	}
	else {
		now--;
		return 0;
	}
	if (needSemicn) {
		checkSemicn();		// ;
	}
	//	outfile << "<语句>" << endl;
	return 1;
}

int isCondition(Function& func)
{
	string type1, type2;
	Expression exp;
	isExpression(func, exp);
	type1 = exp.type;
	preRead();
	if (sym.content == "<" || sym.content == "<=" || sym.content == ">" || sym.content == ">=" || sym.content == "!=" || sym.content == "==") {
		now--;
		isRelation();
		isExpression(func, exp);
		type2 = exp.type;
		if (type1 == "char" || type2 == "char")
		{
			errorOutput(sym.raw_num, 6);
		}
	}
	else {
		now--;
	}
	//	outfile << "<条件>" << endl;
	return 1;
}

int isRelation()
{
	nextSym();			// 关系运算符
	return 1;
}

int isLoopSent(Function& func)
{
	preRead();
	Expression exp;
	Unit unit;
	if (sym.content == "while") {
		now--;
		nextSym();
		nextSym();		//'('
		isCondition(func);
		checkRParent();		//')'
		isSentense(func);
	}
	else if (sym.content == "for") {
		now--;
		nextSym();
		nextSym();			//'('
		isIdenti(unit);
		nextSym();			//'='
		isExpression(func, exp);
		checkSemicn();			//';'
		isCondition(func);
		checkSemicn();			//';'
		isIdenti(unit);
		nextSym();			//'='
		isIdenti(unit);
		nextSym();			//'(+|-)'
		isStepLen();
		checkRParent();			//')'
		isSentense(func);
	}
	else if (sym.content == "do") {
		now--;
		nextSym();
		isSentense(func);
		preRead();
		if (sym.content != "while") {
			errorOutput(sym.raw_num, 14);
			now--;
		}
		else {
			now--;
			nextSym();		// while
		}
		nextSym();		//'('
		isCondition(func);
		checkRParent();		//')'
	}
	else {
		now--;
		return 0;
	}
	//	outfile << "<循环语句>" << endl;
	return 1;
}

int isStepLen()
{
	Unit unit;
	preRead();
	if (sym.name == "INTCON") {
		now--;
		isUnSignInt(unit);
		//		outfile << "<步长>" << endl;
		return 1;
	}
	else {
		now--;
		return 0;
	}
}

int isIfSent(Function& func)
{
	nextSym();			//'if'
	nextSym();			//'('
	isCondition(func);
	checkRParent();			//')'
	isSentense(func);
	while (preRead() && sym.content == "else") {
		now--;
		nextSym();		//'else'
		isSentense(func);
	}
	now--;
	//	outfile << "<条件语句>" << endl;
	return 1;
}

int isPrintfSent(Function& func)
{
	Expression exp;
	nextSym();
	nextSym();		// '('
	isChars();
	if (preRead() && sym.content == ",") {
		now--;
		nextSym();
	}
	else {
		now--;
	}
	isExpression(func, exp);
	checkRParent();		// ')'
//	outfile << "<写语句>" << endl;
	return 1;
}

int isScanfSent(Function& func)
{
	Unit unit;
	nextSym();		// scanf
	nextSym();		//'('
	isIdenti(unit);
	while (preRead() && sym.content == ",") {
		now--;
		nextSym();
		isIdenti(unit);
	}
	now--;
	checkRParent();		// ')'
//	outfile << "<读语句>" << endl;
	return 1;
}

int isReturnSent(Function& func)
{
	nextSym();			// return
	if (preRead() && sym.content == "(") {
		now--;
		nextSym();
		Expression expression;
		isExpression(func, expression);
		if (!func.hasReturn)
		{
			errorOutput(sym.raw_num, 7);
		}
		//if (func.hasReturn && expression.type != func.type) {			//  
		//	if (expression.type != "")
		//	{
		//		errorOutput(sym.raw_num, 8);			/////////////////////////////////
		//	}
		//	//			if (func.type == "")
		//}
		checkRParent();
	}
	else {
		if (func.hasReturn) {
			errorOutput(sym.raw_num, 8);
		}
		now--;
	}
	//		outfile << "<返回语句>" << endl;
	return 1;
}

int isChars()
{
	if (preRead() && sym.name == "STRCON") {
		now--;
		nextSym();
		//		outfile << "<字符串>" << endl;
		return 1;
	}
	else {
		now--;
		return 0;
	}
}

int isReturnFuncSent()
{
	Unit unit;
	Function func;
	isIdenti(unit);
	func = program.name2Func[sym.content];
	nextSym();			//'('
	isValueList(func);
	checkRParent();			//')'
//	outfile << "<有返回值函数调用语句>" << endl;
	return 1;
}

int isExpression(Function& func, Expression& tmp)
{
	Unit unit;
	preRead();
	if ((sym.content == "+" || sym.content == "-") && sym.name != "CHARCON") {
		now--;
		nextSym();
	}
	else {
		now--;
	}
	preRead();
	string str1 = sym.name;
	preRead();
	string str2 = sym.content;
	if (str1 == "CHARCON" && str2 == ")")				// str2 != "+" && str2 != "-" && str2 != "*" && str2 != "/"
	{
		now = now - 2;
		isChar(unit);
		tmp.setType("char");
		return 1;
	}
	else {
		now = now - 2;
		tmp.setType("int");
	}
	if (isTerm(func, unit)) {
		tmp.setType(unit.type);
		while (preRead() && (sym.content == "+" || sym.content == "-")) {
			now--;
			nextSym();			//+|-
			isTerm(func, unit);
			tmp.setType("int");
		}
		now--;
		//		outfile << "<表达式>" << endl;
		return 1;
	}
	else {
		return 0;
	}
}

int isTerm(Function& func, Unit& unit)
{
	Factor factor;
	if (isFactor(func, factor)) {
		unit.setType(factor.type);
		while (preRead() && (sym.content == "*" || sym.content == "/")) {
			now--;
			nextSym();			//* | /
			isFactor(func, factor);
			unit.setType("int");
		}
		now--;
		//		outfile << "<项>" << endl;
		return 1;
	}
	else {
		return 0;
	}
}

int isFactor(Function& func, Factor& factor)
{
	Unit unit;
	Expression exp;
	preRead();
	if (sym.name == "IDENFR") {
		if (program.name2Func.count(sym.content))
		{
			Function func = program.name2Func[sym.content];
			factor.setType(func.type);
			now--;
			isReturnFuncSent();
		}
		else {
			now--;
			isIdenti(unit);
			if (globalFunc.name2Unit.count(sym.content))
			{
				unit = globalFunc.name2Unit[sym.content];
				factor.setType(unit.type);
			}
			else if (func.name2Unit.count(sym.content))
			{
				unit = func.name2Unit[sym.content];
				factor.setType(unit.type);
			}
			if (preRead() && sym.content == "[") {
				now--;
				nextSym();			//'['
				isExpression(func, exp);
				if (exp.type != "int")
				{
					errorOutput(sym.raw_num, 9);
				}
				checkRBrack();			//']'
			}
			else {
				now--;
			}
		}
	}
	else if (sym.content == "(") {
		now--;
		nextSym();				//'('
		isExpression(func, exp);
		factor.setType("int");
		checkRParent();				//')'
	}
	else if (sym.name == "PLUS" || sym.name == "MINU" || sym.name == "INTCON") {
		now--;
		isSignInt(unit);
		factor.setType("int");
	}
	else if (sym.name == "CHARCON") {
		now--;
		isChar(unit);
		factor.setType("char");
	}
	else {
		now--;
		return 0;
	}
	//	outfile << "<因子>" << endl;
	return 1;
}

int isStateHead(Function& func)
{
	isTypeIdenti(func);
	isIdenti(func);		//标识符
//	outfile << "<声明头部>" << endl;
	return 1;
}

int isMainFunc()
{
	nextSym();			//void
	nextSym();			//main
	Function func;
	func.setName(sym.content);
	nextSym();			//'('
	checkRParent();			//')'
	nextSym();			//'{'
	isCompSentenses(func);
	nextSym();			//'}'
//	outfile << "<主函数>" << endl;
	return 1;
}


