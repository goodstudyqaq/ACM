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
    int n, q;
    cin >> n >> q;
    string a, b;
    cin >> a >> b;

    vector<vector<int>> suma(n + 1, vector<int>(26, 0));
    vector<vector<int>> sumb(n + 1, vector<int>(26, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            suma[i + 1][j] = suma[i][j];
            sumb[i + 1][j] = sumb[i][j];
        }
        suma[i + 1][a[i] - 'a']++;
        sumb[i + 1][b[i] - 'a']++;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        vector<int> tmpa(26), tmpb(26);
        for (int i = 0; i < 26; i++) {
            tmpa[i] = suma[r][i] - suma[l - 1][i];
            tmpb[i] = sumb[r][i] - sumb[l - 1][i];
        }

        int res = 0;
        for (int i = 0; i < 26; i++) {
            if (tmpa[i] < tmpb[i]) {
                res += tmpb[i] - tmpa[i];
            }
        }
        cout << res << endl;
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