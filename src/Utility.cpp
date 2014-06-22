#include "Utility.h"

ui Utility::split(const string &txt, char ch) {
	vector<string> strs;
	ui pos = txt.find(ch);
	ui initialPos = 0;
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

ui Utility::split(const string &txt, vector<string> &strs, char ch) {
	ui pos = txt.find(ch);
	ui initialPos = 0;
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
