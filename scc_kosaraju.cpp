#include <stdio.h>

#include <vector>

using namespace std;

vector < vector <int> > lnk[2];

vector <int> stk, grp;

vector <bool> vst;

int top, gtop;

void dfs(int t, int c){
	if(!t){
		if(vst[c])return ;
		vst[c] = true;
	}else{
		if(grp[c])return ;
		grp[c] = gtop;
	}

	for(int i=0; i<lnk[t][c].size(); i++){
		dfs(t, lnk[t][c][i]);
	}

	if(!t)stk[top++] = c;
}

int main(){

	int n, m;
	scanf("%d %d", &n, &m);

	// n vertex, m edge

	stk.resize(n);
	grp.resize(n+1);
	vst.resize(n+1);

	for(int i=1; i<=m; i++){
		int a, b;
		scanf("%d %d", &a, &b);

		lnk[0][a].push_back(b);
		lnk[1][b].push_back(a);
	}

	for(int i=1; i<=n; i++)dfs(0, i);

	for(int i=top-1; i>=0; i--){
		if(grp[stk[i]])continue;
		gtop++;
		dfs(1, stk[i]);
	}

}
