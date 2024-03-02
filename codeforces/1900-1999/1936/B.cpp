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
    string s;
    cin >> n >> s;
    vector<vector<long long>> sum(n + 1, vector<long long>(2, 0));
    vector<vector<int>> num(n + 1, vector<int>(2, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            num[i + 1][j] = num[i][j];
            sum[i + 1][j] = sum[i][j];
        }
        if (s[i] == '<') {
            sum[i + 1][0] += (i + 1);
            num[i + 1][0]++;
        } else {
            sum[i + 1][1] += (i + 1);
            num[i + 1][1]++;
        }
    }
    auto get_left_idx = [&](int idx, int flag, int number) {
        int l = 1, r = idx;
        int ans = -1;
        while (l <= r) {
            int m = l + r >> 1;
            if (num[idx][flag] - num[m - 1][flag] >= number) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return ans;
    };

    auto get_right_idx = [&](int idx, int flag, int number) {
        int l = idx, r = n;
        int ans = -1;
        while (l <= r) {
            int m = l + r >> 1;
            if (num[m][flag] - num[idx - 1][flag] >= number) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return ans;
    };

    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '>') {
            // 右边 < 的个数
            long long right_num = num[n][0] - num[i][0];
            // 左边 > 的个数
            long long left_num = num[i][1];
            int mi_num = min(left_num, right_num);

            int left_need = mi_num, right_need = mi_num;
            if (left_num > right_num) {
                left_need++;
            }

            int left_idx = get_left_idx(i, 1, left_need);
            int right_idx = get_right_idx(i, 0, right_need);

            long long left_val = (1LL * left_need * i - (sum[i][1] - sum[left_idx - 1][1])) * 2;
            long long right_val = (sum[right_idx][0] - sum[i - 1][0] - 1LL * right_need * i) * 2;
            long long ans = left_val + right_val;
            if (right_num >= left_num) {
                ans += i;
            } else {
                ans += n + 1 - i;
            }
            cout << ans << ' ';
        } else {
            long long right_num = num[n][0] - num[i - 1][0];
            long long left_num = num[i - 1][1];
            int mi_num = min(left_num, right_num);

            int left_need = mi_num, right_need = mi_num;
            if (right_num > left_num) {
                right_need++;
            }

            int left_idx = get_left_idx(i, 1, left_need);
            int right_idx = get_right_idx(i, 0, right_need);
            long long left_val = (1LL * left_need * i - (sum[i][1] - sum[left_idx - 1][1])) * 2;
            long long right_val = (sum[right_idx][0] - sum[i - 1][0] - 1LL * right_need * i) * 2;
            long long ans = left_val + right_val;
            // debug(i, left_idx, right_idx, left_val, right_val);
            if (right_num > left_num) {
                ans += i;
            } else {
                ans += n + 1 - i;
            }
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