#include <bits/stdc++.h>

#include <functional>

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
    int n, q;
    cin >> n >> q;
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    vector<vector<int>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        V[x].push_back(y);
        V[y].push_back(x);
    }

    set<int> more;
    set<int> one;

    set<int> black;
    set<int> zero;
    vector<int> cnt(n + 1);

    auto add = [&](int idx) {
        black.insert(idx);
        for (auto v : V[idx]) {
            if (black.count(v)) {
                cnt[idx]++;
                cnt[v]++;
                if (cnt[v] == 1) {
                    zero.erase(v);
                    one.insert(v);
                } else if (cnt[v] == 2) {
                    one.erase(v);
                } else {
                    more.insert(v);
                }
            }
        }

        if (cnt[idx] >= 3) {
            more.insert(idx);
        }
        if (cnt[idx] == 1) {
            one.insert(idx);
        }
        if (cnt[idx] == 0) {
            zero.insert(idx);
        }
    };

    auto remove = [&](int idx) {
        black.erase(idx);
        if (cnt[idx] == 0) {
            zero.erase(idx);
        }
        if (cnt[idx] == 1) {
            one.erase(idx);
        }
        if (cnt[idx] >= 3) {
            more.erase(idx);
        }

        for (auto v : V[idx]) {
            if (black.count(v)) {
                cnt[idx]--;
                cnt[v]--;
                if (cnt[v] == 0) {
                    one.erase(v);
                    zero.insert(v);
                } else if (cnt[v] == 1) {
                    one.insert(v);
                } else if (cnt[v] == 2) {
                    more.erase(v);
                }
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (c[i] == 1) {
            add(i);
        }
    }
    debug(more, one, black);

    while (q--) {
        int u;
        cin >> u;
        if (c[u]) {
            remove(u);
            c[u] = 0;
        } else {
            add(u);
            c[u] = 1;
        }
        if (black.size() == 0) {
            cout << "NO" << endl;
            continue;
        }
        if (more.size() > 0) {
            cout << "NO" << endl;
            continue;
        } 
        if (one.size() > 2) {
            cout << "NO" << endl;
            continue;
        } 
        if (zero.size() > 1) {
            cout << "NO" << endl;
            continue;
        }

        cout << "YES" << endl;

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