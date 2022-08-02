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
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1);
    map<ll, vector<ll>> M;
    map<ll, ll> ans;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        M[a[i]] = {};
    }
    // 不能从 x[i] 的石头里删掉 y[i] 个。
    for (int i = 1; i <= m; i++) {
        ll x, y;
        cin >> x >> y;
        M[x].push_back(x - y);
        // x 不能变成 x - y
    }
    vector<pll> special_vector;
    map<ll, ll> special;
    map<ll, int> count;
    for (auto it : M) {
        // 计算 it.first 的 sg 值
        if (it.second.size() == 0) {
            // 正常值
            int sz = special_vector.size();
            ans[it.first] = it.first - sz;
        } else {
            map<ll, int> tmp_count;
            for (auto val : it.second) {
                if (special.count(val)) {
                    // 特殊值
                    tmp_count[special[val]]++;
                } else {
                    int idx = lower_bound(special_vector.begin(), special_vector.end(), make_pair(1LL * val, -1LL)) - special_vector.begin();
                    tmp_count[val - idx]++;
                }
            }
            bool flag = false;
            for (auto it2 : tmp_count) {
                if (it2.second == count[it2.first] + 1) {
                    special[it.first] = it2.first;
                    special_vector.push_back({it.first, special[it.first]});
                    count[it2.first]++;
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                int sz = special_vector.size();
                ans[it.first] = it.first - sz;
            } else {
                ans[it.first] = special[it.first];
            }
        }
    }

    ll now = 0;
    for (int i = 1; i <= n; i++) {
        now ^= ans[a[i]];
    }
    if (now == 0) {
        cout << "Aoki" << endl;
    } else {
        cout << "Takahashi" << endl;
    }
    return 0;
}