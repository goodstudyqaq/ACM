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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, k;
    cin >> n >> k;

    auto work = [&](int n) -> int {
        vector<int> v;
        while (n) {
            v.push_back(n % 2);
            n /= 2;
        }
        reverse(v.begin(), v.end());

        vector<vector<int>> dp(v.size(), vector<int>(v.size() * 2, -1));
        function<int(int, int, bool, bool)> dfs = [&](int d, int sum, bool lead, bool limit) -> int {
            if (d == v.size()) {
                return sum > k;
            }
            if (!limit && dp[d][sum] != -1) return dp[d][sum];
            int LIMIT = limit ? v[d] : 1;
            int res = 0;
            for (int i = 0; i <= LIMIT; i++) {
                if (i == 0) {
                    res += dfs(d + 1, sum, lead, limit & (i == LIMIT));
                } else {
                    if (lead) {
                        res += dfs(d + 1, v.size() - d, false, limit & (i == LIMIT));
                    } else {
                        res += dfs(d + 1, sum + 1, false, limit & (i == LIMIT));
                    }
                }
            }
            return dp[d][sum] = res;
        };

        return dfs(0, 0, true, true);
    };
    cout << work(n) << '\n';
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