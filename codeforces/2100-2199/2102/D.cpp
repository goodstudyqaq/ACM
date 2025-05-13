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
    vector<int> p(n + 1);
    set<int> S[2];
    vector<int> idx(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        S[i % 2].insert(p[i]);
        idx[p[i]] = i;
    }

    auto change = [&](int x, int y) {
        swap(p[x], p[y]);
        idx[p[x]] = x;
        idx[p[y]] = y;
    };

    for (int i = 1; i <= n - 3; i++) {
        int mi = *S[i % 2].begin();
        int loc = idx[mi];
        S[i % 2].erase(mi);
        if (loc != n) {
            change(i, loc);
            change(i + 1, loc + 1);
        } else {
            change(loc - 2, loc);
            change(loc - 3, loc - 1);
            loc -= 2;
            change(i, loc);
            change(i + 1, loc + 1);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << p[i] << ' ';
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