#include "IBM2.h"

IBM2::IBM2(char* ffilename, char* efilename) :
		IBM1(ffilename, efilename) { //call constructor to base function
	initializeAlignmentDistributionTable();
	EM();
}

void IBM2::EM() {
	int n = 0;
	double LL[2] = { 0 }; //log likelihood
	pair<vector<string>, vector<string> > spair;

	while (n < 2 || LL[(n - 1) % 2] < LL[n % 2]) { //while not converged

		n++;
		LL[n % 2] = 0;

		initializeCountTable(); //init every element of count table to zero
		initializeTotalTable();
		initializeCountAlignmentTable();
		initializeTotalAlignmentTable();

		fsrefresh();
		int cnt = 0;
		while (true) {
			spair = getSentencePair();
			if (spair.first.empty() || spair.second.empty()) {
				break;
			}

			vector<double> z;
			vector<string> fv(spair.second), ev(spair.first);

			for (ui j = 0; j < ev.size(); ++j) {
				double tmpZ = 0.0;
				for (ui k = 0; k < fv.size(); ++k) {
					tmpZ += this->getAlignmentProbability(k, j, ev.size(),
							fv.size())
							* this->getTranslationProbability(ev[j], fv[k]);
				}
				z.push_back(tmpZ);
			}

			int i = 0;
			for (ui j = 0; j < ev.size(); ++j) {
				for (ui k = 0; k < fv.size(); ++k) {
					double p_jk_div_z = this->getAlignmentProbability(k, j,
							ev.size(), fv.size())
							* this->getTranslationProbability(ev[j], fv[k])
							/ z[i];
					this->setWordCount(ev[j], fv[k],
							this->getWordCount(ev[j], fv[k]) + p_jk_div_z);
					this->setWordTotal(fv[k],
							this->getWordTotal(fv[k]) + p_jk_div_z);
					this->setCountAlignment(k, j, ev.size(), fv.size(),
							this->getCountAlignment(k, j, ev.size(), fv.size())
									+ p_jk_div_z);
					this->setTotalAlignment(j, ev.size(), fv.size(),
							this->getTotalAlignment(j, ev.size(), fv.size())
									+ p_jk_div_z);

				}
				LL[n % 2] += log(z[i]);
				i++;
			}
			cnt++;
		}

		for (SS::iterator fit = fs.begin(); fit != fs.end(); ++fit) {
			for (SS::iterator eit = es.begin(); eit != es.end(); ++eit) {
				double newval = this->getWordCount(*eit, *fit)
						/ this->getWordTotal(*fit);
				this->setTranslationProbability(*eit, *fit, newval);
			}
		}

		for (ui i = 0; i < slp.size(); ++i) {
			ui le = slp[i].first;
			ui lf = slp[i].second;
			for (ui j = 0; j <= lf; ++j) {
				for (ui k = 1; k <= le; ++k) {
					this->setAlignmentProbability(j, k, le, lf,
							this->getCountAlignment(j, k, le, lf)
									/ this->getTotalAlignment(k, le, lf));
				}
			}
		}
		cout << LL[n % 2] << endl;
	}
	return;
}

void IBM2::initializeCountAlignmentTable() {
	for (ui i = 0; i < slp.size(); ++i) {
		ui le = slp[i].first;
		ui lf = slp[i].second;
		for (ui j = 0; j <= lf; ++j) {
			for (ui k = 1; k <= le; ++k) {
				setCountAlignment(j, k, le, lf, 0.0);
			}
		}
	}
	return;
}

void IBM2::initializeTotalAlignmentTable() {
	for (ui i = 0; i < slp.size(); ++i) {
		ui le = slp[i].first;
		ui lf = slp[i].second;
		for (ui j = 1; j <= le; ++j) {
			setTotalAlignment(j, le, lf, 0.0);
		}
	}
}

void IBM2::initializeAlignmentDistributionTable() {
	for (ui i = 0; i < slp.size(); ++i) {
		ui le = slp[i].first;
		ui lf = slp[i].second;
		for (ui j = 0; j <= lf; ++j) {
			for (ui k = 1; k <= le; ++k) {
				setAlignmentProbability(j, k, le, lf, 1.0 / (lf + 1));
			}
		}
	}
	return;
}

void IBM2::getSentenceLengthPairs() {
	ui le, lf;
	fsrefresh();
	string es, fs;
	if (getline(ffin, fs) && getline(efin, es)) {
		lf = Utility::split(fs, ' ');
		le = Utility::split(es, ' ');
		pair<ui, ui> p(le, lf);
		slp.push_back(p);
	}
	return;
}

double IBM2::getTotalAlignment(ui j, ui le, ui lf) {
	pair<ui, ui> p1(le, lf);
	pair<ui, pair<ui, ui> > p(j, p1);
	return tat[p];
}

void IBM2::setTotalAlignment(ui j, ui le, ui lf, double val) {
	pair<ui, ui> p1(le, lf);
	pair<ui, pair<ui, ui> > p(j, p1);
	tat[p] = val;
	return;
}

double IBM2::getCountAlignment(ui k, ui i, ui I, ui K) {
	pair<ui, ui> p1(I, K);
	pair<ui, ui> p2(i, k);
	pair<pair<ui, ui>, pair<ui, ui> > p(p2, p1);
	return cat[p];
}

void IBM2::setCountAlignment(ui k, ui i, ui I, ui K, double prob) {
	pair<ui, ui> p1(I, K);
	pair<ui, ui> p2(i, k);
	pair<pair<ui, ui>, pair<ui, ui> > p(p2, p1);
	cat[p] = prob;
	return;
}

double IBM2::getAlignmentProbability(ui k, ui i, ui I, ui K) {
	pair<ui, ui> p1(I, K);
	pair<ui, ui> p2(i, k);
	pair<pair<ui, ui>, pair<ui, ui> > p(p2, p1);
	return adt[p];
}

void IBM2::setAlignmentProbability(ui k, ui i, ui I, ui K, double prob) {
	pair<ui, ui> p1(I, K);
	pair<ui, ui> p2(i, k);
	pair<pair<ui, ui>, pair<ui, ui> > p(p2, p1);
	adt[p] = prob;
	return;
}
