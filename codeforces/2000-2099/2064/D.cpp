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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> w(n);
    vector<int> suf_w(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    suf_w[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        suf_w[i] = w[i];
        if (i != n - 1) {
            suf_w[i] ^= suf_w[i + 1];
        }
    }

    const int BIT = 29;

    vector<vector<int>> idx(BIT + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= BIT; j++) {
            if ((w[i] >> j) & 1) {
                idx[j].push_back(i);
            }
        }
    }
    set<int> S;
    for (int i = 0; i <= BIT; i++) {
        int sz = idx[i].size();
        for (int j = 0; j < 2 && j < sz; j++) {
            S.insert(idx[i][sz - j - 1]);
        }
    }

    // debug(nxt);

    while (q--) {
        int x;
        cin >> x;

        auto it = S.end();
        it--;

        int ans;
        while (true) {
            int idx = *it;

            int val = x ^ suf_w[idx + 1];

            if (val >= w[idx]) {
                if (it == S.begin()) {
                    ans = -1;
                    break;
                } else {
                    it--;
                }
            } else {
                ans = idx;
                break;
            }
        }
        // debug(ans);
        cout << n - ans - 1 << ' ';
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