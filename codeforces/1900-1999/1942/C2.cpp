#include <bits/stdc++.h>

#include <algorithm>
#include <iterator>

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
    for (int i = 0; i < x; i++) {
        int c;
        cin >> c;
        c--;
        S.insert(c);
    }

    int ans = max(0, x - 2);
    debug(ans);

    auto now = S.begin();

    map<int, int> M, M2;

    while (now != S.end()) {
        set<int>::iterator go;
        if (now == prev(S.end())) {
            go = S.begin();
        } else {
            go = next(now);
        }
        int interval = (*go - *now - 1 + n) % n;
        if (interval % 2)
            M[interval]++;
        else
            M2[interval]++;
        now++;
    }

    ans += M[1];

    int num = M[3];

    int use = min(num, y);
    y -= use;
    ans += use * 3;

    for (auto it : M) {
        if (it.first == 0 || it.first == 1 || it.first == 3) continue;
        if (y == 0) break;
        int interval = it.first;
        int times = it.second;
        for (int i = 0; i < times; i++) {
            int use = min(interval / 2, y);
            debug(interval, use, y);
            y -= use;
            ans += 2 * use;
            if (use == interval / 2) {
                ans++;
            }
        }
    }

    for (auto it : M2) {
        if (it.first == 0) continue;
        if (y == 0) break;
        int interval = it.first;
        int times = it.second;
        for (int i = 0; i < times; i++) {
            int use = min(interval / 2, y);
            debug(interval, use, y);
            y -= use;
            ans += 2 * use;
        }
    }

    cout << ans << endl;
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