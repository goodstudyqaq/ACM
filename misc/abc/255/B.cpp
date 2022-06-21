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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    vector<pii> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i].first >> p[i].second;
    }

    double l = 0, r = 1e9;

    auto get_dis = [&](int i, int j) {
        double x = p[i].first - p[j].first;
        double y = p[i].second - p[j].second;
        return sqrt(x * x + y * y);
    };

    auto check = [&](double r) {
        vector<bool> vis(n + 1);
        for (int i = 0; i < k; i++) {
            int idx = a[i];
            for (int j = 1; j <= n; j++) {
                double dis = get_dis(idx, j);
                if (dis <= r) {
                    vis[j] = 1;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) return false;
        }
        return true;
    };

    for (int t = 0; t <= 50; t++) {
        double mid = (l + r) / 2.0;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    cout << l << endl;
    return 0;
}