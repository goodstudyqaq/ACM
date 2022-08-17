#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    bool flag = true;
    for (int i = 1; i < n; i++) {
        if (a[i] > a[i + 1]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << 0 << endl;
        return;
    }

    int l = 1, r = n;
    int ans = n;

    auto check = [&](int idx) {
        vector<int> tmp_a = a;
        unordered_set<int> S;
        for (int i = 1; i <= idx; i++) {
            S.insert(tmp_a[i]);
        }
        for (int i = 1; i <= n; i++) {
            if (S.count(tmp_a[i])) tmp_a[i] = 0;
        }
        debug(tmp_a);

        for (int i = 1; i < n; i++) {
            if (tmp_a[i] > tmp_a[i + 1]) return false;
        }
        return true;
    };
    // l = r = 2;
    while (l <= r) {
        int m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    unordered_set<int> S;
    for (int i = 1; i <= ans; i++) {
        S.insert(a[i]);
    }
    cout << S.size() << endl;
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
}