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
    int n, k;
    cin >> n >> k;
    int x = 0;
    vector<int> v;
    while (n) {
        int val = n % 3;
        v.push_back(val);
        n /= 3;
    }

    long long cnt = 0;
    int sz = v.size();
    for (int i = 0; i < sz; i++) {
        cnt += v[i];
    }

    if (cnt > k) {
        cout << -1 << '\n';
        return;
    }

    for (int i = sz - 1; i > 0; i--) {
        if (v[i] > 0) {
            int after = cnt + 2 * v[i];
            if (after <= k) {
                v[i - 1] += 3 * v[i];
                v[i] = 0;
                cnt = after;
            } else {
                // 移 1 个会多 2
                int have = k - cnt;
                int num = have / 2;
                v[i] -= num;
                v[i - 1] += 3 * num;
                break;
            }
        }
    }

    long long ans = 0;
    long long three = 1;
    debug(v);
    for (int i = 0; i < sz; i++) {
        ans += (three * 3 + 1LL * i * three / 3) * v[i];
        three *= 3;
    }
    cout << ans << '\n';
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