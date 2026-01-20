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
    vector<int> a(n);

    int mx_idx = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[mx_idx] < a[i]) {
            mx_idx = i;
        }
    }

    vector<int> a2(n);
    for (int i = 0; i < n; i++) {
        a2[i] = a[(mx_idx + i) % n];
    }
    a = a2;

    vector<int> stk;
    vector<int> nxt(n, -1);
    vector<int> pre(n, -1);
    for (int i = 0; i < n; i++) {
        while (stk.size() && (a[stk.back()] < a[i])) {
            stk.pop_back();
        }
        if (stk.size()) {
            pre[i] = stk.back();
        }
        stk.push_back(i);
    }

    stk.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (stk.size() && (a[stk.back()] <= a[i])) {
            stk.pop_back();
        }
        if (stk.size()) {
            nxt[i] = stk.back();
        }
        stk.push_back(i);
    }

    ll ans = 0;
    const int inf = numeric_limits<int>::max() / 2;
    for (int i = 1; i < n; i++) {
        int idx1 = nxt[i], idx2 = pre[i];
        int ct = inf;
        if (idx1 != -1) {
            ct = min(ct, a[idx1]);
        }
        if (idx2 != -1) {
            ct = min(ct, a[idx2]);
        }
        if (ct == inf) continue;
        debug(i, ct, idx1, idx2);
        ans += ct;
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