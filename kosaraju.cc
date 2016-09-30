struct kosaraju{

    vector < vector <int> > lnk[2];
    vector <int> stk, grp;
    vector <bool> vst;
    int n, top, gtop;

    vector < vector <int> > G;

    kosaraju(int _n):n(_n), stk(_n), grp(_n+1), vst(_n+1), top(0), gtop(0){
        lnk[0].resize(n+1);
        lnk[1].resize(n+1);
    }

    void addEdge(int a, int b){
        lnk[0][a].push_back(b);
        lnk[1][b].push_back(a);
    }

    void dfs(int t, int c){
        if(!t){
            if(vst[c]) return ;
            vst[c] = true;
        }else{
            if(grp[c]) return ;
            grp[c] = gtop;
        }
        for(int i=0; i<lnk[t][c].size(); i++){
            dfs(t, lnk[t][c][i]);
        }
        if(!t)stk[top++] = c;
    }

    void solve(){
        for(int i=1; i<=n; i++)dfs(0, i);
        for(int i=top-1; i>=0; i--){
            if(grp[stk[i]])continue;
            gtop++;
            dfs(1, stk[i]);
        }

        //G.resize(gtop+1);

        //for(int i=1; i<=n; i++){
        //    G[grp[i]].push_back(i);
        //}
    }

};
