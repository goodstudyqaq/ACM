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
    int n, k;
    cin >> n >> k;
    vector c = vector(n, vector(k, 0));
    vector<ll> num(n);
    map<ll, int> M;
    for (int i = 0; i < n; i++) {
        ll val = 0;
        for (int j = 0; j < k; j++) {
            cin >> c[i][j];
            val = 3LL * val + c[i][j];
        }
        num[i] = val;
        M[val] = i;
    }

    ll ans = 0;

    auto get_val = [&](int x, int y) {
        ll res = 0;

        for (int i = 0; i < k; i++) {
            if (c[x][i] == c[y][i]) {
                res = 3LL * res + c[x][i];
            } else {
                for (int j = 0; j < 3; j++) {
                    if (j != c[x][i] && j != c[y][i]) {
                        res = res * 3 + j;
                        break;
                    }
                }
            }
        }
        return res;
    };

    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            ll the_val = get_val(i, j);
            if (M.count(the_val)) {
                cnt++;
            }
        }
        cnt /= 2;
        ans += 1LL * cnt * (cnt - 1) / 2;
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    // ll res = 1;
    // for (int i = 0; i < 20; i++) {
    //     res *= 3;
    // }
    // debug(res);

    solve();
}