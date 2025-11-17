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
    vector<int> cnt(m + 1);
    vector<vector<int>> V(n);
    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;
        V[i].resize(l);
        for (int j = 0; j < l; j++) {
            cin >> V[i][j];
            cnt[V[i][j]]++;
        }
    }

    bool ok = true;
    for (int i = 1; i <= m; i++) {
        if (cnt[i] == 0) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        cout << "NO\n";
        return;
    }

    auto check = [&](int idx) {
        bool ok = true;
        for (auto v : V[idx]) {
            if (cnt[v] == 1) {
                return false;
            }
        }
        return true;
    };

    int ok_num = 0;
    for (int i = 0; i < n; i++) {
        if (check(i)) {
            ok_num++;
        }
        if (ok_num == 2) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
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