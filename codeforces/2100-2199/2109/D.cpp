#include <bits/stdc++.h>

#include "./graph/graph-template.hpp"

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
    int n, m, sz;
    cin >> n >> m >> sz;
    vector<int> s(sz);
    long long sum = 0;
    for (int i = 0; i < sz; i++) {
        cin >> s[i];
        sum += s[i];
    }

    long long mx_odd = 0, mx_even = 0;

    if (sum % 2) {
        mx_odd = sum;
    } else {
        mx_even = sum;
    }

    for (int i = 0; i < sz; i++) {
        long long tmp = sum - s[i];

        if (tmp % 2) {
            mx_odd = max(mx_odd, tmp);
        } else {
            mx_even = max(mx_even, tmp);
        }
    }

    Graph<> g(n);
    g.read(m);
    vector<vector<int>> d(n, vector<int>(2, -1));

    queue<pair<int, int>> Q;
    Q.push({0, 0});
    d[0][0] = 0;

    while (!Q.empty()) {
        auto [u, f] = Q.front();
        Q.pop();
        int f2 = f ^ 1;

        for (auto v : g[u]) {
            if (d[v][f2] == -1) {
                d[v][f2] = d[u][f] + 1;
                Q.push({v, f2});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        bool flag = false;
        if (d[i][0] != -1 && mx_even >= d[i][0]) {
            flag = true;
        }
        if (d[i][1] != -1 && mx_odd >= d[i][1]) {
            flag = true;
        }
        if (flag) {
            cout << 1;
        } else {
            cout << 0;
        }
    }
    cout << '\n';
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