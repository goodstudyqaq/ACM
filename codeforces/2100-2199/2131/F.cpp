#include <bits/stdc++.h>

#include "structure/others/binary-indexed-tree.hpp"

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
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    vector<int> suma(n + 1), sumb(n + 1);
    for (int i = 0; i < n; i++) {
        suma[i + 1] = (a[i] == '0');
        suma[i + 1] += suma[i];
    }
    for (int i = 0; i < n; i++) {
        sumb[i + 1] = (b[i] == '0');
        sumb[i + 1] += sumb[i];
    }
    int offset = n + 1;

    // 2n + 1
    const int m = 2 * n + 1;
    BIT<long long> bit(m), bit2(m);
    BIT<int> bit3(m);

    for (int i = 1; i <= n; i++) {
        int idx = i - 2 * sumb[i] + offset;
        bit.add(idx, sumb[i]);
        bit2.add(idx, i - sumb[i]);
        bit3.add(idx, 1);
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int idx = 2 * suma[i] - i + offset;
        long long v1 = bit.query(m) - bit.query(idx - 1);
        int num = bit3.query(idx - 1);
        int num2 = bit3.query(m);
        ans += v1 + 1LL * (num2 - num) * suma[i];

        long long v2 = bit2.query(idx - 1);
        // debug(i, v1, v2, num, num2);
        ans += v2 + 1LL * num * (i - suma[i]);
    }
    cout << ans << '\n';
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