
#ifndef IBM2_H_
#define IBM2_H_

#include "IBM1.h"

typedef map<pair<pair<int,int>,pair<int,int> >,double> CATABLE;//count table for alignment
typedef map<pair<int,pair<int,int> >,double> TATABLE;//totale table for alignment

class IBM2:IBM1{
protected:
	CATABLE cat;
	TATABLE tat;
public:
	IBM2(char* ffilename, char* efilename);
	~IBM2();
protected:

private:
	void EM();
	void getInitializedCountAlignmentTable();
	void getInitializedTotalAlignmentTable();
};



#endif /* IBM2_H_ */
