#include <bits/stdc++.h>

#include <cstdio>
#include <vector>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

void solve() {
    int n;
    cin >> n;

    auto out = [&](vector<int> ans1, vector<int> ans2) {
        cout << "!";
        for (int i = 0; i < n; i++) {
            cout << " " << ans1[i] + 1;
        }
        for (int i = 0; i < n; i++) {
            cout << " " << ans2[i] + 1;
        }
        cout << endl;
        fflush(stdout);
        int res;
        cin >> res;
    };

    if (n == 2) {
        out({0, 1}, {1, 0});
        return;
    }

    vector<int> order;
    int l = 0, r = n - 1;

    while (l <= r) {
        order.push_back(r);
        r--;
        if (l > r) break;
        order.push_back(l);
        l++;
    }
    debug(order);

    auto add = [&](int sum) {
        cout << "+ " << sum << endl;
        fflush(stdout);
        int tmp;
        cin >> tmp;
    };

    vector<vector<int>> cache(n, vector<int>(n, -1));
    auto ask = [&](int x, int y) {
        if (cache[x][y] != -1) {
            return cache[x][y];
        }
        if (x == y) {
            return 0;
        }
        cout << "? " << x + 1 << ' ' << y + 1 << endl;
        fflush(stdout);
        int r;
        cin >> r;
        cache[x][y] = r;
        cache[y][x] = r;
        return r;
    };

    add(n + 1);
    add(n);

    vector<int> tmp_res(n);
    int mx = 0;
    for (int i = 1; i < n; i++) {
        int tmp = ask(0, i);
        tmp_res[i] = tmp;
        mx = max(mx, tmp);
    }

    auto work = [&](int idx, vector<int> &ans) {
        ans[0] = order[idx];
        if (idx == 0) {
            for (int i = 1; i < n; i++) {
                int tmp = tmp_res[i];
                ans[i] = order[tmp];
            }
        } else if (idx == n - 1) {
            for (int i = 1; i < n; i++) {
                int tmp = tmp_res[i];
                ans[i] = order[n - 1 - tmp];
            }
        } else {
            int mx_idx = 1;
            for (int i = 1; i < n; i++) {
                if (tmp_res[i] > tmp_res[mx_idx]) {
                    mx_idx = i;
                }
            }
            int l = idx, r = n - 1 - idx;
            int loc = l > r ? 0 : n - 1;
            ans[mx_idx] = order[loc];
            for (int i = 1; i < n; i++) {
                if (ans[i] == -1) {
                    int d = ask(mx_idx, i);
                    if (loc == 0) {
                        ans[i] = order[d];
                    } else {
                        ans[i] = order[n - 1 - d];
                    }
                }
            }
        }
    };

    auto work2 = [&](int idx, vector<vector<int>> &ans) {
        debug("enter");
        ans.push_back(vector<int>(n, -1));
        ans.push_back(vector<int>(n, -1));
        ans[0][0] = order[idx];
        ans[1][0] = order[idx];
        int mx_idx = 1;
        for (int i = 1; i < n; i++) {
            if (tmp_res[i] > tmp_res[mx_idx]) {
                mx_idx = i;
            }
        }

        ans[0][mx_idx] = order[0];
        ans[1][mx_idx] = order[n - 1];

        for (int i = 0; i < n; i++) {
            if (ans[0][i] == -1) {
                int d = ask(mx_idx, i);
                ans[0][i] = order[d];
                ans[1][i] = order[n - 1 - d];
            }
        }
    };

    vector<vector<int>> ans;
    for (int i = 0; i < n; i++) {
        int l = i, r = n - i - 1;
        if (max(l, r) == mx) {
            if (n % 2 && mx == n / 2) {
                // 很不幸抽中了中间的值，需要特判一下
                work2(i, ans);
            } else {
                int idx = ans.size();
                ans.push_back(vector<int>(n, -1));
                work(i, ans[idx]);
            }
        }
    }
    out(ans[0], ans[1]);
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}