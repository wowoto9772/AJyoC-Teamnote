#include <stdio.h>

#include <vector>

#include <algorithm>

using namespace std;

#define NMAX 100003

vector <int> a[NMAX];

bool c[NMAX];

int low[NMAX];

int dfn[NMAX];

int parent[NMAX];

int cnt = 0;

bool cut[NMAX];

vector < pair<int, int> > bridge;

void dfs(int x) {

    c[x] = true;

    dfn[x] = ++cnt;

    low[x] = cnt;

    int children = 0;

    for (int i = 0; i < a[x].size(); i++) {

        int y = a[x][i];

        if (!c[y]) {

            children += 1;

            parent[y] = x;

            dfs(y);

            low[x] = min(low[x], low[y]);

            if (!parent[x] && children >= 2) {

                cut[x] = true;

            }

            if (parent[x] && low[y] >= dfn[x]) {

                cut[x] = true;

            }

            if (low[y] > dfn[x]) {
                bridge.emplace_back(x, y);
            }

        }
        else if (y != parent[x]) {

            low[x] = min(low[x], dfn[y]);

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

    printf("%d\n", bridge.size());

    for (int i = 0; i < bridge.size(); i++) {
        if (bridge[i].first > bridge[i].second) {
            swap(bridge[i].first, bridge[i].second);
        }
    }

    sort(bridge.begin(), bridge.end());

    for (int i = 0; i < bridge.size(); i++) {
        printf("%d %d\n", bridge[i].first, bridge[i].second);
    }

    return 0;

}
