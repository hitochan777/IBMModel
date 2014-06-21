#ifndef ALIGNMENTDISTRIBUTIONELEMENT_H_
#define ALIGNMENTDISTRIBUTIONELEMENT_H_

#ifndef COMMON_H_
#include "common.h"
#endif

class AlignmentDistributionElement{
private:
	int e;
	int f;
	int elen;
	int flen;
public:
	AlignmentDistributionElement(int e,int f,int elen,int flen):e(e),f(f),elen(elen),flen(flen){}

	bool operator<(const AlignmentDistributionElement& adise) const;
};

#endif /* ALIGNMENTDISTRIBUTIONELEMENT_H_ */
