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

    auto work = [&](int x, int y, int z) {
        a[x] -= 2;
        a[y] += 1;
        a[z] += 1;
        loc[a[x]] = x;
        loc[a[y]] = y;
        loc[a[z]] = z;
    };

    while (true) {
        bool change = false;
        // debug(loc);
        for (int val = 3; val <= n; val++) {
            int loc1 = loc[val];
            int loc2 = loc[val - 1];
            int loc3 = loc[val - 2];
            if (loc1 < loc2 && loc1 < loc3) {
                int a = loc1;
                int b = min(loc2, loc3);
                int c = max(loc2, loc3);
                work(a, b, c);
                change = true;
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