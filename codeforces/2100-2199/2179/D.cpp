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
typedef array<int, 2> a2;

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
    int limit = (1 << n) - 1;
    set<int> S;
    for (int i = 0; i <= limit; i++) {
        S.insert(i);
    }

    int now = limit;

    while (now) {
        cout << now << ' ';
        S.erase(now);

        for (int i = now; i <= limit; i = (i + 1) | now) {
            if (S.count(i)) {
                cout << i << ' ';
                S.erase(i);
            }
        }
        // cout << '\n';
        now >>= 1;
    }

    for (auto it : S) {
        cout << it << ' ';
    }

    cout << '\n';
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