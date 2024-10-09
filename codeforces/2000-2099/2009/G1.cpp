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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= i;
    }

    vector<int> ans(n - k + 1);

    map<int, int> cnt;
    set<pii> S;
    int r = 0;
    for (int i = 0; i <= n - k; i++) {
        while (r < i + k) {
            int before_cnt = cnt[a[r]];
            S.erase({before_cnt, a[r]});
            cnt[a[r]]++;
            S.insert({cnt[a[r]], a[r]});
            r++;
        }

        auto it = prev(S.end());
        ans[i] = k - it->first;

        S.erase({cnt[a[i]], a[i]});
        cnt[a[i]]--;
        if (cnt[a[i]]) {
            S.insert({cnt[a[i]], a[i]});
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << ans[l] << endl;
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