#include <bits/stdc++.h>

#include <numeric>

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
    int n;
    cin >> n;

    typedef array<int, 3> a3;
    vector<vector<a3>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        u--, v--;
        V[u].push_back({v, x, y});
        V[v].push_back({u, y, x});
    }
    vector<int> ans(n);

    function<void(int, int)> dfs = [&](int u, int pre) {
        for (auto [v, x, y] : V[u]) {
            if (v == pre) continue;
            if (x > y) {
                ans[v] = ans[u] - 1;
            } else {
                ans[v] = ans[u] + 1;
            }
            dfs(v, u);
        }
    };

    ans[0] = 1;
    dfs(0, -1);

    vector<int> f(n);
    iota(f.begin(), f.end(), 0);
    sort(f.begin(), f.end(), [&](int x, int y) {
        return ans[x] < ans[y];
    });
    vector<int> real_ans(n);

    int now = 1;
    for (int i = 0; i < n; i++) {
        int idx = f[i];
        real_ans[idx] = now++;
    }

    for (int i = 0; i < n; i++) {
        cout << real_ans[i] << ' ';
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