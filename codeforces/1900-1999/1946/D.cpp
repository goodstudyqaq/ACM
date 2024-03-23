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
struct DSU {
    std::vector<int> f;
    DSU(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        return true;
    }
};

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = -1;
    DSU dsu(n + 1);

    int i;
    for (i = 29; i >= 0; i--) {
        int aim = (x >> i) & 1;

        vector<int> idx;
        for (int j = 1; j <= n; j++) {
            if ((a[j] >> i) & 1) {
                idx.push_back(j);
            }
        }
        int num = idx.size();
        if (aim == 0 && num % 2) break;

        // aim == 0 and num % 2 == 0
        if (aim == 0) {
            for (int j = 0; j < num; j += 2) {
                int now = idx[j];
                while (true) {
                    int fa = dsu.leader(now);
                    if (fa >= idx[j + 1]) break;
                    dsu.merge(fa, fa + 1);
                }
            }
        } else if (aim == 1) {
            // aim == 1
            if (num % 2 == 0) {
                // 可以变成 0 也可以变成 1
                DSU tmp = dsu;

                for (int j = 0; j < num; j += 2) {
                    int now = idx[j];
                    while (true) {
                        int fa = tmp.leader(now);
                        if (fa >= idx[j + 1]) break;
                        tmp.merge(fa, fa + 1);
                    }
                }

                int res = 0;
                int now = 1;
                while (now <= n) {
                    res++;
                    now = tmp.leader(now) + 1;
                }
                ans = max(ans, res);

            } else {
                // 只会变成 1 所以不管
                continue;
            }
        }
    }

    if (i == -1) {
        // 全部相等，也可以接受
        int now = 1;
        int res = 0;
        while (now <= n) {
            res++;
            now = dsu.leader(now) + 1;
        }
        ans = max(ans, res);


    }

    cout << ans << endl;
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