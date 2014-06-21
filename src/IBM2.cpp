#include "IBM2.h"

IBM2::IBM2(char* ffilename, char* efilename):IBM1(ffilename,efilename){//call constructor to base function
	EM();
}

void IBM2::EM(){
	int n = 0;
	double LL[2] = { 0 }; //log likelihood
	string f, e;
	pair<vector<string>, vector<string> > spair;

	while (n < 2 || LL[(n - 1) % 2] < LL[n % 2]) { //while not converged

		n++;
		LL[n % 2] = 0;

		getInitializedCountTable(); //init every element of count table to zero
		getInitializedTotalTable();
		getInitializedCountAlignmentTable();
		getInitializedTotalAlignmentTable();

		fsrefresh();

		while (true) {
			spair = getSentencePair(f, e);
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
					ct[p] += t[p] / z[i];
					tt[fv[k]] += t[p] / z[i];
				}
				LL[n % 2] += log(z[i]);
				i++;
			}
		}

		for (SS::iterator fit = fs.begin(); fit != fs.end(); ++fit) {
			for (SS::iterator eit = es.begin(); eit != es.end(); ++eit) {
				SSP p(*eit, *fit);
				t[p] = ct[p] / tt[*fit];
			}
		}
		//cout << LL[n % 2] << endl;
	}
	return;
}

void IBM2::getInitializedCountAlignmentTable(){

}

void IBM2::getInitializedTotalAlignmentTable(){

}
