#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

typedef pair<int, int> pii;
pii operator+(const pii &a, const pii &b) {
    pii res;
    res.first = a.first + b.first;
    res.second = a.second + b.second;
    return res;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector dp = vector(n / 2 + 1, vector(2, make_pair(0, 0)));

    auto change_num = [&](int idx, int flag) {
        int res = 0;
        if (s[idx] - '0' != flag) res++;
        if (s[idx + 1] - '0' != flag) res++;
        return res;
    };

    for (int i = 0; i < n; i += 2) {
        int idx = i / 2 + 1;

        if (idx == 1) {
            int tmp = change_num(i, 0);
            dp[idx][0] = make_pair(tmp, 1);
            tmp = change_num(i, 1);
            dp[idx][1] = make_pair(tmp, 1);
        } else {
            int tmp = change_num(i, 0);
            dp[idx][0] = min(dp[idx - 1][0] + make_pair(tmp, 0), dp[idx - 1][1] + make_pair(tmp, 1));
            tmp = change_num(i, 1);
            dp[idx][1] = min(dp[idx - 1][0] + make_pair(tmp, 1), dp[idx - 1][1] + make_pair(tmp, 0));
        }
    }

    auto ans = min(dp[n / 2][0], dp[n / 2][1]);
    cout << ans.first << ' ' << ans.second << endl;
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