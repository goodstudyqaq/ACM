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
    ll l, r;
    cin >> l >> r;

    auto work = [&](ll x) {
        vector<int> res;
        while (x) {
            res.push_back(x % 2);
            x /= 2;
        }
        reverse(res.begin(), res.end());
        return res;
    };

    debug(work(l));
    debug(work(r));
    debug(r - l + 1);

    vector<ll> ans;
    for (ll i = l + 1; i <= r; i++) {
        ans.push_back(i ^ l);
    }

    vector<ll> real_ans;
    for (auto it : ans) {
        bool flag = true;
        for (ll i = l; i <= r; i++) {
            ll tmp = i ^ it;
            if (tmp < l || tmp > r) {
                flag = false;
                break;
            }
        }
        if (flag) real_ans.push_back(it);
    }
    sort(real_ans.begin(), real_ans.end());
    debug(real_ans);
    cout << real_ans.size() << '\n';
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