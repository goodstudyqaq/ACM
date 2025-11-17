#include <bits/stdc++.h>

#include <cstdio>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

void solve() {
    int n;
    cin >> n;

    auto ask = [&](int x, vector<int> &v) {
        cout << "? " << x << ' ' << v.size();
        for (auto it : v) {
            cout << ' ' << it;
        }
        cout << '\n';
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };

    vector<int> v(n);
    for (int i = 1; i <= n; i++) {
        v[i - 1] = i;
    }

    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        ans[i] = ask(i, v);
    }

    int u = 1;
    for (int i = 2; i <= n; i++) {
        if (ans[i] > ans[u]) {
            u = i;
        }
    }

    vector<int> res;
    res.push_back(u);
    int d = ans[u];
    int now = u;

    while (true) {
        d--;
        if (d == 0) break;
        int go = -1;
        for (int i = 1; i <= n; i++) {
            if (ans[i] + 1 == ans[now]) {
                vector<int> tmp{now, i};
                int res = ask(now, tmp);
                if (res == 2) {
                    go = i;
                    break;
                }
            }
        }
        res.push_back(go);
        now = go;
    }

    cout << "! " << res.size();
    for (int i = 0; i < res.size(); i++) {
        cout << ' ' << res[i];
    }
    cout << '\n';
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}