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
    long long n, m;
    cin >> n >> m;
    if (m == 0) {
        cout << n << endl;
        return;
    }

    long long res = 0;

    for (int i = 50; i >= 0; i--) {
        long long v = 1LL << i;
        if ((n >> i) & 1) {
            res += v;
            continue;
        }

        if (n < v) {
            long long need = v - n % v;
            
            if (m >= need) {
                debug(m, need, i);
                res += v;
            }
        } else {
            long long tmp0 = n % v + 1;
            long long tmp1 = v - n % v;
            long long need = min(tmp0, tmp1);
            if (m >= need) {
                res += v;
            }
        }
    }
    cout << res << endl;
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