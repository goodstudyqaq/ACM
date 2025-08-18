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
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    auto work = [&](vector<int> &x, vector<int> &y) -> long long {
        int mi_x = *min_element(x.begin(), x.end());
        int mx_x = *max_element(x.begin(), x.end());

        int mi_y = *min_element(y.begin(), y.end());
        int mx_y = *max_element(y.begin(), y.end());
        int num = count_if(x.begin(), x.end(), [&](int val) { return val == mi_x; });
        if (num == 1) {
            int idx = min_element(x.begin(), x.end()) - x.begin();

            mi_x = 1e9, mx_x = -1e9, mi_y = 1e9, mx_y = -1e9;
            for (int i = 0; i < n; i++) {
                if (i == idx) continue;
                mi_x = min(mi_x, x[i]);
                mx_x = max(mx_x, x[i]);
                mi_y = min(mi_y, y[i]);
                mx_y = max(mx_y, y[i]);
            }

            long long tmp = 1LL * (mx_x - mi_x + 1) * (mx_y - mi_y + 1);
            if (tmp == n - 1) {
                long long X = mx_x - mi_x + 1;
                long long Y = mx_y - mi_y + 1;
                return min((X + 1) * Y, X * (Y + 1));
            } else {
                return tmp;
            }

        } else {
            return 1LL * (mx_x - mi_x + 1) * (mx_y - mi_y + 1);
        }
    };

    long long ans1 = work(x, y);
    for (int i = 0; i < n; i++) {
        x[i] = -x[i];
    }
    long long ans2 = work(x, y);
    for (int i = 0; i < n; i++) {
        x[i] = -x[i];
    }

    for (int i = 0; i < n; i++) {
        swap(x[i], y[i]);
    }
    long long ans3 = work(x, y);
    for (int i = 0; i < n; i++) {
        x[i] = -x[i];
    }
    long long ans4 = work(x, y);
    cout << min({ans1, ans2, ans3, ans4}) << '\n';
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