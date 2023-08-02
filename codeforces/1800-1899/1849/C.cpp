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
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    s = " " + s;
    vector<pii> p(m + 1);

    vector<int> sum(n + 1);

    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + s[i] - '0';
    }

    set<pii> S;

    auto get_l = [&](int idx) {
        if (idx == 1) return 1;
        if (s[idx - 1] == '1') return idx;
        int l = 1, r = idx - 1;
        int ans = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            int val = sum[idx - 1] - sum[mid - 1];
            if (val == 0) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    };

    auto get_r = [&](int idx) {
        if (idx == n) return n;
        if (s[idx + 1] == '0') return idx;
        int l = idx + 1, r = n;
        int ans = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            int val = sum[mid] - sum[idx];
            if (val == mid - idx) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    };

    bool same = false;
    for (int i = 1; i <= m; i++) {
        cin >> p[i].first >> p[i].second;
        p[i].first = get_l(p[i].first);
        p[i].second = get_r(p[i].second);

        int tmp = sum[p[i].second] - sum[p[i].first - 1];
        int r = p[i].second;

        if (sum[r] - sum[r - tmp] == tmp) {
            same = true;
            continue;
        }

        S.insert(p[i]);
    }
    cout << S.size() + same << endl;
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