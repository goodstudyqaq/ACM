#include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <limits>

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
vector<vector<long long>> dp;

const int N = 60;
void init() {
    const long long inf = numeric_limits<long long>::max() / 2;
    dp.resize(N + 1, vector<long long>(N + 1, inf));
    dp[0][0] = 0;
    for (int i = 1; i <= N; i++) {
        vector<vector<long long>> ndp = dp;
        for (int j = 0; j <= N; j++) {
            for (int k = 0; k <= N; k++) {
                if (j + i <= N) {
                    dp[j + i][k] = min(ndp[j][k] + (1LL << i), dp[j + i][k]);
                }
                if (k + i <= N) {
                    dp[j][k + i] = min(ndp[j][k] + (1LL << i), dp[j][k + i]);
                }
            }
        }
    }
}

void solve() {
    long long x, y;
    cin >> x >> y;

    auto work = [&](long long x) {
        vector<int> v;
        while (x) {
            v.push_back(x % 2);
            x /= 2;
        }
        reverse(v.begin(), v.end());
        return v;
    };
    auto v1 = work(x);
    auto v2 = work(y);
    int sz = min(v1.size(), v2.size());
    int now = 0;
    while (now < sz && v1[now] == v2[now]) {
        now++;
    }

    int left = v1.size() - now;
    int right = v2.size() - now;
    debug(left, right);
    // 左边需要移 left 位 右边移 right 位
    long long ans = numeric_limits<long long>::max() / 2;
    now = 0;
    assert(v1.size() - left == v2.size() - right);
    int tmp = v1.size() - left;
    debug(tmp);
    while (now < tmp) {
        ans = min(ans, dp[left + now][right + now]);
        now++;
    }
    for (int i = v1.size(); i <= N; i++) {
        for (int j = v2.size(); j <= N; j++) {
            ans = min(ans, dp[i][j]);
        }
    }
    cout << ans << '\n';
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}