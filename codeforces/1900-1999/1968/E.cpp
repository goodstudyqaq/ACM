#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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
    int n;
    cin >> n;

    if (n == 2) {
        cout << 1 << ' ' << 1 << endl;
        cout << 1 << ' ' << 2 << endl;
        return;
    }

    set<pair<int, int>> S;
    set<pair<int, int>> ans;

    S.insert({1, 1});
    S.insert({1, 2});
    S.insert({n, n});

    auto out = [&]() {
        for (auto it : S) {
            cout << it.first << ' ' << it.second << endl;
        }
    };

    if (n == 3) {
        out();
        return;
    }

    S.insert({n, n - 2});

    set<int> have;
    for (auto it : S) {
        for (auto it2 : S) {
            have.insert(abs(it.first - it2.first) + abs(it.second - it2.second));
        }
    }

    auto check = [&](int x, int y) {
        int new_add = 0;
        for (auto it : ans) {
            int tmp = abs(it.first - x) + abs(it.second - y);
            if (have.count(tmp) == 0) {
                new_add++;
            }
        }
        return new_add >= 2;
    };

    auto add = [&](int x, int y) {
        for (auto it : ans) {
            int tmp = abs(it.first - x) + abs(it.second - y);
            have.insert(tmp);
        }
    };

    int need = n - 4;
    ans = S;

    for (int i = 1; i <= n && need; i++) {
        for (int j = 1; j <= n && need; j++) {
            if (S.count({i, j})) continue;

            if (check(i, j)) {
                S.insert({i, j});
                add(i, j);
                need--;
            }
        }
    }
    debug(have);
    out();
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