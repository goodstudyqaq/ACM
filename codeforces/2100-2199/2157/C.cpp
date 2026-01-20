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
    int n, k, q;
    cin >> n >> k >> q;

    vector<int> status(n + 1);
    typedef array<int, 2> a2;
    vector<a2> V;
    for (int i = 0; i < q; i++) {
        int c, l, r;
        cin >> c >> l >> r;
        c--;
        for (int j = l; j <= r; j++) {
            status[j] |= (1 << c);
        }
        if (c == 1) {
            V.push_back({l, r});
        }
    }

    vector<int> ans(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (status[i] == 0) {
            ans[i] = 1e9;
        } else if (status[i] == 1) {
            ans[i] = k;
        } else if (status[i] == 2) {
        } else {
            ans[i] = 1e9;
        }
        }
    sort(V.begin(), V.end());

    for (auto it : V) {
        int l = it[0], r = it[1];
        set<int> S;
        vector<int> tmp;

        for (int i = l; i <= r; i++) {
            if (ans[i] == -1) {
                tmp.push_back(i);
            }
            if (ans[i] == -1 || ans[i] == 1e9) continue;
            S.insert(ans[i]);
        }

        int now = 0;

        int now_val = 0;
        while (now_val < k) {
            if (S.count(now_val)) {
                now_val++;
                continue;
            }
            ans[tmp[now]] = now_val;
            now++;
            now_val++;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i] == -1) ans[i] = 1e9;
        cout << ans[i] << ' ';
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