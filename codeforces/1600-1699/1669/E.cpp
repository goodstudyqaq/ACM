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

void solve() {
    int k = ('k' - 'a') + 1;
    debug(k);
    vector sum = vector(k, vector(k, 0));
    vector sum2 = vector(k, vector(k, 0));
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        sum[s[0] - 'a'][s[1] - 'a']++;
        sum2[s[1] - 'a'][s[0] - 'a']++;
    }
    // debug(sum);
    // debug(sum2);

    long long ans = 0;
    for (int i = 0; i < k; i++) {
        int tmp = 0, tmp1 = 0;
        for (int j = 0; j < k; j++) {
            tmp += sum[i][j];
            tmp1 += sum2[i][j];
        }
        for (int j = 0; j < k; j++) {
            ans += 1LL * sum[i][j] * (tmp - sum[i][j]);
            ans += 1LL * sum2[i][j] * (tmp1 - sum2[i][j]);
        }
    }
    ans /= 2;
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
}