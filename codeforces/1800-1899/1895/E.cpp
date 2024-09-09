#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
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
    vector<piii> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first.first;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i].first.second;
    }
    int m;
    cin >> m;
    vector<piii> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i].first.first;
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i].first.second;
    }
    for (int i = 0; i < n; i++) {
        a[i].second = i;
    }
    for (int i = 0; i < m; i++) {
        b[i].second = i;
    }

    sort(b.begin(), b.end());

    vector<int> b_suf_mx(m);
    for (int i = m - 1; i >= 0; i--) {
        b_suf_mx[i] = i;
        if (i + 1 < m) {
            if (b[i].first.second < b[b_suf_mx[i + 1]].first.second) {
                b_suf_mx[i] = b_suf_mx[i + 1];
            }
        }
    }

    vector<vector<int>> V(n + m), revV(n + m);
    for (int i = 0; i < n; i++) {
        int defence = a[i].first.second;
        int idx = upper_bound(b.begin(), b.end(), piii(pii(defence, 1e9), 1e9)) - b.begin();

        if (idx != m) {
            int idx2 = b_suf_mx[idx];
            V[a[i].second].push_back(n + b[idx2].second);
            revV[n + b[idx2].second].push_back(a[i].second);
        }
    }

    sort(a.begin(), a.end());
    vector<int> a_suf_mx(n);
    for (int i = n - 1; i >= 0; i--) {
        a_suf_mx[i] = i;
        if (i + 1 < n) {
            if (a[i].first.second < a[a_suf_mx[i + 1]].first.second) {
                a_suf_mx[i] = a_suf_mx[i + 1];
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int defence = b[i].first.second;
        int idx = upper_bound(a.begin(), a.end(), piii(pii(defence, 1e9), 1e9)) - a.begin();
        if (idx != n) {
            int idx2 = a_suf_mx[idx];
            V[n + b[i].second].push_back(a[idx2].second);
            revV[a[idx2].second].push_back(n + b[i].second);
        }
    }
    debug(V);

    vector<int> dp(n + m, -1);

    function<void(int)> dfs = [&](int u) {
        for (auto v : revV[u]) {
            dp[v] = dp[u] ^ 1;
            dfs(v);
        }
    };

    for (int i = 0; i < n + m; i++) {
        if (V[i].size() == 0) {
            dp[i] = 1;
            dfs(i);
        }
    }

    vector<int> cnt(2);
    for (int i = 0; i < n; i++) {
        if (dp[i] != -1) cnt[dp[i]]++;
    }

    cout << cnt[1] << ' ' << n - cnt[0] - cnt[1] << ' ' << cnt[0] << endl;
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