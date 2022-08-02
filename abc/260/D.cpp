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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> ans(n + 1, -1);
    if (k == 1) {
        for (int i = 1; i <= n; i++) {
            int val = a[i];
            ans[val] = i;
        }
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << endl;
        }
        return 0;
    }
    set<pii> S;
    vector<int> to(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        int val = a[i];
        auto it = S.lower_bound({val, -1});
        if (it == S.end()) {
            S.insert({val, 1});
        } else {
            pii it2 = *it;
            if (it2.second == k - 1) {
                to[val] = it2.first;
                int now = val;
                while (to[now] != -1) {
                    ans[now] = i;
                    now = to[now];
                }
                ans[now] = i;
                S.erase(it);
            } else {
                to[val] = it2.first;
                S.erase(it);
                S.insert({val, it2.second + 1});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}