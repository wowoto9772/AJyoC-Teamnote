void make_data(int mod){
    nCm[0][0] = 1;
    for(int i=1; i<=mod; i++){
        nCm[i][0] = 1;
        for(int j=1; j<=i; j++){
            nCm[i][j] = (nCm[i-1][j-1] + nCm[i-1][j]) % mod;
        }
    }
}

/* nCm mod k (n&m big, k small) */
ll nCm_k(int n, int m, int k){ 

    vector <int> p, q;

    while(n){
        p.push_back(n%k);
        q.push_back(m%k);
        n /= k, m /= k;
    }

    make_data(k);

    ll ans = 1;
    for(int i=0; i<p.size(); i++){
        ans = (ans * nCm[p[i]][q[i]]) % k;
    }

    return ans;

}
