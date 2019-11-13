#pragma once
#include"function.h"
#include<fstream>

string readUntil(char x, FILE* fp);
int isLetter(char x);
int isNum(char x);
int isSpWord(string word);
void isSpace();
void getWord();
int nextSym();
int preRead();

extern ofstream outfile;

class singleWord
{
public:
	string content;
	string name;
	int raw_num;
	bool noRSingle;
	bool noRDouble;
};

void errorOutput(int raw_num, int code);
int checkSemicn();
int checkRBrack();
int checkRepeat(Function& func, string name, int raw);
int isProgram();
int isConstDes(Function& tmp);
int isConstDef(Function& tmp);
int isAssignSent(Function& func);
int isSignInt(Unit& unit);
int isUnSignInt(Unit& unit);
int isIdenti(Unit& unit);
int isChar(Unit& unit);
int isVarDes(Function& func);
int isVarDef(Function& func);
int isTypeIdenti(Unit& unit);
int isReturnFuncDef();
int isNonReturnFuncDef();
int isFactorList(Function& func);
int isCompSentenses(Function& func);
int isSentenses(Function& func);
int isValueList(Function& func);
int isSentense(Function& func);
int isCondition(Function& func);
int isRelation();
int isLoopSent(Function& func);
int isStepLen();
int isIfSent(Function& func);
int isPrintfSent(Function& func);
int isScanfSent(Function& func);
int isReturnSent(Function& func);
int isChars();
int isReturnFuncSent();
int isExpression(Function& func, Expression& tmp);
int isTerm(Function& func, Unit& unit);
int isFactor(Function& func, Factor& factor);
int isStateHead(Function& func);
int isMainFunc();
