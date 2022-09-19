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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<pii> interval(n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        interval[i] = {l, r};
    }

    int m;
    cin >> m;

    vector<int> w(m);
    for (int i = 0; i < m; i++) {
        cin >> w[i];
    }

    auto work = [&](int val) -> int {
        int res = 0;
        vector<pii> events;
        for (int i = 0; i < n; i++) {
            auto [l, r] = interval[i];
            if (r - l + 1 >= val) {
                res++;
            } else {
                int l_mod = l % val, r_mod = r % val;
                if (l_mod <= r_mod) {
                    events.push_back({l_mod, 1});
                    events.push_back({r_mod + 1, -1});
                } else {
                    events.push_back({l_mod, 1});
                    events.push_back({0, 1});
                    events.push_back({r_mod + 1, -1});
                }
            }
        }
        sort(events.begin(), events.end());
        int now = 0;
        int ans = 0;
        for (auto it : events) {
            now += it.second;
            ans = max(ans, now);
        }
        return ans + res;
    };

    vector<int> ans(30);
    for (int i = 0; i < 30; i++) {
        int res = work(1 << i);
        ans[i] = res;
    }

    for (int i = 0; i < m; i++) {
        int res = ans[__builtin_ctz(w[i])];
        cout << res << endl;
    }
    return 0;
}