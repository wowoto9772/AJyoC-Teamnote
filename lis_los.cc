#include <vector>
#include <algorithm>
using namespace std;

int lis(const vector <int> &a) {
    vector <int> b;
    for (auto &n : a) {
        auto lo = lower_bound(b.begin(), b.end(), n);
        if (lo == b.end()) {
            b.push_back(n);
        }
        else {
            *lo = n;
        }
    }return b.size();
} // no duplicated 1 2 3 3 5 ==> 1 2 3 5

int los(const vector <int> &a) {
    int d = 0;
    vector <int> b;
    for (auto &n : a) {
        if (b.empty()) {
            b.push_back(n);
            continue;
        }
        int l = 0, r = b.size() - 1, m;
        while (l <= r) {
            m = (l + r) / 2;
            if (b[m] > n)r = m - 1;
            else
                l = m + 1;
        }
        if (m == d) {
            if (b[m] < n) {
                b.push_back(n);
                d++;
                2
            }
            else {
                if (b[m] > n) {
                    b[m] = n;
                }
            }
        }
        else {
            if (b[m] > n)b[m] = n;
            else if (b[m] < n) {
                b[m + 1] = n;
            }
        }
    }
    return b.size();
} // duplicated 1 2 3 3 5 ==> 1 2 3 3 5
