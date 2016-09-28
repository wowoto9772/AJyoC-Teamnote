#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN 500005

int N;
int SA[MAXN], lcp[MAXN];
char S[MAXN];

void SuffixArray()
{
    int i, j, k;
    int m = 26;
    vector <int> cnt(max(N, m) + 1, 0), x(N + 1, 0), y(N + 1, 0);
    for (i = 1; i <= N; i++) cnt[x[i] = S[i] - 'a' + 1]++;
    for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (i = N; i; i--) SA[cnt[x[i]]--] = i;

    for (int len = 1, p = 1; p<N; len <<= 1, m = p) {
        for (p = 0, i = N - len; ++i <= N;) y[++p] = i;
        for (i = 1; i <= N; i++) if (SA[i] > len) y[++p] = SA[i] - len;
        for (i = 0; i <= m; i++) cnt[i] = 0;
        for (i = 1; i <= N; i++) cnt[x[y[i]]]++;
        for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (i = N; i; i--) SA[cnt[x[y[i]]]--] = y[i];
        swap(x, y); p = 1; x[SA[1]] = 1;
        for (i = 1; i<N; i++)
            x[SA[i + 1]] = SA[i] + len <= N && SA[i + 1] + len <= N && y[SA[i]] == y[SA[i + 1]] && y[SA[i] + len] == y[SA[i + 1] + len] ? p : ++p;
    }
}

void LCP()
{
    int i, j, k = 0;
    vector <int> rank(N + 1, 0);
    for (i = 1; i <= N; i++) rank[SA[i]] = i;
    for (i = 1; i <= N; lcp[rank[i++]] = k)
        for (k ? k-- : 0, j = SA[rank[i] - 1]; S[i + k] == S[j + k]; k++);
}

int main()
{
    int i;
    scanf("%s", S + 1); N = strlen(S + 1);

    SuffixArray(); LCP();

    for (i = 1; i <= N; i++) printf("%d ", SA[i]); 

    printf("\n");

    for (i = 2; i <= N; i++) printf(" %d", lcp[i]); 

}
