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
vector<int> z_function(const string &s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    string s;
    cin >> s;

    vector<int> z = z_function(s);
    debug(z);
    z[0] = n;

    vector<int> ans(n + 1);

    set<int> S;

    set<pair<int, int>> Info;

    for (int i = 0; i < n; i++) {
        if (s[i] == s[0]) {
            S.insert(i);
            Info.insert({z[i], i});
        }
    }

    auto work = [&](int len, char c) -> int {
        // set<int>::iterator itor = S.begin();

        set<pair<int, int>>::iterator itor = Info.begin();

        while (itor != Info.end()) {
            int the_len = (*itor).first;
            if (the_len < len + 1) {
                S.erase(itor->second);
                itor = Info.erase(itor);
            } else {
                break;
            }
        }

        int mx = -1;
        int res = 0;

        set<int>::iterator itor2 = S.begin();

        while (itor2 != S.end()) {
            res++;
            itor2 = S.upper_bound(*itor2 + len);
        }

        return res;
    };
    ans[S.size()] = 1;
    int now = 1;
    debug(n);
    while (S.size() && now < n) {
        int res = work(now, s[now]);
        now++;
        debug(now, S, res);
        ans[res] = max(ans[res], now);
    }

    for (int i = n - 1; i >= 1; i--) {
        ans[i] = max(ans[i], ans[i + 1]);
    }

    for (int i = l; i <= r; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
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