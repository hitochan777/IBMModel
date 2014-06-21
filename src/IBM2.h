
#ifndef IBM2_H_
#define IBM2_H_

#include "AlignmentDistributionElement.h"
#include "IBM1.h"

class IBM2:IBM1{
private:
public:
	IBM2(char* ffilename, char* efilename);
	~IBM2();
protected:

private:
	void EM();

};



#endif /* IBM2_H_ */
