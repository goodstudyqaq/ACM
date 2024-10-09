#include <bits/stdc++.h>
#include <limits>

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
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < 4; j++) {
            if (s[j] == '#') {
                ans[i] = j;
                break;
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        cout << ans[i] + 1 << ' ';
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