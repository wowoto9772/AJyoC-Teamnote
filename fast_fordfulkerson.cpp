#include <stdio.h>
#include <memory.h>
#include <vector>
#include <algorithm>

using namespace std;

class fast_ford_fulkerson{
public:

	vector < bool > chk;
	vector < vector <int> > cap;

	int tot, src, snk;

	void setEdge(int a, int b, int k){
		cap[a][b] = k;
	}

	fast_ford_fulkerson(int tot_, int src_, int snk_){

		tot = tot_, src = src_, snk = snk_;

		chk.resize(tot);
		cap.resize(tot);

		for(int i=0; i < tot; i++)cap[i].resize(tot);

	}

	int dfs(int x) {

		if (chk[x])return 0;

		chk[x] = true;

		if (x == snk)return true;

		for (int i = 0; i < tot; i++) {
			if (cap[x][i] > 0) {
				if (dfs(i)) { 
					// exists augmenting path
					cap[x][i]--;
					cap[i][x]++;
					return true;
				}
			}
		}

		return false;

	}

	int Solve() {

		int ans = 0;

		while (true) {

			for(int i=0; i < tot; i++)chk[i] = false;

			if (!dfs(src)) {
				return ans;
			}

			ans++;
		}

		return ans;

	}

	// return maximum flow


};