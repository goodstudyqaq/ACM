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

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<long long> a(n);
    vector<long long> suma(n);
    vector<pii> v(n + m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        suma[i] = a[i];
        if (i) {
            suma[i] += suma[i - 1];
        }
        v[i] = {a[i], i};
    }

    vector<long long> b(m);

    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());
    vector<long long> sumb(m);
    for (int i = 0; i < m; i++) {
        sumb[i] = b[i];
        if (i) {
            sumb[i] += sumb[i - 1];
        }
        v[i + n] = {b[i], i + n};
    }

    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());

    vector<vector<int>> use(n + m, vector<int>(2));
    vector<long long> sum(n + m);

    for (int i = 0; i < n + m; i++) {
        sum[i] = v[i].first;
        if (v[i].second >= n) {
            use[i][1]++;
        } else {
            use[i][0]++;
        }

        if (i) {
            use[i][0] += use[i - 1][0];
            use[i][1] += use[i - 1][1];
            sum[i] += sum[i - 1];
        }
    }
    // debug(sum);

    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (z == 0) {
            cout << 0 << '\n';
            continue;
        }
        auto it = use[z - 1];
        if (it[0] <= x && it[1] <= y) {
            cout << sum[z - 1] << '\n';
            continue;
        }

        if (it[0] > x) {
            long long tmpa = x == 0 ? 0 : suma[x - 1];
            long long tmpb = (z - x == 0 ? 0 : sumb[z - x - 1]);
            cout << tmpa + tmpb << '\n';
        } else {
            long long tmpb = y == 0 ? 0 : sumb[y - 1];
            long long tmpa = (z - y == 0 ? 0 : suma[z - y - 1]);
            cout << tmpa + tmpb << '\n';
        }
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