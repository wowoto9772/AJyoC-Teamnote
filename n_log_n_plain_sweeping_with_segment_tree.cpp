#include <stdio.h>
#include <limits.h>
 
#include <vector>
#include <algorithm>
 
#define ll long long
 
using namespace std;
 
struct rect {
    ll x, y, y2;
    int f;
    bool operator<(const rect &X)const {
        if (x == X.x) {
            if (y == X.y)return f < X.f;
            return y < X.y;
        }
        return x < X.x;
    }
}I[400003];
 
class Segment { // interval update (lgN)
public:
    int S;
    vector <ll> t;
    vector <int> c;
    vector <int> y;
 
    Segment(const int &n, const vector <int> &Y) {
        S = n;
        t.resize(S * 2);
        c.resize(S * 2);
        y = Y;
    }
 
    void update(int il, int ir, int v, int x, int xl, int xr) {
        if (il > xr || ir < xl)return;
        if (il <= xl && xr <= ir)c[x] += v;
        else {
            int m = (xl + xr) / 2;
            update(il, ir, v, x * 2, xl, m);
            update(il, ir, v, x * 2 + 1, m + 1, xr);
        }
        t[x] = 0;
        if (c[x] > 0) { 
            // completely included
            t[x] = y[xr] - y[xl];
        }
        else if (!c[x] && xl < xr) {
            // search interval
            t[x] = t[x * 2] + t[x * 2 + 1];
        }
    }
 
    ll sum() {
        return t[1];
    }
};
 
int main() {
 
    int n;
    scanf("%d", &n);
 
    int top = 0;
 
    vector <int> y;
 
    for (int i = 1; i <= n; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &c, &b, &d);
        I[top].x = a, I[top].y = b, I[top].y2 = d, I[top].f = 1;
        top++;
        I[top].x = c, I[top].y = b, I[top].y2 = d, I[top].f = -1;
        top++;
        y.push_back(b);
        y.push_back(d);
    }
 
    sort(y.begin(), y.end());
    y.resize(unique(y.begin(), y.end()) - y.begin());
    int a = y.size();
 
    for (int i = 0; i < a; i++)y.push_back(y[i]);
 
    ll x = 1;
    y.push_back(-1);
    a = y.size();
    while (x < a)x <<= 1;
    for (ll i = 1; i <= x - a; i++)y.push_back(INT_MAX);
 
    sort(y.begin(), y.end());
    sort(I, I + top);
 
    Segment tree(y.size(), y);
 
    int p = I[0].x;
    ll ans = 0;
 
    for (int i = 0; i < top; i++) {
 
        ans += (I[i].x - p) * tree.sum();
 
        int m = upper_bound(y.begin(), y.end(), I[i].y) - y.begin();
        m--; // 2 (2)
 
        int m2 = lower_bound(y.begin(), y.end(), I[i].y2) - y.begin(); // (3) 3
 
        tree.update(m, m2, I[i].f, 1, 0, y.size() - 1);
        p = I[i].x;
    }
 
    printf("%lld\n", ans);
}
 
// -1 2 / 2 3 / 3 5 / 5 8 / 8 15 / INT_MAX >>>>>>