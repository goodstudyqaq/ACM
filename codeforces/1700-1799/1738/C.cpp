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

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    vector<int> cnt(2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = abs(a[i]);
        cnt[a[i] % 2]++;
    }

    vector dp = vector(2, vector(cnt[0] + 1, vector(cnt[1] + 1, -1)));
    // 1 必胜 0 必败
    function<int(int, int, int)> dfs = [&](int f, int x, int y) -> int {
        // debug(f, x, y);
        if (dp[f][x][y] != -1) return dp[f][x][y];
        if (x == 0 && y == 0) return f == 0;

        if (x == 0) {
            return ((((y + 1) / 2) % 2) ^ f) == 0;
        } else if (y == 0) {
            return f == 0;
        }

        bool flag1 = true, flag2 = true;

        if (x > 0) {
            if (x > 1) {
                int tmp = dfs(f, x - 2, y);
                if (tmp == 0) {
                    flag1 = false;
                }
            }
            if (flag1 && y > 0) {
                int tmp = dfs(f, x - 1, y - 1);
                if (tmp == 0) {
                    flag1 = false;
                }
            }
            if (flag1) return dp[f][x][y] = 1;
        }
        if (y > 0) {
            if (x > 0) {
                int tmp = dfs(f ^ 1, x - 1, y - 1);
                if (tmp == 0) {
                    flag2 = false;
                }
            }
            if (flag2 && y > 1) {
                int tmp = dfs(f ^ 1, x, y - 2);
                if (tmp == 0) {
                    flag2 = false;
                }
            }
            if (flag2) return dp[f][x][y] = 1;
        }
        return dp[f][x][y] = 0;
    };
    debug(cnt[0], cnt[1]);
    int res = dfs(0, cnt[0], cnt[1]);
    if (res) {
        cout << "Alice" << endl;
    } else {
        cout << "Bob" << endl;
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
}