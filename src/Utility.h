#ifndef UTILITY_H_
#define UTILITY_H_

#include "common.h"

using namespace std;

class Utility {
public:
	static ui split(const string &txt, char ch);
	static ui split(const string &txt, vector<string> &strs, char ch);
};

#endif /* UTILITY_H_ */
