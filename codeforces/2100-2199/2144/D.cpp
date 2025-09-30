#include <bits/stdc++.h>

#include <limits>

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
    int n, y;
    cin >> n >> y;
    vector<int> c(n);

    const int maxn = 2e5;
    vector<int> cnt(maxn + 1);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        cnt[c[i]]++;
    }

    for (int i = 1; i <= maxn; i++) {
        cnt[i] += cnt[i - 1];
    }

    const long long inf = numeric_limits<long long>::max();
    long long mx_ans = -inf;
    for (int x = 2; x <= maxn; x++) {
        int now = 1;
        long long ans = 0;
        for (int j = 1; j <= maxn; j += x) {
            // [j, r] 除以 x 都等于 now
            int r = min(j + x - 1, maxn);
            int num = cnt[r] - cnt[j - 1];
            int cost = min(num, cnt[now] - cnt[now - 1]);
            ans += 1LL * num * now - 1LL * y * (num - cost);
            now++;
        }
        mx_ans = max(mx_ans, ans);
    }
    cout << mx_ans << '\n';
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