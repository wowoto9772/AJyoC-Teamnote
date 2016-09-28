#include <stdio.h>

#include <vector>

#include <algorithm>

using namespace std;

#define NMAX 10003

vector<int> a[NMAX];

bool c[NMAX];

int low[NMAX];

int num[NMAX];

int parent[NMAX];

int cnt = 0;

bool cut[NMAX];

void dfs(int x) {

    c[x] = true;

    num[x] = ++cnt;

    low[x] = cnt;

    int children = 0;

    for (int i = 0; i < a[x].size(); i++) {

        int y = a[x][i];

        if (c[y] == false) {

            children += 1;

            parent[y] = x;

            dfs(y);

            low[x] = min(low[x], low[y]);

            if (!parent[x] && children >= 2) {

                cut[x] = true;

            }

            if (parent[x] && low[y] >= num[x]) {

                cut[x] = true;

            }

        }
        else if (y != parent[x]) {

            low[x] = min(low[x], num[y]);

        }

    }

}

int main() {

    int n, m;

    scanf("%d %d", &n, &m);

    while (m--) {

        int u, v;

        scanf("%d %d", &u, &v);

        a[u].push_back(v);

        a[v].push_back(u);

    }

    for (int i = 1; i <= n; i++) {

        if (c[i] == false) {

            dfs(i);

        }

    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {

        if (cut[i]) {

            ans += 1;

        }

    }

    printf("%d\n", ans);

    for (int i = 1; i <= n; i++) {

        if (cut[i]) {

            printf("%d ", i);

        }

    }

    return 0;

}

