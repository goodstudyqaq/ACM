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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    map<int, int> M;
    map<int, int> M2;
    map<int, int> mi_cost;

    auto work = [&](int val, map<int, int>& M, int cost) {
        for (int j = 2; j * j <= val; j++) {
            if (val % j == 0) {
                M[j]++;
                if (cost != -1) {
                    if (mi_cost.count(j)) {
                        mi_cost[j] = min(mi_cost[j], cost);
                    } else {
                        mi_cost[j] = cost;
                    }
                }

                while (val % j == 0) {
                    val /= j;
                }
            }
        }
        if (val != 1) {
            M[val]++;
            if (cost != -1) {
                if (mi_cost.count(val)) {
                    mi_cost[val] = min(mi_cost[val], cost);
                } else {
                    mi_cost[val] = cost;
                }
            }
        }
    };

    for (int i = 0; i < n; i++) {
        int val = a[i];
        work(val, M, -1);
        work(val + 1, M2, b[i]);
    }
    for (auto it : M) {
        if (it.second > 1) {
            cout << 0 << '\n';
            return;
        }
    }

    int ans = 2e9 + 1;
    for (auto it : M) {
        if (it.second >= 1 && M2.count(it.first) && M2[it.first] >= 1) {
            ans = min(ans, mi_cost[it.first]);
        }
    }
    auto b2 = b;
    sort(b2.begin(), b2.end());
    ans = min(ans, b2[0] + b2[1]);

    int idx = 0;
    for (int i = 0; i < n; i++) {
        if (b[i] == b2[0]) {
            idx = i;
            break;
        }
    }

    int val = a[idx];
    debug(idx);

    for (int j = 2; j * j <= val; j++) {
        if (val % j == 0) {
            M[j]--;
            while (val % j == 0) {
                val /= j;
            }
        }
    }
    if (val != 1) {
        M[val]--;
    }

    for (auto it : M) {
        if (it.second == 0) continue;
        int tmp = a[idx] % it.first;
        ans = min(1LL * ans, 1LL * (it.first - tmp) * b[idx]);
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