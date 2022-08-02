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
    string s;
    cin >> s;

    vector<int> x(n + 1), y(n + 1), z(n + 1), p(n + 1);

    for (int i = 0; i < n; i++) {
        if (s[i] == '+') {
            x[i + 1] = x[i] + 1;
            y[i + 1] = y[i];
            z[i + 1] = z[i];
        } else {
            if (i - 1 >= 0 && s[i - 1] == '-') {
                x[i + 1] = x[i - 1];
                y[i + 1] = y[i - 1];
                z[i + 1] = z[i - 1] + 1;
            } else {
                x[i + 1] = x[i];
                y[i + 1] = y[i] + 1;
                z[i + 1] = z[i];
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int the_x = x[j] - x[i];
            int the_y = y[j] - y[i];
            int the_z = z[j] - z[i];

            int tmp = the_y + 2 * the_z - the_x;
            if (tmp >= 0 && tmp % 3 == 0 && (tmp / 3) <= the_z) {
                // debug(i, j);
                res++;
            }
        }
    }
    cout << res << endl;
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