#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    string s;
    cin >> s;
    if (n == 1) {
        cout << 1 << endl;
        return;
    }

    vector<vector<int>> sum(n, vector<int>(26, 0));

    for (int i = 0; i < n; i++) {
        if (i >= 2) {
            for (int j = 0; j < 26; j++) {
                sum[i][j] = sum[i - 2][j];
            }
        }
        sum[i][s[i] - 'a']++;
    }

    if (n % 2 == 0) {
        int half = n / 2;
        int mx = 0, mx2 = 0;
        for (int i = 0; i < 26; i++) {
            mx = max(mx, sum[n - 1][i]);
            mx2 = max(mx2, sum[n - 2][i]);
        }

        cout << n - mx - mx2 << endl;
        return;
    }

    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        // 枚举删掉第 i 个字符
        vector<vector<int>> sum2(2, vector<int>(26));
        if (i - 1 >= 0) {
            sum2[(i - 1) % 2] = sum[i - 1];
        }
        if (i - 2 >= 0) {
            sum2[(i - 2) % 2] = sum[i - 2];
        }
        vector<vector<int>> sum3(2, vector<int>(26));

        sum3[(n - 1) % 2] = sum[n - 1];
        sum3[(n - 2) % 2] = sum[n - 2];

        if (i % 2 == 0) {
            for (int j = 0; j < 26; j++) {
                sum3[0][j] -= sum[i][j];
            }
            if (i - 1 >= 0) {
                for (int j = 0; j < 26; j++) {
                    sum3[1][j] -= sum[i - 1][j];
                }
            }
        } else {
            for (int j = 0; j < 26; j++) {
                sum3[0][j] -= sum[i - 1][j];
                sum3[1][j] -= sum[i][j];
            }
        }

        int mx = 0, mx2 = 0;
        for (int i = 0; i < 26; i++) {
            sum2[0][i] += sum3[1][i];
            sum2[1][i] += sum3[0][i];
            mx = max(mx, sum2[0][i]);
            mx2 = max(mx2, sum2[1][i]);
        }
        // debug(i, mx, mx2, sum2[1]);
        ans = min(ans, n - mx - mx2);
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