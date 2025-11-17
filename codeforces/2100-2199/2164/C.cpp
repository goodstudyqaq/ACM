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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    typedef array<int, 2> mon;
    vector<mon> V(m);
    for (int i = 0; i < m; i++) {
        cin >> V[i][0];
    }
    for (int i = 0; i < m; i++) {
        cin >> V[i][1];
    }

    vector<mon> V0, V1;
    for (int i = 0; i < m; i++) {
        if (V[i][1] > 0) {
            V1.push_back(V[i]);
        } else {
            V0.push_back(V[i]);
        }
    }

    multiset<int> S;
    for (auto it : a) {
        S.insert(it);
    }
    // 先搞 V1
    sort(V1.begin(), V1.end());
    int ans = 0;
    int sz = V1.size();
    for (int i = 0; i < sz; i++) {
        auto [b, c] = V1[i];
        auto it = S.lower_bound(b);
        if (it == S.end()) {
            break;
        }
        ans++;
        int val = *it;
        S.erase(it);
        val = max(val, c);
        S.insert(val);
    }
    // 干 V0

    sort(V0.begin(), V0.end());
    sz = V0.size();
    for (int i = 0; i < sz; i++) {
        auto [b, c] = V0[i];
        auto it = S.lower_bound(b);
        if (it == S.end()) {
            break;
        }
        ans++;
        S.erase(it);
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