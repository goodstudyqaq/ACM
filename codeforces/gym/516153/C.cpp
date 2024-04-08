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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> v;
    int m = 1;
    bool flag = false;
    const int limit = 1e6;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > 1) {
            v.push_back(i);
            if (m > limit / a[i]) {
                flag = true;
            } else {
                m = m * a[i];
            }
        }
    }
    if (flag) {
        // 全包括
        cout << v[0] << ' ' << v.back() << endl;
        return;
    }

    if (v.size() == 0) {
        cout << 1 << ' ' << 1 << endl;
        return;
    }

    // < 17

    vector<int> sum(n + 1);
    vector<int> mul(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
        mul[i] = mul[i - 1] * a[i];
    }
    int ans = sum[n];
    int l = 1, r = 1;
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            int tmp = mul[v[j]] / mul[v[i] - 1] + sum[n] - (sum[v[j]] - sum[v[i] - 1]);
            if (ans < tmp) {
                ans = tmp;
                l = v[i], r = v[j];
            }
            // ans = max(ans, tmp);
        }
    }
    cout << l << ' ' << r << endl;
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