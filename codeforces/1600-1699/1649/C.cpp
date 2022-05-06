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

    int n, m;
    cin >> n >> m;
    map<int, vector<int>> row, cow;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int a;
            cin >> a;
            row[a].push_back(i);
            cow[a].push_back(j);
        }
    }

    auto work = [&](map<int, vector<int>>& r) -> long long {
        ll ans = 0;
        for (auto it : r) {
            auto v = it.second;
            sort(v.begin(), v.end());
            ll sum = 0, cnt = 0;
            for (auto it2 : v) {
                ans += cnt * it2 - sum;
                sum += it2;
                cnt++;
            }
        }
        return ans;
    };

    ll ans = work(row) + work(cow);
    cout << ans << endl;
}