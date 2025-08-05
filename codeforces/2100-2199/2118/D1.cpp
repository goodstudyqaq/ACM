#include <bits/stdc++.h>

#include <algorithm>

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

template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<long long> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    vector<int> delay(n);
    for (int i = 0; i < n; i++) {
        cin >> delay[i];
    }

    int q;
    cin >> q;

    auto dp = vect(-1, n, k, 2);  // -1 没碰到过，0: 没有环，1 有环 2 在栈中
    typedef array<int, 3> a3;

    function<int(int, int, int)> dfs = [&](int s, int t, int f) -> int {
        // debug(s, t, f, dp[s][t][f], dp);
        if (dp[s][t][f] == 0 || dp[s][t][f] == 1) {
            return dp[s][t][f];
        } else if (dp[s][t][f] == 2) {
            return dp[s][t][f] = 1;
        } else {
            dp[s][t][f] = 2;
            if (s == 0 && f == 0) {
                return dp[s][t][f] = 0;
            }
            if (s == n - 1 && f == 1) {
                return dp[s][t][f] = 0;
            }
            if (f == 0) {
                // 左边
                long long dis = (p[s] - p[s - 1]) % k;
                int t2 = (t + dis) % k;
                int res = dfs(s - 1, t2, f ^ (t2 == delay[s - 1]));
                return dp[s][t][f] = res;
            } else {
                long long dis = (p[s + 1] - p[s]) % k;
                int t2 = (t + dis) % k;
                int res = dfs(s + 1, t2, f ^ (t2 == delay[s + 1]));
                dp[s][t][f] = res;
                return res;
            }
        }
    };

    auto check = [&](long long start) -> bool {
        // 出去返回 true
        long long now_time = 0;
        int idx = lower_bound(p.begin(), p.end(), start) - p.begin();

        if (idx == n) {
            return true;
        }

        // 0 左 1 右
        long long dis = p[idx] - start;
        (now_time += dis) %= k;
        // debug(idx, now_time, delay[idx]);

        if (now_time == delay[idx]) {
            auto res = dfs(idx, now_time, 0);
            return !res;
        } else {
            auto res = dfs(idx, now_time, 1);
            return !res;
        }
    };

    while (q--) {
        long long a;
        cin >> a;
        if (!check(a)) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
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