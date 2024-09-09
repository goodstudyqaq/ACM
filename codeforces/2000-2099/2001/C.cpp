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

    vector<int> V;
    for (int i = 2; i <= n; i++) {
        V.push_back(i);
    }

    vector<vector<int>> V2(n + 1);

    map<pair<int, int>, int> cache;

    int ask_num = 0;
    vector<int> vis(n + 1);
    function<void(int, int)> ask = [&](int a, int b) {
        if (cache.count({a, b})) {
            return;
        }
        vis[a] = 1;
        vis[b] = 1;
        ask_num++;

        cout << "? " << a << ' ' << b << endl;
        fflush(stdout);
        int u;
        if (cache.count({a, b})) {
            u = cache[{a, b}];
        } else {
            cin >> u;
        }
        cache[{a, b}] = u;
        if (a == u) {
            V2[a].push_back(b);
        } else {
            ask(a, u);
            ask(u, b);
        }
    };

    vis[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            ask(1, i);
        }
    }

    assert(ask_num <= 15 * n);

    cout << "!";
    for (int i = 1; i <= n; i++) {
        for (auto v : V2[i]) {
            cout << " " << i << " " << v;
        }
    }
    cout << endl;
    fflush(stdout);
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