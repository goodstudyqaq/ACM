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
    vector<long long> a(N + 2);
    long long sum = 0;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        sum += a[i];
    };

    auto work = [&](int n) {
        long long s1 = 0, s2 = 0;

        for (int i = 1; i <= n; i++) {
            s1 += a[i];
            for (int j = i + 1; j <= n; j++) {
                s2 += a[i] * a[j];
            }
        }

        if (s1 == 0 && s2 == 0) {
            cout << 1 << endl;
        } else if (s1 == 0 || s2 % s1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << -s2 / s1 << endl;
        }
    };

    if (K == 1) {
        work(N);
    } else {
        a[N + 1] = -sum + 1;
        cout << -sum + 1 << ' ';
        work(N + 1);
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