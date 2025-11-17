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
    int n;
    cin >> n;
    vector<int> a(n + 1), loc(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        loc[a[i]] = i;
    }

    while (true) {
        bool change = false;
        // debug(loc);
        for (int i = n; i >= 1; i--) {
            int val = a[i];
            if (val >= 3 && loc[val - 1] > i && loc[val - 2] > i) {
                int l1 = loc[val - 1];
                int l2 = loc[val - 2];
                a[i] -= 2;
                a[l1]++;
                a[l2]++;
                loc[a[i]] = i;
                loc[a[l1]] = l1;
                loc[a[l2]] = l2;
                change = true;
                break;
            }
        }
        if (!change) break;
    }

    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
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