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
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1), b(m + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    set<int> S;
    int l = 1;
    for (int i = 1; i <= m; i++) {
        debug(i, S);
        int val = b[i];
        if (S.count(val)) {
            continue;
        } else if (l <= n && a[l] == val) {
            S.insert(val);
            l++;
            continue;
        } else {
            cout << "TIDAK" << endl;
            return;
        }
    }
    cout << "YA" << endl;
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