#include "IBM1.h"

IBM1::IBM1(char* ffilename, char* efilename) {
	ffin.open(ffilename);
	efin.open(efilename);
	getUniqueWords();
	initializeTranslationTable();
	EM();
}

IBM1::~IBM1() {
	ffin.close();
	efin.clear();
}

void IBM1::showTranslationTable() {
	writeTranslationTable(cout);
}

void IBM1::showCountTable() {
	for (CTable::iterator it = ct.begin(); it != ct.end(); ++it) {
		cout << it->first.second << "->" << it->first.first << ":" << it->second
				<< endl;
	}
	return;
}

void IBM1::showTotalTable() {
	for (TotalTable::iterator it = tt.begin(); it != tt.end(); ++it) {
		cout << it->first << ":" << it->second << endl;
	}
	return;
}

void IBM1::showWordsInSet(string which) {
	SS s;
	if (which == "f") {
		s = fs;
	} else if (which == "e") {
		s = es;
	} else {
		return;
	}
	for (SS::iterator it = s.begin(); it != s.end(); ++it) {
		cout << *it << endl;
	}
	return;
}

void IBM1::writeTranslationTableToFile(string filename) {
	ofstream ofs(filename.c_str());
	writeTranslationTable(ofs);
	ofs.close();
}

void IBM1::writeTranslationTableToFile(string filename, string word) {
	ofstream ofs(filename.c_str());
	writeTranslationTable(ofs, word);
	ofs.close();
}

void IBM1::writeTranslationTable(ostream &s) {
	for (TTable::iterator it = t.begin(); it != t.end(); ++it) {
		if (it->second < 1 + LIMIT && it->second > 1 - LIMIT) {
			s << it->first.second << "->" << it->first.first << ":"
					<< it->second << endl;
		}
	}
	return;
}

void IBM1::writeTranslationTable(ostream &s, string word) {
	for (TTable::iterator it = t.begin(); it != t.end(); ++it) {
		if (it->second < 1 + LIMIT && it->second > 1 - LIMIT) {
			if (it->first.second == word) {
				s << it->first.second << "->" << it->first.first << ":"
						<< it->second << endl;
			}
		}
	}
	return;
}

void IBM1::EM() {
	int n = 0;
	double LL[2] = { 0 }; //log likelihood
	//string f, e;
	pair<vector<string>, vector<string> > spair;

	while (n < 2 || LL[(n - 1) % 2] < LL[n % 2]) { //while not converged

		n++;
		LL[n % 2] = 0;

		initializeCountTable(); //init every element of count table to zero
		initializeTotalTable();
		fsrefresh();
		while (true) {
			spair = getSentencePair();
			if (spair.first.empty() || spair.second.empty()) {
				break;
			}
			vector<double> z;
			vector<string> fv(spair.second), ev(spair.first);

			for (unsigned int j = 0; j < ev.size(); ++j) {
				double tmpZ = 0.0;
				for (unsigned int k = 0; k < fv.size(); ++k) {
					SSP p(ev[j], fv[k]);
					tmpZ += t[p];
				}
				//cout << tmpZ << endl;
				z.push_back(tmpZ);
			}

			int i = 0;
			for (unsigned int j = 0; j < ev.size(); ++j) {
				for (unsigned int k = 0; k < fv.size(); ++k) {
					SSP p(ev[j], fv[k]);
					double newval = this->getWordCount(ev[j], fv[k])
							+ this->getTranslationProbability(ev[j], fv[k])
									/ z[i];
					this->setWordCount(ev[j], fv[k], newval);
					newval = this->getWordTotal(fv[k])
							+ this->getTranslationProbability(ev[j], fv[k])
									/ z[i];
					this->setWordTotal(fv[k], newval);
				}
				LL[n % 2] += log(z[i]);
				i++;
			}
		}

		for (SS::iterator fit = fs.begin(); fit != fs.end(); ++fit) {
			for (SS::iterator eit = es.begin(); eit != es.end(); ++eit) {
				double newval = this->getWordCount(*eit, *fit)
						/ this->getWordTotal(*fit);
				this->setTranslationProbability(*eit, *fit, newval);
			}
		}
		//cout << LL[n % 2] << endl;
		//cout<<LL[1]<<endl;
	}
	//cout<<n<<endl;
	return;
}

void IBM1::fsrefresh() {
	ffin.clear();
	ffin.seekg(0);
	efin.clear();
	efin.seekg(0);
}

SP IBM1::getSentencePair() {
	vector<string> fv, ev;
	string es, fs;
	if (getline(ffin, fs) && getline(efin, es)) {
		istringstream fss(fs), ess(es);
		string word;
		fv.push_back(NULLWORD);
		while (fss >> word) {
			fv.push_back(word);
		}
		while (ess >> word) {
			ev.push_back(word);
		}
	}
	pair<vector<string>, vector<string> > spair(ev, fv);

	return spair;
}

void IBM1::getUniqueWords() {
	string word;
	while (ffin >> word) {
		fs.insert(word);
	}
	while (efin >> word) {
		es.insert(word);
	}
	fs.insert(NULLWORD); //NULL
	return;
}

void IBM1::initializeTranslationTable() {
	int elen = es.size();
	for (SS::iterator fit = fs.begin(); fit != fs.end(); ++fit) {
		for (SS::iterator eit = es.begin(); eit != es.end(); ++eit) {
			this->setTranslationProbability(*eit, *fit, 1.0 / elen);
		}
	}

	return;
}

void IBM1::setTranslationProbability(string e, string f, double prob) {
	SSP p(e, f);
	t[p] = prob;
	return;
}

double IBM1::getTranslationProbability(string e, string f) {
	SSP p(e, f);
	return t[p];
}

void IBM1::setWordCount(string e, string f, double val) {
	SSP p(e, f);
	ct[p] = val;
	return;
}

double IBM1::getWordCount(string e, string f) {
	SSP p(e, f);
	return ct[p];
}

void IBM1::setWordTotal(string f, double val) {
	tt[f] = val;
	return;
}

double IBM1::getWordTotal(string f) {
	return tt[f];
}

void IBM1::initializeCountTable() {
	for (TTable::iterator it = t.begin(); it != t.end(); ++it) {
		ct[it->first] = 0;
	}
	return;
}

void IBM1::initializeTotalTable() {
	for (SS::iterator it = fs.begin(); it != fs.end(); ++it) {
		tt[*it] = 0;
	}
	return;
}
