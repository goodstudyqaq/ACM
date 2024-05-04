#include <bits/stdc++.h>

#include <numeric>
#include <queue>

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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<int> f(n);
    iota(f.begin(), f.end(), 0);
    sort(f.begin(), f.end(), [&](int x, int y) {
        if (b[x] != b[y]) {
            return b[x] > b[y];
        }

        return a[x] < a[y];

    });
    debug(f);

    // 按 b 排序

    vector<long long> suf_sum(n + 1);

    for (int i = n - 1; i >= 0; i--) {
        int val = 0;
        int idx = f[i];
        if (b[idx] >= a[idx]) {
            val = b[idx] - a[idx];
        }
        suf_sum[i] = suf_sum[i + 1] + val;
    }

    priority_queue<int> Q;
    long long sum = 0;
    for (int i = 0; i < k; i++) {
        int idx = f[i];
        Q.push(a[idx]);
        sum += a[idx];
    }

    long long ans = 0;
    ans = max(ans, suf_sum[k] - sum);
    debug(ans);
    for (int i = k; i < n; i++) {
        int idx = f[i];
        Q.push(a[idx]);
        int tmp = Q.top();
        Q.pop();
        sum = sum - tmp + a[idx];
        ans = max(ans, suf_sum[i + 1] - sum);
        // debug(i, ans);
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