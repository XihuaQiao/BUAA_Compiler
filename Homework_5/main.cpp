#include"Source.h"
using namespace std;

int main()
{
	outfile.open("mips.txt", ios::out);
	outfile.close();
	outfile.open("mips.txt", ios::app);
	getWord();
	isProgram();
	outfile.close();
	return 0;
}