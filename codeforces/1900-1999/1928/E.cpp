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

const int maxn = 2e5 + 5;
const int limit = 800;
const int inf = numeric_limits<int>::max() / 2;
const int LIMIT = maxn * 3;
vector<int> sqr;
vector<int> dp;
void init() {
    sqr.resize(limit + 1);
    dp.resize(LIMIT + 1, inf);
    for (int i = 1; i <= limit; i++) {
        sqr[i] = i * i - i;
    }

    dp[0] = 0;

    for (int i = 1; i <= LIMIT; i++) {
        for (int j = 1; j <= limit; j++) {
            if (i >= sqr[j]) {
                dp[i] = min(dp[i], dp[i - sqr[j]] + j);
            } else {
                break;
            }
        }
    }
}

void solve() {
    long long n, x, y, s;
    cin >> n >> x >> y >> s;
    int real_x = x % y;

    auto out = [&](int beg, int times) {
        for (int i = 0; i < times; i++) {
            cout << beg << ' ';
            beg += y;
        }
    };

    auto check = [&](int h, int v) -> pair<vector<int>, int> {
        int val = v - h;
        if (h >= dp[val]) {
            debug(val, dp[val]);
            vector<int> ans;
            int now = val;
            while (now) {
                for (int j = 1; j <= limit; j++) {
                    if (dp[now] == dp[now - sqr[j]] + j) {
                        ans.push_back(j);
                        now -= sqr[j];
                        break;
                    }
                }
            }

            int tmp = h - dp[val];
            while (tmp--) ans.push_back(1);

            return {ans, 1};
        }
        return {{}, 0};
    };

    for (int a0 = 1; a0 <= n; a0++) {
        int have_num = n - a0;
        long long delta = 1LL * x * a0 + 1LL * (a0 - 1) * a0 * y / 2;
        long long v = 2LL * (1LL * s - delta - 1LL * real_x * have_num);
        if (v % y) continue;
        if (v < 0) continue;
        v /= y;
        v += have_num;
        debug(a0, have_num, delta, v);
        if ((v - have_num) % 2) continue;
        auto res = check(have_num, v);
        if (res.second == 0) continue;

        cout << "YES" << endl;
        out(x, a0);
        for (auto a : res.first) {
            out(real_x, a);
        }
        cout << endl;
        return;
    }

    cout << "NO" << endl;
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