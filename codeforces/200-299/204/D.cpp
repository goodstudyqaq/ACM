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
const int mod = 1e9 + 7;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, k;
    string s;
    cin >> n >> k;
    cin >> s;
    s = " " + s;
    map<int, char> M;
    M[0] = 'B';
    M[1] = 'W';

    auto work = [&](int flag, vector<int> &dp1, vector<int> &dp2) {
        vector<vector<int>> sum;
        sum.resize(2, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            if (s[i] == 'B') {
                sum[0][i]++;
            } else if (s[i] == 'W') {
                sum[1][i]++;
            }
            sum[0][i] += sum[0][i - 1];
            sum[1][i] += sum[1][i - 1];
        }
        // debug(sum);
        /*
            dp1[i]: 到 i 位置为止，没有长度为 k 的 flag 的方案数
            dp2[i]: [i - k + 1, i] 都为 flag 且以前没有的方案数
        */
        dp1.resize(n + 1);
        dp2.resize(n + 1);
        dp1[0] = 1;
        for (int i = 1; i <= n; i++) {
            if (i >= k && sum[flag ^ 1][i] - sum[flag ^ 1][i - k] == 0) {
                if (s[i - k] != M[flag]) {
                    // debug(i, sum[flag ^ 1][i], sum[flag ^ 1][i - k]);
                    dp2[i] = dp1[max(i - k - 1, 0)];
                }
            }
            int tmp = dp1[i - 1];
            if (s[i] == 'X') {
                tmp = 1LL * tmp * 2 % mod;
            }
            tmp = (tmp - dp2[i]) % mod;
            dp1[i] = tmp;
        }
    };

    vector<int> leftdp1, leftdp2, rightdp1, rightdp2;
    work(0, leftdp1, leftdp2);
    reverse(s.begin() + 1, s.begin() + 1 + n);
    work(1, rightdp1, rightdp2);
    reverse(s.begin() + 1, s.begin() + 1 + n);
    int res = 0;
    int two = 1;
    for (int i = 1; i <= n - k; i++) {
        if (s[i] == 'X') {
            two = 1LL * two * 2 % mod;
        }
        int i2 = n - i;
        // debug(i, two - leftdp1[i], i2, rightdp2[i2]);
        (res += 1LL * (two - leftdp1[i]) * rightdp2[i2] % mod) %= mod;
    }
    res = (res + mod) % mod;
    cout << res << endl;
    return 0;
}