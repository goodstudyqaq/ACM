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
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int n;
    cin >> n;
    int l = 1, r = n - 1;
    int ans = -1;
    int t = 0, v = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        int q = (n - mid + n - t % n) % n;
        cout << "+ " << q << endl;
        fflush(stdout);
        t += q;
        int res;
        cin >> res;
        if (res == v) {
            r = mid - 1;
        } else {
            ans = mid;
            l = mid + 1;
        }
        v = res;
    }
    debug(ans);
    cout << "! " << t + ans << endl;
    return 0;
}