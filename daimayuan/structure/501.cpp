#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    int n, q;
    cin >> n >> q;
    int B = 500;
    vector<long long> sum(n + 1);
    vector<vector<long long>> tag(B + 1, vector<long long>(B + 1));

    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, y, d;
            cin >> x >> y >> d;
            if (x > B) {
                for (int i = y; i <= n; i += x) {
                    sum[i] += d;
                }
            } else {
                tag[x][y] += d;
            }
        } else {
            int i;
            cin >> i;

            long long res = sum[i];

            for (int x = 1; x <= B; x++) {
                res += tag[x][i % x];
            }
            cout << res << '\n';
        }
    }
}