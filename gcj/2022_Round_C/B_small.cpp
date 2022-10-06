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

void solve() {
    int N, K;
    cin >> N >> K;
    vector<long long> a(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }

    long long tmp1 = 0, tmp2 = 0;
    for (int i = 1; i <= N; i++) {
        tmp1 += a[i];
        for (int j = i + 1; j <= N; j++) {
            tmp2 += a[i] * a[j];
        }
    }
    if (tmp1 == 0 && tmp2 == 0) {
        cout << 1 << endl;
        return;
    }
    // debug(tmp1, tmp2);
    if (tmp1 != 0 && tmp2 % tmp1 == 0) {
        cout << -tmp2 / tmp1 << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
}