char S[100003];
char T[200003];
int B[200003];

int main(){
    int n;
    scanf("%s", S+1);
    n = strlen(S+1);
    int p = 0, r = 0;
    // includes even length
    p = r = 0;
    for(int i=1; i<=n; i++){
        T[2*i-1] = '#';
        T[2*i] = S[i];
    }
    T[2*n+1] = '#';
    int m = 2 * n + 1;
    for(int i=1; i<=m; i++){
        if(i <= r)B[i] = min(B[2*p-i], r-i);
        else
            B[i] = 0;
        while(i-B[i]-1 > 0 && i+B[i]+1 <= m && T[i-B[i]-1] == T[i+B[i]+1])B[i]++;
        if(r < i+B[i])r = i+B[i], p = i;
    }
 
    int ans = 0;
    for(int i=1; i<=m; i++){
        ans = max(ans, B[i]);
    }
    printf("%d\n", ans);
}
