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
    int n, m, k;
    cin >> n >> m >> k;
    typedef pair<pll, int> piii;
    vector<piii> V(k);
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        V.push_back({{x, y}, i});
    }
    V.push_back({{0, 1}, k});

    sort(V.begin(), V.end(), [&](piii a, piii b) {
        if (a.first.first != b.first.first) {
            return a.first.first > b.first.first;
        }
        return a.first.second < b.first.second;
    });

    long long ans = 0;

    int now_y = m + 1, now_x = n;
    vector<long long> res(k + 1);
    vector<int> vis(k + 1);
    // vector<int> prex, prey;

    for (int i = 0; i <= k; i++) {
        auto it = V[i];
        int x = it.first.first, y = it.first.second;
        if (y < now_y) {
            res[i] = 1LL * (now_y - 1) * (now_x - x);
            vis[i] = 1;
            ans += res[i];
            now_x = x;
            now_y = y;
        }
    }
    cout << ans << endl;

    now_y = m + 1, now_x = n;
    for (int i = 0; i < k; i++) {
        long long val = res[i];
        if (vis[i] == 0) continue;
        int now2_y = now_y, now2_x = now_x;
        debug(now_x, now_y);
        long long tmp = 0;
        int j;
        for (j = i + 1; j <= k; j++) {
            auto it = V[j];
            int x = it.first.first, y = it.first.second;
            if (y < now2_y) {
                tmp += 1LL * (now2_y - 1) * (now2_x - x);
                now2_x = x;
                now2_y = y;
            }
            if (vis[j] > 0) {
                break;
            }
        }
        // debug(i, tmp, val, now2_x, now2_y);  
        now_x = V[i].first.first, now_y = V[i].first.second;
        res[i] = tmp - val - res[j];
    }

    vector<long long> real_res(k);

    for (int i = 0; i < k; i++) {
        real_res[V[i].second] = res[i];
    }
    for (int i = 0; i < k; i++) {
        cout << real_res[i] << ' ';
    }
    cout << endl;
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