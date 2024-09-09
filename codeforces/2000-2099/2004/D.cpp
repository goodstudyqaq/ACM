#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<string> type(n);
    map<string, vector<int>> V;
    for (int i = 0; i < n; i++) {
        cin >> type[i];
        V[type[i]].push_back(i);
    }

    map<pair<string, string>, int> cache;

    auto check = [&](string &x, string &y) {
        if (cache.count({x, y})) return cache[{x, y}];
        for (auto c1 : x) {
            for (auto c2 : y) {
                if (c1 == c2) return cache[{x, y}] = true;
            }
        }
        return cache[{x, y}] = false;
    };

    auto work = [&](int x, int y, int m) {
        if (x <= m && m <= y) {
            return abs(x - y);
        }

        if (m < x) {
            return abs(x - y) + 2 * (x - m);
        } else {
            return abs(x - y) + 2 * (m - y);
        }
    };

    while (q--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        if (x > y) swap(x, y);
        if (check(type[x], type[y])) {
            cout << abs(x - y) << endl;
        } else {
            int res = 1e9;
            for (auto &it : V) {
                auto s = it.first;
                if (it.first != type[x] && check(s, type[x])) {
                    int idx1 = lower_bound(it.second.begin(), it.second.end(), x) - it.second.begin();
                    if (idx1 != it.second.size()) {
                        res = min(res, work(x, y, it.second[idx1]));
                    }
                    if (idx1 != 0) {
                        idx1--;
                        res = min(res, work(x, y, it.second[idx1]));
                    }
                }
            }
            if (res == 1e9) res = -1;
            cout << res << endl;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}