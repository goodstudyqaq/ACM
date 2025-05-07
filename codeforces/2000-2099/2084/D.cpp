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

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    auto check = [&](int len) {
        // len 个循环
        int have = n / len;
        return have > m;
    };
    auto work = [&](int len) {
        vector<int> a(n);
        for (int i = 0; i < len; i++) {
            a[i] = i;
        }
        for (int i = len; i < n; i++) {
            a[i] = a[i - len];
        }
        for (int i = 0; i < n; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
    };

    for (int i = n; i > k; i--) {
        if (check(i)) {
            work(i);
            return;
        }
    }
    work(k);
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