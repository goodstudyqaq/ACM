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
    int n, x;
    cin >> n >> x;

    if ((n - x) % 2) {
        cout << 0 << endl;
        return;
    }

    int v1 = (n - x) / 2;

    int ans = 0;
    unordered_set<int> S;
    for (int m = 1; m <= sqrt(v1) + 1; m++) {
        if (v1 % m == 0) {
            // K = v1 / m + 1, M = m
            int k = v1 / m + 1;
            if (k >= x) S.insert(k);

            // K = m + 1, M = v1 / m
            int k2 = m + 1;
            if (k2 >= x && k != k2) S.insert(k2);
        }
    }
    debug(ans);

    if (x >= 2) {
        int v2 = (n + x) / 2;
        for (int i = 0; i <= sqrt(v2) * 2; i++) {
            int m = i;
            int left = v2 + m;
            if (left % (m + 1) == 0) {
                int k = left / (m + 1);
                if (k >= x) S.insert(k);
            }

            int k = i;
            left = v2 - k;
            if (k >= x && left % (k - 1) == 0) {
                S.insert(k);
            }
        }
    }

    cout << S.size() << endl;
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