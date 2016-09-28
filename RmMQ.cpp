#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

class RmMQ{
public:
	int n;
	vector <int> rM, rm;

	RmMQ(vector <int> &I){
		n = I.size();
		rm.resize(4 * n + 1);
		rM.resize(4 * n + 1);
		init(I, 1, 0, n - 1, 1); // Range Maximum Query
		init(I, 1, 0, n - 1, 0); // Range Minimum Query
	} // init(O(2*n-1))

	int init(vector <int> &I, int x, int xl, int xr, int isMax){
		if (xl == xr){
			if (isMax)return rM[x] = I[xl];
			else{
				return rm[x] = I[xl];
			}
		}
		else{
			int m = (xl + xr) / 2;
			if (isMax){
				return rM[x] = max(init(I, x * 2, xl, m, isMax), init(I, x * 2 + 1, m + 1, xr, isMax));
			}
			else{
				return rm[x] = min(init(I, x * 2, xl, m, isMax), init(I, x * 2 + 1, m + 1, xr, isMax));
			}
		}
	}

	int query(int il, int ir, int x, int xl, int xr, int isMax){
		if (ir < xl || xr < il){
			if (isMax)return INT_MIN;
			else
				return INT_MAX;
		}
		else if (il <= xl && xr <= ir){
			if (isMax)return rM[x];
			else
				return rm[x];
		}
		else{
			int m = (xl + xr) / 2;
			if (isMax)return max(query(il, ir, x * 2, xl, m, isMax), query(il, ir, x * 2 + 1, m + 1, xr, isMax));
			else
				return min(query(il, ir, x * 2, xl, m, isMax), query(il, ir, x * 2 + 1, m + 1, xr, isMax));
		}
	}

	int query(int il, int ir, int isMax){
		return query(il, ir, 1, 0, n - 1, isMax);
	}

	int update(int p, int v, int x, int xl, int xr, int isMax){
		if (p < xl || xr < p){
			if (isMax)return rM[x];
			else
				return rm[x];
		}
		else if (xl == xr){
			if (isMax)return rM[x] = v;
			else
				return rm[x] = v;
		}
		else{
			int m = (xl + xr) / 2;
			if (isMax)return rM[x] = max(update(p, v, x * 2, xl, m, isMax), update(p, v, x * 2 + 1, m + 1, xr, isMax));
			else{
				return rm[x] = min(update(p, v, x * 2, xl, m, isMax), update(p, v, x * 2 + 1, m + 1, xr, isMax));
			}
		}
	}

	int update(int p, int v, int isMax){
		return update(p, v, 1, 0, n - 1, isMax);
	}
};