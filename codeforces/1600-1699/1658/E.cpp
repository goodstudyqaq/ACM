#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

typedef pair<int, int> pii;
typedef pair<int, pii> piii;
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, k;
    cin >> n >> k;
    vector<piii> v;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int a;
            cin >> a;
            v.push_back({a, {i, j}});
        }
    }
    sort(v.begin(), v.end(), greater<piii>());
    vector<vector<char>> ans;
    ans.resize(n + 1, vector<char>(n + 1, 'G'));

    auto it = v[0];
    ans[it.second.first][it.second.second] = 'M';
    int v1 = it.second.first + it.second.second;
    int v2 = v1;
    int v3 = it.second.first - it.second.second;
    int v4 = v3;

    auto check = [&](int tmp1, int tmp2) -> bool {
        return abs(v1 - tmp1) <= k && abs(v2 - tmp1) <= k && abs(v3 - tmp2) <= k && abs(v4 - tmp2) <= k;
    };

    for (int i = 1; i < v.size(); i++) {
        auto it = v[i];
        int tmp1 = it.second.first + it.second.second;
        int tmp2 = it.second.first - it.second.second;
        if (check(tmp1, tmp2)) {
            ans[it.second.first][it.second.second] = 'M';
            v1 = min(v1, tmp1);
            v2 = max(v2, tmp1);
            v3 = min(v3, tmp2);
            v4 = max(v4, tmp2);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
    return 0;
}