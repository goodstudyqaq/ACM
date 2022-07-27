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
    string s, t;
    cin >> s >> t;

    auto get_ans = [&](string s, string t) -> ll {
        if (s[0] != t[0] || s[n - 1] != t[n - 1]) {
            return -1;
        }
        vector<int> v1, v2;

        for (int i = 1; i < n; i++) {
            if (s[i] != s[i - 1]) {
                v1.push_back(i);
            }
            if (t[i] != t[i - 1]) {
                v2.push_back(i);
            }
        }

        if (v1.size() != v2.size()) return -1;

        ll ans = 0;
        for (int i = 0; i < v1.size(); i++) {
            if (s[v1[i]] != t[v2[i]]) return -1;
            ans += abs(v1[i] - v2[i]);
        }
        return ans;
    };

    ll ans1 = get_ans(s, t);
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    ll ans2 = get_ans(s, t);

    if (ans1 == -1 && ans2 == -1) {
        cout << -1 << endl;
    } else if (ans1 != -1 && ans2 != -1) {
        cout << min(ans1, ans2) << endl;
    } else if (ans1 != -1) {
        cout << ans1 << endl;
    } else {
        cout << ans2 << endl;
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
}