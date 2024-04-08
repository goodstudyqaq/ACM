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
    int n, x, y;
    cin >> n >> x >> y;
    set<int> S;
    for (int i = 1; i <= x; i++) {
        int c;
        cin >> c;
        c--;
        S.insert(c);
    }
    int ans = max(0, x - 2);

    set<int> bonus;

    auto check = [&](int p) {
        if (S.count(p)) return false;
        int l = (p + 1) % n;
        int r = (p - 1 + n) % n;
        if (S.count(l) && S.count(r)) return true;
        return false;
    };

    for (auto i : S) {
        int p = (i + 1) % n;
        if (check(p)) bonus.insert(p);
        p = (i - 1 + n) % n;
        if (check(p)) bonus.insert(p);
    }
    cout << ans + bonus.size() << endl;
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