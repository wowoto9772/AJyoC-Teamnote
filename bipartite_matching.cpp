#include <vector>

using namespace std;

class bipartite_matching {
public:

	int n;
	vector <bool> vst;
	vector <int> le, ri;
	vector < vector <bool> > lnk;

	bipartite_matching(int _n) { // zero_base

		n = _n;

		vst.resize(n);
		le.resize(n);
		ri.resize(n);
		lnk.resize(n);

		for (int i = 0; i < n; i++) {
			le[i] = ri[i] = -1;
			lnk[i].resize(n);
		}

	}

	void addEdge(int s, int a) {
		lnk[s][a] = true;
	}

	bool augmenting(int c) {

		if (vst[c])return false;

		vst[c] = true;

		for (int i = 0; i < n; i++) {
			if (lnk[c][i]) {
				if (ri[i] == -1 || augmenting(ri[i])) {
					ri[i] = c;
					le[c] = i;
					return true;
				}
			}
		}

		return false;

	}

	int solve() {

		int ret = 0;

		for (int i = 0; i < n; i++) {
			if (ri[i] == -1) { // not matched
				for (int j = 0; j < n; j++)vst[j] = false;
				ret += augmenting(i);
			}
		}

		return ret;

	}

};