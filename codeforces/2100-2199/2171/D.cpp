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
    vector<int> p(n + 1), loc(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        loc[p[i]] = i;
    }

    vector<int> pre_mi_idx(n + 1);
    pre_mi_idx[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (p[pre_mi_idx[i - 1]] > p[i]) {
            pre_mi_idx[i] = i;
        } else {
            pre_mi_idx[i] = pre_mi_idx[i - 1];
        }
    }

    int now = n;
    set<int> S;
    typedef array<int, 2> a2;
    vector<a2> edges;
    while (now >= 1) {
        int go = pre_mi_idx[now];
        int val = p[go];
        if (val == 1) {
            for (int i = go; i <= now; i++) {
                if (i != go)
                    edges.push_back({1, p[i]});
                S.insert(p[i]);
            }
            now = go - 1;
        } else {
            int mx = *S.rbegin();
            if (val > mx) {
                cout << "No\n";
                return;
            }
            edges.push_back({val, mx});
            for (int i = go; i <= now; i++) {
                if (i != go) {
                    edges.push_back({val, p[i]});
                }
                S.insert(p[i]);
            }
        }
        now = go - 1;
    }
    cout << "Yes\n";
    for (auto it : edges) {
        cout << it[0] << ' ' << it[1] << '\n';
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