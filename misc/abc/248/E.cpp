#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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

    int n, k;
    cin >> n >> k;

    vector<long long> x, y;
    x.resize(n + 1);
    y.resize(n + 1);
    map<int, int> M;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        M[x[i]]++;
    }

    if (k == 1) {
        cout << "Infinity" << endl;
        return 0;
    }

    long long ans = 0;
    for (auto it : M) {
        if (it.second >= k) {
            ans++;
        }
    }

    vector<long long> ans2(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (x[i] == x[j]) continue;
            int cnt = 0;
            for (int k = 1; k <= n; k++) {
                if ((y[k] - y[i]) * (x[j] - x[i]) == (y[j] - y[i]) * (x[k] - x[i])) {
                    cnt++;
                }
            }
            ans2[cnt]++;
        }
    }
    for (int i = k; i <= n; i++) {
        ans += 1LL * ans2[i] * 2 / i / (i - 1);
    }
    cout << ans << endl;

    return 0;
}