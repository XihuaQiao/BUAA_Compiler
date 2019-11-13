#include"class.h"
using namespace std;

int main()
{
	outfile.open("error.txt", ios::out);
	outfile.close();
	outfile.open("error.txt", ios::app);
	getWord();
	isProgram();
	outfile.close();
	return 0;
}