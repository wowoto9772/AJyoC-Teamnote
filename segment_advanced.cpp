#include <stdio.h>
#include <limits.h>
 
#include <vector>
#include <algorithm>

#define ll long long
 
using namespace std;
 
class segment {
public:
    // find interval's maximum consecutive sum
    int n;
 
    class ele {
    public:
        ll le, ri, mi, ans;
        ele() {}
        ele(ll a, ll b, ll c, ll d) {
            le = a, ri = b, mi = c, ans = d;
        }
    };
 
    bool eQuals(const ele &a, const ele &b) {
        return a.ans == b.ans && a.le == b.le && a.ri == b.ri && a.mi == b.mi;
    }
 
    ele minV;
 
    vector <ele> t;
 
    segment(vector <ll> &I) {
        n = I.size();
        t.resize(4 * n + 1);
        minV = { LLONG_MIN / 2, LLONG_MIN / 2, LLONG_MIN / 2, LLONG_MIN / 2 };
        init(I, 1, 0, n - 1);
    }
 
    void init(vector <ll> &I, int x, int xl, int xr) {
        if (xl == xr) {
            t[x].le = t[x].ri = t[x].mi = t[x].ans = I[xl];
        }
        else {
            int m = (xl + xr) / 2;
 
            int le = x << 1;
            int ri = le + 1;
 
            init(I, le, xl, m);
            init(I, ri, m + 1, xr);
 
            t[x].ri = max(t[le].ri + t[ri].mi, t[ri].ri);
            t[x].le = max(t[le].mi + t[ri].le, t[le].le);
            t[x].mi = t[le].mi + t[ri].mi;
            t[x].ans = max({ t[le].ri + t[ri].le, t[le].ans, t[ri].ans, t[x].le, t[x].ri });
        }
    }
 
    void update(int idx, ll val, int x, int xl, int xr) {
        if (idx < xl || xr < idx)return;
        else if (xl == idx && idx == xr) {
            t[x].ri += val;
            t[x].le += val;
            t[x].mi += val;
            t[x].ans += val;
        }
        else {
 
            int m = (xl + xr) / 2;
 
            int le = x << 1;
            int ri = le | 1;
 
            update(idx, val, le, xl, m);
            update(idx, val, ri, m + 1, xr);
 
            t[x].ri = max(t[le].ri + t[ri].mi, t[ri].ri);
            t[x].le = max(t[le].mi + t[ri].le, t[le].le);
            t[x].mi = t[le].mi + t[ri].mi;
            t[x].ans = max({ t[le].ri + t[ri].le, t[le].ans, t[ri].ans, t[x].le, t[x].ri });
        }
    }
 
    void update(int idx, ll val) {
        update(idx, val, 1, 0, n - 1);
    }
 
    ele query(int il, int ir, int x, int xl, int xr) {
 
        if (ir < xl || xr < il) {
            return minV;
        }
        else if (il <= xl && xr <= ir) {
            return t[x];
        }
        else {
            int m = (xl + xr) / 2;
 
            int _le = x << 1;
            int _ri = _le | 1;
 
            ele le = query(il, ir, _le, xl, m);
            ele ri = query(il, ir, _ri, m + 1, xr);
 
            ele ret;
 
            // validation
            if (eQuals(le, minV))ret = ri;
            else if (eQuals(ri, minV))ret = le;
            else {
                ret.le = max(le.le, le.mi + ri.le);
                ret.ri = max(ri.ri, ri.mi + le.ri);
                ret.mi = le.mi + ri.mi;
                ret.ans = max({ le.ri + ri.le, le.ans, ri.ans, ret.le, ret.ri });
            }
 
            return ret;
        }
    }
 
    ll query(int il, int ir) {
        return query(il, ir, 1, 0, n - 1).ans;
    }
};