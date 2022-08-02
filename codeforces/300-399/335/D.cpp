#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;

    vector<int> x1, y1, x2, y2;
    x1.resize(n + 1);
    y1.resize(n + 1);
    x2.resize(n + 1);
    y2.resize(n + 1);
    vector<vector<int>> sum, sum_l, sum_r, sum_up, sum_down;
    const int maxn = 3002;
    sum = vect(0, maxn, maxn);
    sum_l = vect(0, maxn, maxn);
    sum_r = vect(0, maxn, maxn);
    sum_up = vect(0, maxn, maxn);
    sum_down = vect(0, maxn, maxn);

    for (int i = 1; i <= n; i++) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        x1[i]++, y1[i]++;
        for (int x = x1[i]; x <= x2[i]; x++) {
            for (int y = y1[i]; y <= y2[i]; y++) {
                sum[x][y] = 1;
            }
        }

        for (int y = y1[i]; y <= y2[i]; y++) {
            // 左边界
            sum_l[x1[i]][y]++;
            // 右边界
            sum_r[x2[i]][y]++;
        }

        for (int x = x1[i]; x <= x2[i]; x++) {
            // 上边界
            sum_up[x][y2[i]]++;
            // 下边界
            sum_down[x][y1[i]]++;
        }
    }

    for (int i = 1; i <= maxn - 1; i++) {
        for (int j = 1; j <= maxn - 1; j++) {
            sum[i][j] = sum[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            sum_l[i][j] += sum_l[i][j - 1];
            sum_r[i][j] += sum_r[i][j - 1];
            sum_up[i][j] += sum_up[i - 1][j];
            sum_down[i][j] += sum_down[i - 1][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        // 左下角
        int x = x1[i], y = y1[i];
        int len = 1;

        for (; sum_l[x][y + len - 1] - sum_l[x][y - 1] == len; len++) {
            int _x2 = x + len - 1, _y2 = y + len - 1;
            if (sum[_x2][_y2] - sum[x - 1][_y2] - sum[_x2][y - 1] + sum[x - 1][y - 1] != len * len) break;
            if (sum_r[_x2][_y2] - sum_r[_x2][y - 1] != len) continue;
            if (sum_up[_x2][_y2] - sum_up[x - 1][_y2] != len) continue;
            if (sum_down[_x2][y] - sum_down[x - 1][y] != len) continue;

            vector<int> ans;
            for (int j = 1; j <= n; j++) {
                int tmpx = x1[j], tmpy = y1[j];
                if (tmpx >= x && tmpx <= _x2 && tmpy >= y && tmpy <= _y2) {
                    ans.push_back(j);
                }
            }
            cout << "YES " << ans.size() << endl;
            for (auto it : ans) {
                cout << it << ' ';
            }
            cout << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}