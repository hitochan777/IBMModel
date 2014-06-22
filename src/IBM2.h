
#ifndef IBM2_H_
#define IBM2_H_

#include "IBM1.h"

typedef map<pair<pair<ui,ui>,pair<ui,ui> >,double> CATABLE;//count table for alignment count_a(k|i,I,K)
typedef map<pair<ui,pair<ui,ui> >,double> TATABLE;//total table for alignment total_a(i,I,K)
typedef CATABLE ADTABLE;//alignment distribution table
typedef vector<pair<ui,ui> > SLP;//sencence length pairs (le,lf)'s

class IBM2:IBM1{
protected:
	CATABLE cat;
	TATABLE tat;
	ADTABLE adt;
	SLP slp;

public:
	IBM2(char* ffilename, char* efilename);
	~IBM2();
protected:

private:
	void EM();
	void initializeAlignmentDistributionTable();
	void initializeCountAlignmentTable();
	void initializeTotalAlignmentTable();
	void getSentenceLengthPairs();
	double getAlignmentProbability(ui k, ui i, ui I, ui K);
	void setAlignmentProbability(ui k, ui i, ui I, ui K, double prob);
	double getTotalAlignment(ui j, ui le, ui lf);
	void setTotalAlignment(ui j, ui le, ui lf, double val);
	double getCountAlignment(ui k, ui i, ui I, ui K);
	void setCountAlignment(ui k, ui i, ui I, ui K, double prob);
};



#endif /* IBM2_H_ */
