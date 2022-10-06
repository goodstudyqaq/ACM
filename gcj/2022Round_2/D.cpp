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

void solve() {
    vector<array<int, 2>> s1, s2;
    int n;
    ll c;
    cin >> n >> c;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if (a < 0) {
            s1.push_back({-2 * a, b});
        } else {
            s2.push_back({2 * a, b});
        }
    }

    auto work = [&](vector<array<int, 2>> s) -> ll {
        sort(s.begin(), s.end());

        int n = s.size();
        vector<vector<ll>> sum;
        sum = vector(2, vector(n + 1, 0LL));

        for (int i = 0; i < n; i++) {
            sum[0][i + 1] = sum[0][i];
            sum[1][i + 1] = sum[1][i];
            sum[s[i][1]][i + 1] += s[i][0];
        }
        vector<ll> dp(n + 1);
        map<ll, ll> last;
        last[0] = 0;
        int now = 0;
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            auto it = s[i - 1];
            now += (it[1] == 0 ? 1 : -1);
            if (i == 1) {
                dp[i] = sum[it[1]][1];
            } else {
                auto it2 = s[i - 2];
                dp[i] = min({dp[i - 1] + it[0], dp[i - 2] + it[0] + c * (it2[1] == it[1])});
            }
            if (last.count(now)) {
                int j = last[now];
                if (s[j][1] == 0) {
                    dp[i] = min(dp[i], dp[j] + sum[1][i] - sum[1][j]);
                } else {
                    dp[i] = min(dp[i], dp[j] + sum[0][i] - sum[0][j]);
                }
            }
            last[now] = i;
        }
        return dp[n];
    };

    cout << work(s1) + work(s2) << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";

        solve();
    }
}