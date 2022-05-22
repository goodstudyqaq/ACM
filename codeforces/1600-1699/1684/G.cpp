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

struct Hungary {
    vector<int> cx, cy;
    vector<bool> used;
    int count;
    vector<vector<int>> g;

    bool dfs(int u) {
        for (auto v : g[u]) {
            if (!used[v]) {
                used[v] = 1;
                if (cy[v] == -1 || dfs(cy[v])) {
                    cy[v] = u;
                    cx[u] = v;
                    return 1;
                }
            }
        }
        return 0;
    }

    Hungary() {}
    Hungary(int uN, int vN, vector<vector<int>> &_g) {
        g = _g;
        cx.resize(uN, -1);
        cy.resize(vN, -1);
        used.resize(vN, 0);
        int res = 0;
        for (int u = 0; u < uN; u++) {
            used.assign(vN, 0);
            if (dfs(u)) res++;
        }
        count = res;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;

    vector<ll> left, right;
    int limit = m / 3;
    for (int i = 1; i <= n; i++) {
        ll t;
        cin >> t;
        if (t > limit) {
            left.push_back(t);
        } else {
            right.push_back(t);
        }
    }
    int left_sz = left.size();
    int right_sz = right.size();
    vector<vector<int>> g(left_sz);
    for (int i = 0; i < left.size(); i++) {
        for (int j = 0; j < right.size(); j++) {
            if (left[i] % right[j] == 0 && 2LL * left[i] + right[j] <= m) {
                g[i].push_back(j);
            }
        }
    }
    Hungary h(left_sz, right_sz, g);
    int cnt = h.count;
    if (cnt < left_sz) {
        cout << -1 << endl;
        return 0;
    }
    typedef pair<int, int> pii;
    vector<pii> ans;
    for (int i = 0; i < left_sz; i++) {
        int y = h.cx[i];
        int left_val = left[i];
        int right_val = right[y];
        int a = left_val + right_val, b = 2 * left_val + right_val;
        ans.push_back({b, a});
        // cout << b << ' ' << a << endl;
    }

    for (int i = 0; i < right_sz; i++) {
        if (h.cy[i] == -1) {
            int val = right[i];
            ans.push_back({3 * val, 2 * val});
            // cout << 3 * val << ' ' << 2 * val << endl;
        }
    }
    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it.first << ' ' << it.second << endl;
    }

    return 0;
}