#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    map<int, int> M;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        M[v]++;
    }
    set<int> S;
    for (auto it : M) {
        if (it.second >= k) {
            S.insert(it.first);
        }
    }

    auto it = S.begin();
    int ans = -1;
    int l, r;
    debug(S);
    while (it != S.end()) {
        auto go = it;
        while (go != S.end() && next(go) != S.end() && *next(go) == *go + 1) {
            go++;
        }
        int v1 = *it, v2 = *go;
        if (v2 - v1 + 1 > ans) {
            ans = v2 - v1 + 1;
            l = v1, r = v2;
        }
        it = go;
        it++;
    }
    if (ans == -1) {
        cout << -1 << endl;
        return;
    }
    cout << l << ' ' << r << endl;
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
}