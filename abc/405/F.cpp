#include <bits/stdc++.h>

#include <cassert>

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

    int n, m;
    cin >> n >> m;
    n *= 2;

    typedef pair<int, int> pii;
    vector<pii> event;

    vector<int> A(m), B(m);
    vector<int> idx(n + 1, -1);
    for (int i = 0; i < m; i++) {
        cin >> A[i] >> B[i];
        A[i]--, B[i]--;
        idx[A[i]] = i + 1;
        idx[B[i]] = i + 1;
    }

    int m1 = 0;
    while ((1 << m1) < m + 1) m1++;
    stack<int> stk;
    stk.push(0);

    vector<vector<int>> par(m1, vector<int>(m + 1));
    vector<int> dep(m + 1);
    par[0][0] = -1;

    vector<int> belong(n);
    for (int i = 0; i < n; i++) {
        if (i % 2) {
            if (idx[i] != -1) {
                if (stk.top() == idx[i]) {
                    stk.pop();
                } else {
                    par[0][idx[i]] = stk.top();
                    dep[idx[i]] = dep[stk.top()] + 1;
                    stk.push(idx[i]);
                }
            } else {
                continue;
            }
        } else {
            belong[i] = stk.top();
        }
    }

    for (int i = 0; i < m1 - 1; i++) {
        for (int j = 0; j < m + 1; j++) {
            int p = par[i][j];
            if (p != -1) {
                par[i + 1][j] = par[i][p];
            }
        }
    }

    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }

        int d = dep[u] - dep[v];

        for (int i = m1 - 1; i >= 0; i--) {
            if ((d >> i) & 1) {
                u = par[i][u];
            }
        }
        if (u == v) {
            return u;
        }

        assert(dep[u] == dep[v]);

        for (int i = m1 - 1; i >= 0; i--) {
            if (par[i][u] != par[i][v]) {
                u = par[i][u];
                v = par[i][v];
            }
        }
        return par[0][u];
    };

    int q;
    cin >> q;
    while (q--) {
        int c, d;
        cin >> c >> d;
        c--, d--;
        int u = belong[c], v = belong[d];

        int _lca = lca(u, v);
        debug(u, v, _lca);
        cout << dep[u] + dep[v] - 2 * dep[_lca] << '\n';
    }
    return 0;
}