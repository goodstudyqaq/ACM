#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    vector<int> p(n);
    int now = -1;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        if (i != p[i]) {
            if (now == -1) {
                now = p[i];
            } else {
                now &= p[i];
            }
        }
    }
    cout << now << endl;
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
}