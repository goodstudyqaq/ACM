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

// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;

// typedef pair<int, int> pii;
// typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void solve() {
    int n, q;
    cin >> n >> q;
    int m = sqrt(n) + 1;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<vector<long long>>> sum1, sum2;
    sum1.resize(m + 1);
    sum2.resize(m + 1);
    for (int i = 1; i <= m; i++) {
        sum1[i].push_back(vector<long long>{});
        sum2[i].push_back(vector<long long>{});
    }

    // sum1[i][j][k] 跳 i，起始位置为 j，第 k 个数
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= i; j++) {
            sum1[i].push_back(vector<long long>{0});
            sum2[i].push_back(vector<long long>{0});
            for (int k = 1; k <= n; k++) {
                int idx = j + i * (k - 1);
                if (idx > n) break;
                sum1[i][j].push_back(sum1[i][j][k - 1] + a[idx] * k);
                sum2[i][j].push_back(sum2[i][j][k - 1] + a[idx]);
            }
        }
    }
    // debug(m);

    while (q--) {
        int s, d, k;
        cin >> s >> d >> k;
        // debug(s, d, k);
        long long ans = 0;

        if (k <= m) {
            // 暴力
            for (int i = 0; i < k; i++) {
                int idx = s + i * d;
                ans += a[idx] * (i + 1);
            }
            cout << ans << ' ';
        } else {

            // sum1[i][j][k] 跳 i，起始位置为 j，第 k 个数
            int begin = s % d;
            if (begin == 0) begin += d;
            int num = (s - begin) / d;
            long long tmp1 = sum1[d][begin][num + k] - sum1[d][begin][num];
            long long tmp2 = (sum2[d][begin][num + k] - sum2[d][begin][num]) * num;
            ans = tmp1 - tmp2;
            cout << ans << ' ';
        }
    }
    cout << endl;
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