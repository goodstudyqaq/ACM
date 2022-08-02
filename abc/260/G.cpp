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

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    int q;
    cin >> q;
    vector<vector<pii>> V(n);
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        V[x].push_back({y, i});
    }
    vector<int> ans(q);

    vector<int> sum(2 * m + n);
    vector<int> r(2 * m + n);

    vector<vector<int>> l(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == 'O') {
                l[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int up_row = i - m;
        if (up_row >= 0) {
            for (auto it : l[up_row]) {
                sum[it]--;
                sum[it + 1]--;
                r[it + 1]--;
            }
        }
        for (int i = 3; i <= 2 * m + n - 1; i++) {
            sum[i] -= r[i];
            sum[i - 1] -= r[i];
            r[i - 2] = r[i];
        }
        r[2 * m + n - 1] = r[2 * m + n - 2] = 0;

        vector<int> tmp_sum(2 * m + n);
        for (auto it : l[i]) {
            int the_r = 2 * m + it - 1;
            r[the_r]++;
            tmp_sum[it]++;
            tmp_sum[the_r + 1]--;
        }
        for (int i = 0; i <= 2 * m + n - 2; i++) {
            if (i) tmp_sum[i] += tmp_sum[i - 1];
            sum[i] += tmp_sum[i];
        }

        for (auto it : V[i]) {
            ans[it.second] = sum[it.first];
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}