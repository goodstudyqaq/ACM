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
    ll n, m;
    cin >> n >> m;
    vector<int> cnt(21);
    vector<bool> vis(20 * m + 1, 0);
    int sum = 0;
    for (int i = 1; i <= 20; i++) {
        for (int j = i; j <= m * i; j += i) {
            if (vis[j]) continue;
            vis[j] = 1;
            sum++;
        }
        cnt[i] = sum;
    }
    debug("done1");
    ll ans = 1;
    vector<int> vis2(n + 1);

    for (int i = 2; i <= n; i++) {
        if (vis2[i]) continue;
        // debug(i);
        ll now = i, now_cnt = 0;
        while (now <= n) {
            vis2[now] = 1;
            now_cnt++;
            now *= i;
        }
        // debug(now_cnt, cnt[now_cnt]);
        ans += cnt[now_cnt];
    }
    cout << ans << endl;
    return 0;
}