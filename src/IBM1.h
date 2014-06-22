#ifndef IMB1_H_
#define IMB1_H_

#include "common.h"
//#define DEBUG

#define NULLWORD " "
#define LIMIT 0.0000001

using namespace std;

typedef pair<string, string> SSP;
typedef set<string> SS;
typedef map<SSP, double> TTable; //Translation table
typedef map<SSP, double> CTable; //Count table
typedef map<string, double> TotalTable;
typedef pair<vector<string>,vector<string> > SP; //sentence pairs (e's, f's)

class IBM1 {

protected:
	TTable t;
	CTable ct;
	TotalTable tt;
	ifstream ffin, efin;
	SS fs;
	SS es;
public:
	IBM1(char* ffilename, char* efilename);

	~IBM1();

	void showTranslationTable();

	void showCountTable();

	void showTotalTable();

	void showWordsInSet(string which);

	void writeTranslationTableToFile(string filename);

	double getTranslationProbability(string from, string to);

	void writeTranslationTableToFile(string filename, string word);


protected:

	void writeTranslationTable(ostream &s);

	void writeTranslationTable(ostream &s, string word);

	void EM();

	void fsrefresh();

	SP getSentencePair();

	void getUniqueWords();

	void initializeTranslationTable();

	void initializeCountTable();

	void initializeTotalTable();

};
#endif /* IMB1_H_ */
