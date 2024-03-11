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

const double eps = 1e-6;
int z(double x) {
    if (fabs(x) <= eps) return 0;
    if (x > 0)
        return 1;
    else
        return -1;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int s;
    cin >> s;
    double l = 0.0, r = 1e5;

    double tmp = sqrt(2.0);

    auto get_val = [&](double r) {
        int r2 = floor(r / tmp);

        long long val = 1LL * r2 * r2 * 4;
        double tmp = sqrt(1.0 * r2 * r2 + 1.0 * (r2 + 1) * (r2 + 1));
        if (z(r - tmp) == 1) {
            val += 8LL * r2;
        }
        return val;
    };
    // debug(get_val(2));
    double ans = 0;

    for (int i = 0; i < 500; i++) {
        double m = (l + r) / 2.0;
        long long val = get_val(m);
        if (val > s) {
            r = m;
            ans = m;
        } else {
            l = m;
        }
    }
    cout << ans << endl;
}