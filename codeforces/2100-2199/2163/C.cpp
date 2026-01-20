#include <bits/stdc++.h>

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
    vector<vector<int>> a(2, vector<int>(n));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    vector<int> pre_mi(n), pre_mx(n);

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            pre_mi[i] = a[0][i];
            pre_mx[i] = a[0][i];
        } else {
            pre_mi[i] = min(pre_mi[i - 1], a[0][i]);
            pre_mx[i] = max(pre_mx[i - 1], a[0][i]);
        }
    }

    vector<int> suf_mi(n), suf_mx(n);
    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1) {
            suf_mi[i] = a[1][i];
            suf_mx[i] = a[1][i];
        } else {
            suf_mi[i] = min(suf_mi[i + 1], a[1][i]);
            suf_mx[i] = max(suf_mx[i + 1], a[1][i]);
        }
    }

    typedef array<int, 2> a2;
    vector<a2> V;
    for (int i = 0; i < n; i++) {
        int mi = min(pre_mi[i], suf_mi[i]);
        int mx = max(pre_mx[i], suf_mx[i]);
        V.push_back({mi, mx});
    }
    sort(V.begin(), V.end());

    set<a2> S;
    for (int i = 0; i < n; i++) {
        S.insert({V[i][1], i});
    }

    int v_idx = 0;
    ll ans = 0;
    for (int l = 1; l <= 2 * n; l++) {
        while (v_idx < V.size() && l > V[v_idx][0]) {
            S.erase({V[v_idx][1], v_idx});
            v_idx++;
        }

        if (S.size() == 0) break;

        auto it = S.begin();
        ans += 2 * n - (*it)[0] + 1;
    }
    cout << ans << '\n';
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