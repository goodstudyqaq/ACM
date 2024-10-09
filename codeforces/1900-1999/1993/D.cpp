#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> x;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        x.push_back(a[i]);
    }
    debug(a);
    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());

    int need = n % m;
    if (need == 0)
        need = m - 1;
    else
        need--;

    int tmp = n % m;
    if (tmp == 0) tmp += m;

    int l = 0, r = x.size() - 1;
    int ans = -1;
    int mid = (tmp + 1) / 2;
    int cnt = tmp - mid + 1;
    vector<int> dp(n);
    debug(need);

    function<int(int, int)> dfs = [&](int idx, int limit) -> int {
        // debug(idx, limit);
        if (dp[idx] != -1) return dp[idx];
        int len = idx % m;
        if (len == need) {
            // 不选
            int res = 0;
            if (idx + m < n) {
                res = max(res, dfs(idx + m, limit));
            }
            if (res >= cnt) {
                return dp[idx] = res;
            }

            // 选 idx
            res = max(res, int(a[idx] >= limit));
            if (res >= cnt) {
                return dp[idx] = res;
            }
            return dp[idx] = res;
        } else {
            // 不选
            int res = 0;
            if (idx + m < n) {
                res = max(res, dfs(idx + m, limit));
            }
            if (res >= cnt) {
                return dp[idx] = res;
            }

            // 选 idx
            res = max(res, (a[idx] >= limit) + dfs(idx + 1, limit));
            if (res >= cnt) {
                return dp[idx] = res;
            }
            return dp[idx] = res;
        }
    };

    auto check = [&](int val) -> bool {
        for (int i = 0; i < n; i++) {
            dp[i] = -1;
        }

        int res = dfs(0, val);
        return res >= cnt;
    };

    while (l <= r) {
        int m = l + r >> 1;
        if (check(x[m])) {
            ans = x[m];
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    cout << ans << endl;
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