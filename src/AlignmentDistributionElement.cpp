#include "common.h"

class AlignmentDistributionElement{
private:
	int e;
	int f;
	int elen;
	int flen;
public:
	AlignmentDistributionElement(int e,int f,int elen,int flen):e(e),f(f),elen(elen),flen(flen){}

	bool operator<(const AlignmentDistributionElement& adise) const{
		return (e==f)?((f==elen)?(elen<flen):f<elen):e<f;
	}
};
