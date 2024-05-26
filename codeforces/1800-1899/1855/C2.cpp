#include <bits/stdc++.h>

#include <algorithm>

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
    vector<int> a(n + 1);
    int mx_2 = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (abs(a[i]) > abs(a[mx_2])) {
            mx_2 = i;
        }
    }
    if (a[mx_2] == 0) {
        cout << 0 << endl;
        return;
    }

    auto work = [&](vector<int> a, int f) -> vector<pii> {
        vector<pii> ans;
        int mx = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 0) continue;
            int f2 = a[i] > 0;
            if (f == f2) {
                if (mx == -1 || abs(a[i]) > abs(a[mx])) {
                    mx = i;
                }
            }
        }

        if (mx == -1) {
            for (int i = 0; i < 35; i++) {
                ans.push_back({i, i});
            }
            return ans;
        }

        if (mx_2 == mx) {
            for (int i = 1; i <= n; i++) {
                if (a[i] == 0) continue;
                int f2 = a[i] > 0;
                if (f != f2) {
                    ans.push_back({i, mx});
                    a[i] += a[mx];
                }
            }
        } else {
            while (abs(a[mx]) < abs(a[mx_2])) {
                ans.push_back({mx, mx});
                a[mx] += a[mx];
            }
            for (int i = 1; i <= n; i++) {
                if (a[i] == 0) continue;
                int f2 = a[i] > 0;
                if (f != f2) {
                    ans.push_back({i, mx});
                    a[i] += a[mx];
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            if (a[i] == 0) continue;
            f = a[i] > 0;
            break;
        }


        if (f) {
            for (int i = 2; i <= n; i++) {
                ans.push_back({i, i - 1});
                a[i] += a[i - 1];
            }
        } else {
            for (int i = n - 1; i >= 1; i--) {
                ans.push_back({i, i + 1});
                a[i] += a[i + 1];
            }
        }
        return ans;

    };

    auto ans1 = work(a, 0);
    if (ans1.size() > 31) {
        ans1 = work(a, 1);
    }
    cout << ans1.size() << endl;
    for (auto it : ans1) {
        cout << it.first << ' ' << it.second << endl;
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