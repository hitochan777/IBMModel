#ifndef IMB1_H_
#define IMB1_H_

#include "common.h"
#include "Utility.h"
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

	void setTranslationProbability(string e,string f,double prob);

	double getTranslationProbability(string e,string f);

	void setWordCount(string e, string f, double prob);

	double getWordCount(string e, string f);

	void setWordTotal(string f,double val);

	double getWordTotal(string f);
};
#endif /* IMB1_H_ */
