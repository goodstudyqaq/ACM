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

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

int ask(int idx) {
    cout << "? " << idx << endl;
    fflush(stdout);
    int res;
    cin >> res;
    return res;
}

void tell(int ans) {
    cout << "! " << ans << endl;
    fflush(stdout);
}

void solve() {
    int n, k;
    cin >> n >> k;
    int ans = 0;
    if (n % k == 0) {
        int now = 1;
        while (now < n) {
            int res = ask(now);
            ans ^= res;
            now += k;
        }
        tell(ans);
        return;
    } else {
        int tmp1 = ask(n - k + 1);
        ask(n - k + 1);
        int half = (n % k) / 2;
        int tmp2 = ask(n - half - k + 1);
        int res = tmp1 ^ tmp2;
        int times = n / k;
        for (int i = 0; i < times; i++) {
            int tmp = ask(1 + i * k);
            res ^= tmp;
        }
        tell(res);
        return;
    }
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}