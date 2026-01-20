#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n = 7;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = i + 1;
    }

    auto check = [&]() {
        int res = 0;
        for (int i = 0; i < n - 2; i++) {
            int val = v[i];
            int val2 = v[i + 1];
            int val3 = v[i + 2];
            if (gcd(val, val2) == 1 && gcd(val, val3) == 1 && gcd(val2, val3) == 1) res++;
        }
        return res;
    };

    int mi = 1e9;
    vector<int> res;
    do {
        int num = check();
        if (num == 0) {
            res = v;
            debug(v);
            // break;
        }
    } while (next_permutation(v.begin(), v.end()));
    debug(res);
}