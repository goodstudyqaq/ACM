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

template <typename T>
struct Fenwick {
#define lowbit(x) x & -x
    const int n;
    vector<T> a;
    Fenwick(int n) : n(n), a(n + 1) {}
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    vector<int> pos(n + 1);
    Fenwick<int> fen(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    int LIMIT = 1 << (k + 1);
    const int inf = numeric_limits<int>::max() / 2;
    vector dp = vector(n + 2, vector(LIMIT, inf));
    dp[1][0] = 0;
    int now_inv = 0;

    auto query = [&](int small_num, int status, int choose_num) -> int {
        int res = 0;
        for (int i = 0; i <= k; i++) {
            if ((status >> i) & 1) {
                if (small_num + i > n) break;
                if (pos[small_num + choose_num] < pos[small_num + i]) res++;
            }
        }
        int tmp = fen.query(n) - fen.query(pos[small_num + choose_num]);
        return res + tmp;
    };

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < LIMIT; j++) {
            if (dp[i][j] == inf) continue;
            // [i, i + k - 1] 都可以被选
            // 选 [i + 1, i + k - 1]
            for (int p = 1; p <= k; p++) {
                if ((j >> p) & 1) continue;
                if (i + p > n) continue;
                dp[i][j + (1 << p)] = min(dp[i][j + (1 << p)], dp[i][j] + query(i, j, p));
            }

            // 选 i
            int new_i = i + 1;
            int new_j = j >> 1;
            while (new_j % 2) {
                new_i++;
                new_j >>= 1;
            }
            dp[new_i][new_j] = min(dp[new_i][new_j], dp[i][j] + query(i, j, 0));
        }
        fen.add(pos[i], 1);
    }
    // debug(dp);

    cout << dp[n + 1][0] << endl;
    return 0;
}