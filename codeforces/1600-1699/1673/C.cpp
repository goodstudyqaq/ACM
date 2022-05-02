#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
vector<int> V;
const int mod = 1e9 + 7;

vector<int> dp;
void init() {
    int n = 4e4;

    auto check = [&](int val) {
        vector<int> tmp;
        while (val) {
            tmp.push_back(val % 10);
            val /= 10;
        }
        int m = tmp.size();
        for (int i = 0; i < m / 2; i++) {
            if (tmp[i] != tmp[m - 1 - i]) {
                return false;
            }
        }
        return true;
    };

    for (int i = 1; i <= n; i++) {
        if (check(i)) {
            V.push_back(i);
        }
    }
    // debug(V);
    int sz = V.size();
    dp.resize(n + 1);
    dp[0] = 1;

    for (int j = 1; j <= sz; j++) {
        for (int i = 0; i <= n; i++) {
            int val = V[j - 1];
            if (i >= val) {
                (dp[i] += dp[i - val]) %= mod;
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;

    int res = 0;
    int sz = V.size();
    res = dp[n];

    cout << res << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}