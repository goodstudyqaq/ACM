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

void brute_force(ll l, ll r) {
    vector<ll> ans;
    for (ll i = l + 1; i <= r; i++) {
        ans.push_back(i ^ l);
    }

    int res = 0;
    for (auto it : ans) {
        bool flag = true;
        for (ll i = l; i <= r; i++) {
            ll tmp = i ^ it;
            if (tmp < l || tmp > r) {
                flag = false;
                break;
            }
        }
        if (flag) res++;
    }
    cout << res << '\n';
}

void solve() {
    ll l, r;
    cin >> l >> r;
    if (l == r) {
        cout << 0 << '\n';
        return;
    }
    // if (r - l <= 50) {
    //     brute_force(l, r);
    //     return;
    // }

    auto work = [&](ll x) {
        vector<int> res;
        while (x) {
            res.push_back(x % 2);
            x /= 2;
        }
        return res;
    };

    int b1 = 0, b2 = 0;
    auto v1 = work(l);
    auto v2 = work(r);
    debug(v1);
    debug(v2);
    while (b1 < v1.size() && v1[b1] == 0) b1++;
    while (b2 < v2.size() && v2[b2] == 1) b2++;

    int b = min(b1, b2);

    debug(b);
    ll ans = (1LL << b);

    auto check = [&](int b) {
        int len = max(v1.size(), v2.size());
        int flag = 1;
        int len1 = 0, len2 = 0;
        for (int i = b; i < len; i++) {
            int tmp1 = i < v1.size() ? v1[i] : 0;
            int tmp2 = i < v2.size() ? v2[i] : 0;

            if (flag == 1) {
                if (tmp1 == tmp2) {
                    flag = 2;
                    len2++;
                } else {
                    len1++;
                }
            } else if (flag == 2) {
                if (tmp1 != tmp2) return false;
                len2++;
            }
        }

        if (len1 == 0) return false;

        return true;
    };

    if (check(b)) {
        ans *= 2;
    }
    ans--;

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