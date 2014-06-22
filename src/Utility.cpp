#include "Utility.h"

unsigned int Utility::split(const string &txt, char ch) {
	vector<string> strs;
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != string::npos) { //npos is a constant value -1. this is used to check whether search has reached the end of the string.
		strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(
			txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

unsigned int Utility::split(const string &txt, vector<string> &strs, char ch) {
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != string::npos) { //npos is a constant value -1. this is used to check whether search has reached the end of the string.
		strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(
			txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}
