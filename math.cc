using ll = long long;
using VI = vector<int>;
using VII = vector< pair<int,int> >;
using VL = vector<ll>;
using VLL = vector< pair<ll,ll> >;
using PII = pair<int,int>;
using PLL = pair<ll, ll>;

int mod(int a, int b){
    return ((a%b)+b)%b;
}

int gcd(int a, int b){
    int m = 1;
    while(m){
        m = a % b;
        a = b;
        b = m;
    }
    return m;
}

int extended_gcd(int a, int b, int &x, int &y) {
    int xx = y = 0;
    int yy = x = 1;
    while (b) {
        int q = a / b;
        int t = b; b = a%b; a = t;
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;
}

/* Chinese remainder theorem (special case): find z such that
 * z % m1 = r1, z % m2 = r2.  Here, z is unique modulo M = lcm(m1, m2).
 * Return (z, M).  On failure, M = -1. */

PII chinese_remainder_theorem(int m1, int r1, int m2, int r2) {
    int s, t;
    int g = extended_gcd(m1, m2, s, t);
    if (r1%g != r2%g) return {0, -1};
    return {mod(s*r2*m1 + t*r1*m2, m1*m2) / g, m1*m2 / g};
}

/* Chinese remainder theorem: find z such that
 * z % m[i] = r[i] for all i.  Note that the solution is
 * unique modulo M = lcm_i (m[i]).  Return (z, M). On 
 * failure, M = -1. Note that we do not require the a[i]'s
 * to be relatively prime. */

PII chinese_remainder_theorem(const VI &m, const VI &r) {
    PII ret = make_pair(r[0], m[0]);
    for (int i = 1; i < m.size(); i++) {
        ret = chinese_remainder_theorem(ret.second, ret.first, m[i], r[i]);
        if (ret.second == -1) break;
    }
    return ret;
}

/* find a pair (c,d) s.t. ac + bd = gcd(a,b)
 * Dependencies: none */
PLL extended_gcd(ll a, ll b) {
    if (b == 0) return make_pair(1, 0);
    PIL t = extended_gcd(b, a % b);
    return {t.second, t.first - t.second * (a / b)};
}

/* Find x in [0,m) s.t. ax ≡ gcd(a, m) (mod m)
 * Dependencies: extended_gcd(a, b) */
ll modinverse(ll a, ll m) {
    return (extended_gcd(a, m).first % m + m) % m;
}

/* Find a^p mod m */
ll modpower(ll a, ll p, ll m){
    ll r = 1;
    while(p){
        if(p&1)r = (r*a) % m;
        a = (a*a) % m;
        p >>= 1;
    }
    return r;
}
