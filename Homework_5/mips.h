#include"Class.h"
#include"Source.h"


void mkGlobalOffset();
void mkFuncOffset(Function func);
void Add(string name1, string name2, string name3);
void Minus(string name1, string name2, string name3);
void Mult(string name1, string name2, string name3);
void Div(string name1, string name2, string name3);
void lwData(string name, string regName);
void swData(string name, string regName);
bool isNum(string str);
void basicOp();
void controller();
string getReg(int i);
int nextMidCode();