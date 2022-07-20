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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    int cnta = 0, cntb = 0;
    vector<vector<int>> a, b;
    a.resize(2, vector<int>(n));
    b.resize(2, vector<int>(n));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            cnta += a[i][j];
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
            cntb += b[i][j];
        }
    }
    if (cnta != cntb) {
        cout << -1 << endl;
        return 0;
    }

    int now[2] = {0, 0};
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            now[j] += a[j][i];
            now[j] -= b[j][i];
        }

        if (now[0] > 0 && now[1] < 0) {
            int mi = min(now[0], -now[1]);
            ans += mi;
            now[0] -= mi;
            now[1] += mi;
        } else if (now[0] < 0 && now[1] > 0) {
            int mi = min(-now[0], now[1]);
            ans += mi;
            now[0] += mi;
            now[1] -= mi;
        }
        ans += abs(now[0]) + abs(now[1]);
    }
    cout << ans << endl;
}