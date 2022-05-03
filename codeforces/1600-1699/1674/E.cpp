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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    int mi1 = 1e7, mi2 = 1e7;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];

        if (mi1 > a[i]) {
            mi2 = mi1;
            mi1 = a[i];
        } else if (mi2 > a[i]) {
            mi2 = a[i];
        }
    }
    int ans = (mi1 - 1) / 2 + 1 + (mi2 - 1) / 2 + 1;

    auto work1 = [&](int idx) {
        int sum = a[idx] + a[idx + 1];
        return max({(sum + 2) / 3, (a[idx] + 1) / 2, (a[idx + 1] + 1) / 2});
    };

    auto work2 = [&](int idx1, int idx2) {
        int mi = min(a[idx1], a[idx2]);
        int res = mi;
        int tmp = max(a[idx1], a[idx2]) - mi;
        debug(tmp, res);
        if (tmp == 0) return res;
        res += (tmp - 1) / 2 + 1;
        debug(res);
        return res;
    };

    for (int i = 1; i < n; i++) {
        ans = min(ans, work1(i));
        if (i + 2 <= n)
            ans = min(ans, work2(i, i + 2));
    }
    cout << ans << endl;
}