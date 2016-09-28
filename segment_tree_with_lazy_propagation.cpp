#include <stdio.h>

#include <vector>

#define ll long long

using namespace std;

class Segment { // interval update (lgN) with lazy propagation

				// (lgN)*(lgN)
public:

	int S;
	vector <ll> c, my, lz;

	int added;

	// make complete tree
	Segment(const vector<ll> &y, int added_) {
		added = added_;
		S = y.size();
		c.resize(S * 2);
		my.resize(S * 2);
		lz.resize(S * 2); // lazy propagation
		init(y, 1, 0, S - 1);
	}

	void init(const vector <ll> &y, int x, int xl, int xr) {
		if (xl < xr) {
			int m = (xl + xr) / 2;
			init(y, x << 1, xl, m);
			init(y, (x << 1) | 1, m + 1, xr);
			c[x] = c[x << 1] + c[(x << 1) | 1];
			my[x] = my[x << 1] + my[(x << 1) | 1];
		}
		else {
			my[x] = y[xl];
			if (xl >= S - added)c[x] = 0;
			else
				c[x] = 1;
		}
	}

	void update(int il, int ir, ll v, int x, int xl, int xr) {

		if (il > xr || ir < xl)return;

		if (il <= xl && xr <= ir) {

			lz[x] += v;

		}
		else {
			int m = (xl + xr) / 2;

			if (lz[x]) {
				lz[x << 1] += lz[x];
				lz[(x << 1) | 1] += lz[x];
				lz[x] = 0;
			}

			update(il, ir, v, x << 1, xl, m);
			update(il, ir, v, (x << 1) | 1, m + 1, xr);

			my[x] = my[x << 1] + (ll)(c[x << 1] * lz[x << 1]) + my[(x << 1) | 1] + (ll)(c[(x << 1) | 1] * lz[(x << 1) | 1]);
		}

	}

	void update(int il, int ir, ll v) {
		update(il, ir, v, 1, 0, S - 1);
	}

	ll query(int il, int ir, int x, int xl, int xr) {

		if (il > xr || ir < xl) return 0;

		if (il <= xl && xr <= ir) {
			return my[x] + (ll)(c[x] * lz[x]);
		}
		else {

			if (lz[x]) {
				lz[x << 1] += lz[x];
				lz[(x << 1) | 1] += lz[x];
				lz[x] = 0;
			}

			int m = (xl + xr) / 2;
			ll out = ((query(il, ir, x << 1, xl, m)) + (query(il, ir, (x << 1) | 1, m + 1, xr)));

			my[x] = my[x << 1] + (ll)(c[x << 1] * lz[x << 1]) + my[(x << 1) | 1] + (ll)(c[(x << 1) | 1] * lz[(x << 1) | 1]);

			return out;
		}
	}

	ll query(int il, int ir) {
		return query(il, ir, 1, 0, S - 1);
	}

};