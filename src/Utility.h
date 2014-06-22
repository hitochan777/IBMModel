#ifndef UTILITY_H_
#define UTILITY_H_

#include <string>
#include <vector>

using namespace std;

class Utility {
public:
	static unsigned int split(const string &txt, char ch);
	static unsigned int split(const string &txt, vector<string> &strs, char ch);
};

#endif /* UTILITY_H_ */
