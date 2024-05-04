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
    int n, k;
    cin >> n >> k;

    vector<int> ans;

    int r = 0;

    while (r < k) {
        if (r + r + 1 < k) {
            ans.push_back(r + 1);
            r = r + r + 1;
        } else {
            break;
        }
    }

    int val = k - r - 1;
    if (val != 0) {
        ans.push_back(val);
    }
    r = k - 1;
    if (k != n) {
        ans.push_back(k + 1);
        // [1, 2k] 全都有 除了 k
        r += k + 1;
        if (r < n) {
            ans.push_back(2 * k);
            r += 2 * k;
            // [1, 4k 全都有，除了 k, 3k]
        }

        r = 3 * k - 1;
        int now = 3 * k;
        while (r < n) {
            ans.push_back(now);
            r += now;
            now *= 2;
        }
    }

    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it << ' ';
    }
    cout << endl;
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