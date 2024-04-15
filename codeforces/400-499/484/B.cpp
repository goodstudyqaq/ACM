#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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

    int n;
    cin >> n;
    vector<int> a(n + 1);
    set<int> S;

    int mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        S.insert(a[i]);
        mx = max(mx, a[i]);
    }
    const int maxm = mx * 2 + 1;
    vector<int> left(maxm, -1);
    for (int i = 1; i <= n; i++) {
        left[a[i]] = a[i];
    }

    for (int i = 1; i < maxm; i++) {
        if (left[i] != -1) continue;
        left[i] = left[i - 1];
    }

    int ans = 0;
    for (auto x : S) {
        int now = 2 * x;
        while (now < maxm) {
            int the_left = left[now - 1];
            if (the_left >= x) {
                ans = max(ans, the_left % x);
            }
            now += x;
        }
    }
    cout << ans << endl;
}