#include "IBM1.h"

int main(){
	string output = "output.txt";
	IBM1 ibm1(argv[1], argv[2]);
	//ibm1.showTranslationTable();
	ibm1.writeTranslationTableToFile(output);
	return 0;
}



