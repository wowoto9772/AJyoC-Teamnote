#include <stdio.h>

#include <vector>
#include <algorithm>

using namespace std;


class Segment { // interval update (lgN)
public:
	int S;
	vector <int> t, a;

	Segment(const vector <int> &Y) {
		S = Y.size();
		t.resize(S * 2);
		a.resize(S * 2);
		init(Y, 1, 0, S-1);
	}

	void init(const vector <int> &y, int x, int xl, int xr) {
		if (xl == xr) {
			t[x] = y[xl];
			return;
		}
		else {
			int m = (xl + xr) / 2;
			init(y, x << 1, xl, m);
			init(y, (x << 1) | 1, m + 1, xr);
			t[x] = t[x << 1] + t[(x << 1) | 1];
			return;
		}
	}


	void update(int il, int ir, int v, int x, int xl, int xr) {

		if (il > xr || ir < xl)return;

		if(il <= xl && xr <= ir)c[x] += v;
		else{
			int m = (xl + xr) / 2;
			update(il, ir, v, x << 1, xl, m);
			update(il, ir, v, (x << 1) | 1, m + 1, xr);
		}

		if(xl < xr)t[x] = t[x<<1] + t[(x<<1)|1] + c[x<<1];
		else if(xl == xr)t[x] += c[x];

	}

	void update(int il, int ir, int v) {
		update(il, ir, v, 1, 0, S - 1);
	}

	int query(int il, int ir, int x, int xl, int xr) {

		if (il > xr || ir < xl)return 0;

		if (il <= xl && xr <= ir)return t[x];
		else {
			int m = (xl + xr) / 2;
			return query(il, ir, x << 1, xl, m) + query(il, ir, (x << 1) | 1, m + 1, xr);
		}

	}

	int query(int il, int ir) {
		return query(il, ir, 1, 0, S - 1);
	}

};
