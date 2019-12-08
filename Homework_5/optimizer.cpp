#include "Optimizer.h"
using namespace std;

map<int, BasicBlock> num2Block;
map<string, int> label2Num;
extern vector<MidCode> midCode;

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
}