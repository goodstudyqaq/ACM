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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    auto work = [&]() {
        set<int> S;
        for (int i = 1; i <= n; i++) {
            S.insert(i);
        }

        vector<int> ans(n + 1);
        for (int i = 1; i <= n; i++) {
            auto it = S.upper_bound(a[i]);

            if (it != S.begin()) {
                it--;
                S.erase(it);
            }
            ans[i] = n - S.size();
        }
        return ans;
    };

    auto pre = work();

    reverse(a.begin() + 1, a.begin() + 1 + n);
    auto suf = work();
    reverse(suf.begin() + 1, suf.begin() + 1 + n);

    long long res = 0;
    for (int i = 1; i < n; i++) {
        res += min(pre[i], suf[i + 1]);
    }
    cout << res << '\n';
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