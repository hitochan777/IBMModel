
#ifndef IBM2_H_
#define IBM2_H_

#include "IBM1.h"

typedef map<pair<pair<unsigned int,unsigned int>,pair<unsigned int,unsigned int> >,double> CATABLE;//count table for alignment count_a(k|i,I,K)
typedef map<pair<unsigned int,pair<unsigned int,unsigned int> >,double> TATABLE;//total table for alignment total_a(i,I,K)
typedef CATABLE ADTABLE;//alignment distribution table
typedef vector<pair<unsigned int,unsigned int> > SLP;//sencence length pairs (le,lf)'s

class IBM2:IBM1{
protected:
	CATABLE cat;
	TATABLE tat;
	ADTABLE adt;

public:
	IBM2(char* ffilename, char* efilename);
	~IBM2();
protected:

private:
	void EM();
	void initializeAlignmentDistributionTable();
	void initializeCountAlignmentTable();
	void initializeTotalAlignmentTable();
	SLP getSentenceLengthPairs();
};



#endif /* IBM2_H_ */
