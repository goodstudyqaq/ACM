#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n == 1) {
        if (a[0] > 0) {
            cout << 0 << ' ' << 0 << endl;
        } else {
            cout << 1 << ' ' << 0 << endl;
        }
        return;
    }

    int now = 0;
    int ans = -1;
    typedef pair<int, int> pii;
    typedef pair<int, pii> piii;
    pii res = {n, 0};

    auto work = [&](int l, int r) -> piii {
        if (l == r) {
            if (a[l] > 0) {
                int tmp = (a[l] == 1 ? 0 : 1);
                return {tmp, {l, n - r - 1}};
            } else {
                return {-1, {-1, -1}};
            }
        }
        int x = 0, y = 0;
        int ans = -1;
        pii res = {l, n - r - 1};
        for (int i = l; i <= r; i++) {
            if (abs(a[i]) == 2) {
                x++;
            }
            if (a[i] < 0) {
                y++;
            }
            if (y % 2 == 0) {
                if (ans < x) {
                    ans = x;
                    res.first = l;
                    res.second = n - i - 1;
                }
            }
        }
        // debug(ans, res);

        x = 0, y = 0;
        for (int i = r; i >= l; i--) {
            if (abs(a[i]) == 2) {
                x++;
            }
            if (a[i] < 0) {
                y++;
            }
            if (y % 2 == 0) {
                if (ans < x) {
                    ans = x;
                    res.second = n - r - 1;
                    res.first = i;
                }
            }
        }
        return {ans, res};
    };

    while (now < n) {
        int go1 = now;
        while (go1 < n && a[go1] == 0) {
            go1++;
        }
        if (go1 == n) break;
        int go2 = go1;
        while (go2 < n && a[go2] != 0) {
            go2++;
        }
        piii tmp = work(go1, go2 - 1);
        if (tmp.first > ans) {
            ans = tmp.first;
            res = tmp.second;
        }
        now = go2;
    }
    debug(ans);

    if (ans == -1) {
        cout << n << ' ' << 0 << endl;
        return;
    }
    cout << res.first << ' ' << res.second << endl;
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