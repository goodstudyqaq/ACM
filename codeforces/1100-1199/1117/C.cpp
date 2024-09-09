#include <bits/stdc++.h>

#include <limits>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int x1, y1;
    int x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x2 -= x1;
    y2 -= y1;
    int n;
    string s;
    cin >> n >> s;

    vector<pair<int, int>> loc(n);
    for (int i = 0; i < n; i++) {
        if (i - 1 >= 0) {
            loc[i] = loc[i - 1];
        }
        if (s[i] == 'U') {
            loc[i].second++;
        } else if (s[i] == 'D') {
            loc[i].second--;
        } else if (s[i] == 'L') {
            loc[i].first--;
        } else {
            loc[i].first++;
        }
    }

    long long l = 0, r = numeric_limits<long long>::max() / 2;
    long long ans = -1;

    auto check = [&](long long step) -> bool {
        long long times = step / n;
        long long x = 1LL * loc[n - 1].first * times;
        long long y = 1LL * loc[n - 1].second * times;
        int left = step % n;
        if (left) {
            x += loc[left - 1].first;
            y += loc[left - 1].second;
        }

        long long tmp = abs(x - x2) + abs(y - y2);
        return tmp <= step;
    };

    while (l <= r) {
        long long m = l + r >> 1;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << ans << endl;
}