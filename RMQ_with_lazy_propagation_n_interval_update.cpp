class Segment { // interval update (lgN) with lazy propagation

	// (lgN)*(lgN)
public:

	int S;
	vector <int> c, mx, lz;

	Segment(int s) {
		S = s;
		mx.resize((S + 1) * 4); // max
		lz.resize((S + 1) * 4); // lazy propagation
	}

	void update(int il, int ir, int v, int x, int xl, int xr) {

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

			mx[x] = max(mx[x << 1] + lz[x << 1], mx[(x << 1) | 1] + lz[(x << 1) | 1]);
		}

	}

	void update(int il, int ir, int v) {
		update(il, ir, v, 1, 0, S);
	}

	int query(int il, int ir, int x, int xl, int xr) {

		if (il > xr || ir < xl)return INT_MIN;

		if (il <= xl && xr <= ir)return mx[x] + lz[x];
		else {

			if(lz[x]){
				lz[x<<1] += lz[x];
				lz[(x<<1)|1] += lz[x];
				lz[x] = 0;
			}

			int m = (xl + xr) / 2;
			int out = max(query(il, ir, x << 1, xl, m), query(il, ir, (x << 1) | 1, m + 1, xr));
			mx[x] = max(mx[x << 1] + lz[x << 1], mx[(x << 1) | 1] + lz[(x << 1) | 1]);			

			return out;
		}

	}

	int query(int il, int ir) {
		return query(il, ir, 1, 0, S);
	}

};