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
    vector<int> a(n + 1);
    vector<int> idx;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] != -1) {
            idx.push_back(i);
        }
    }
    int m = idx.size();

    if (m == 0) {
        for (int i = 1; i <= n; i++) {
            if (i % 2) {
                cout << 1 << ' ';
            } else {
                cout << 2 << ' ';
            }
        }
        cout << endl;
        return;
    }

    for (int i = idx[0] - 1; i >= 1; i--) {
        if (a[i + 1] == 1) {
            a[i] = 2;
        } else {
            a[i] = a[i + 1] / 2;
        }
    }
    for (int i = idx[m - 1] + 1; i <= n; i++) {
        if (a[i - 1] == 1) {
            a[i] = 2;
        } else {
            a[i] = a[i - 1] / 2;
        }
    }

    auto check = [&](int idx) {
        if (idx <= 0 || idx > n) return true;
        int l = idx - 1;
        if (l > 0 && a[l] != -1) {
            if (a[l] / 2 != a[idx] && a[idx] / 2 != a[l]) return false;
        }
        int r = idx + 1;
        if (r <= n && a[r] != -1) {
            if (a[r] / 2 != a[idx] && a[idx] / 2 != a[r]) return false;
        }
        return true;
    };

    for (int i = 0; i < m - 1; i++) {
        int val1 = a[idx[i]];
        int val2 = a[idx[i + 1]];
        int lidx = idx[i] + 1;
        int ridx = idx[i + 1] - 1;

        while (val1 != val2 && lidx <= ridx) {
            if (val2 > val1) {
                val2 /= 2;
                a[ridx] = val2;
                ridx--;
            } else {
                val1 /= 2;
                a[lidx] = val1;
                lidx++;
            }
        }
        debug(lidx, ridx);

        if (lidx > ridx) {
            if (!check(lidx) || !check(ridx)) {
                cout << -1 << endl;
                return;
            }
        } else {
            int num = ridx - lidx + 1;
            if (num % 2 == 0) {
                cout << -1 << endl;
                return;
            }
            int newval = val1 * 2;
            if (newval > 1e9) newval = val1 / 2;
            for (int i = lidx; i <= ridx; i++) {
                if ((i - lidx) % 2 == 0) {
                    a[i] = newval;
                } else {
                    a[i] = val1;
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
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