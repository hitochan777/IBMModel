#include "IBM1.h"

int main(int argc,char** argv){
	string output = "output.txt";
	//IBM1 ibm1(argv[1], argv[2]);
	//IBM1 ibm1("toy.de","toy.en");
	//IBM1 ibm1("toy2.ge","toy2.en");
	IBM1 ibm1("fr-en.tiny.fr","fr-en.tiny.fr");
	//ibm1.showTranslationTable();
	ibm1.writeTranslationTableToFile(output);
	return 0;
}



