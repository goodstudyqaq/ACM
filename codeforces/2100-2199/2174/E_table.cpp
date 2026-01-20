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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, m, p;
    cin >> n >> m >> p;

    // 长度为 n，m 个不同颜色
    ll down = 1;
    for (int i = 0; i < n; i++) {
        down *= m;
    }

    vector<int> now(n);
    ll up = 0;
    
    auto check2 = [&](int l, int r) {
        for (int i = l; i <= (l + r) / 2; i++) {
            if (now[i] != now[l + r - i]) return false;
        }
        return true;
    };

    auto check = [&]() {
        int tmp = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (check2(i, j)) {
                    tmp++;
                }
            }
        }
        debug(tmp);
        up += tmp * tmp;
    };


    function<void(int)> dfs = [&](int d) {
        if (d == n) {
            check();
            return;
        }
        for (int i = 0; i < m; i++) {
            now[d] = i;
            dfs(d + 1);
        }
    }; 


    dfs(0);
    debug(up, down, gcd(up, down));

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