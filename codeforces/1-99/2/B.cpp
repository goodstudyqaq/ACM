#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;
const int maxn = 1005;

int a[maxn][maxn];
int two[maxn][maxn];
int five[maxn][maxn];

typedef array<int, 2> a2;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    bool have_zero = false;
    int zero_x, zero_y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];

            int val = a[i][j];
            if (val == 0) {
                two[i][j] = five[i][j] = 1e9;
                zero_x = i, zero_y = j;
                have_zero = true;
                continue;
            }
            while (val % 2 == 0) {
                two[i][j]++;
                val /= 2;
            }
            while (val % 5 == 0) {
                five[i][j]++;
                val /= 5;
            }
        }
    }

    auto work = [&](int x[maxn][maxn], int y[maxn][maxn]) {
        vector<vector<a2>> dp(2, vector<a2>(n));     // {i, j} 有 i 个 2 j 个 5 ？以 2 小为主？
        vector<vector<int>> dir(n, vector<int>(n));  // 0 从上面， 1 从左边

        for (int i = 0; i < n; i++) {
            int f = i % 2;
            for (int j = 0; j < n; j++) {
                if (i == 0) {
                    if (j == 0) {
                        dp[f][j] = {x[i][j], y[i][j]};
                    } else {
                        dp[f][j] = {dp[f][j - 1][0] + x[i][j], dp[f][j - 1][1] + y[i][j]};
                        dir[i][j] = 1;
                    }
                } else {
                    dp[f][j] = {dp[f ^ 1][j][0] + x[i][j], dp[f ^ 1][j][1] + y[i][j]};
                    dir[i][j] = 0;
                    if (j != 0) {
                        a2 it = {dp[f][j - 1][0] + x[i][j], dp[f][j - 1][1] + y[i][j]};
                        if (dp[f][j] > it) {
                            dp[f][j] = it;
                            dir[i][j] = 1;
                        }
                    }
                }
            }
        }
        return make_pair(dp[(n - 1) % 2], dir);
    };
    auto res1 = work(two, five);
    auto res2 = work(five, two);

    auto out = [&](vector<vector<int>> dir) {
        int x = n - 1, y = n - 1;

        string s = "";
        while (x || y) {
            assert(x >= 0 && y >= 0);
            if (dir[x][y] == 0) {
                s += "D";
                x -= 1;
            } else {
                s += "R";
                y -= 1;
            }
        }
        reverse(s.begin(), s.end());
        cout << s << '\n';
    };

    int ans1 = min(res1.first[n - 1][0], res1.first[n - 1][1]);
    int ans2 = min(res2.first[n - 1][0], res2.first[n - 1][1]);

    auto special_work = [&]() {
        for (int i = 0; i < zero_x; i++) {
            cout << 'D';
        }

        for (int i = 0; i < n - 1; i++) {
            cout << 'R';
        }
        for (int i = zero_x; i < n - 1; i++) {
            cout << 'D';
        }
        cout << '\n';
    };

    if (ans1 > 1 && ans2 > 1 && have_zero) {
        cout << 1 << '\n';
        special_work();
        return 0;
    }

    if (ans1 < ans2) {
        cout << ans1 << '\n';
        out(res1.second);
    } else {
        cout << ans2 << '\n';
        out(res2.second);
    }
}