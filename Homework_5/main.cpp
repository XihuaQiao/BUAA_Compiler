#include"Source.h"
#include"mips.h"
#include"Optimizer.h"
using namespace std;
#include<iostream>

int main()
{
	extern ofstream outfile;
	extern vector<string>orders;
	outfile.open("output.txt", ios::out);
	outfile.close();
	outfile.open("output.txt", ios::app);
	getWord();
	isProgram();
	outfile.close();

	createBlocks();
	connectBlock();
	constOpt();
	outVerOne();

	controller();
	outfile.open("mips.txt", ios::out);
	outfile.close();
	outfile.open("mips.txt", ios::app);
	for (int i = 0; i < orders.size(); i++) {
		outfile << orders[i] << endl;
	}
	return 0;
}