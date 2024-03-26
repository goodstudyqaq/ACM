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

typedef pair<int, int> pii;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> V(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    set<int> special;
    for (int i = 1; i <= n; i++) {
        if (V[i].size() == 4) {
            special.insert(i);
        }
    }
    int sz = special.size();
    debug(sz);

    // sz + sz * (sz - 1) == n
    if (1LL * sz + 1LL * sz * (sz - 1) != n) {
        cout << "NO" << endl;
        return;
    }

    int now = *special.begin();
    int rt = now;
    int pre = -1;

    for (int i = 0; i < sz; i++) {
        int go = -1;
        for (auto v : V[now]) {
            if (special.count(v) == 0) continue;
            if (v == pre) continue;
            if (go != -1 && now != rt) {
                cout << "NO" << endl;
                return;
            }
            go = v;
        }
        if (go == -1) {
            cout << "NO" << endl;
            return;
        }
        pre = now;
        now = go;
    }
    debug(now, rt);
    if (now != rt) {
        cout << "NO" << endl;
        return;
    }

    auto check = [&](int begin) -> bool {
        int now = begin;
        int pre = -1;
        // begin 是 special 的
        for (int i = 0; i < sz; i++) {
            int go = -1;
            for (auto v : V[now]) {
                if (v == pre) continue;
                if (special.count(v)) {
                    if (now == begin) {
                        continue;
                    }

                    if (v != begin) {
                        return false;
                    }
                }
                if (go != -1 && now != begin) {
                    return false;
                }
                go = v;
            }
            if (go == -1) {
                return false;
            }
            pre = now;
            now = go;
        }
        return now == begin;
    };

    for (auto it : special) {
        if (check(it) == false) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
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