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
    vector<int> a(n + 1);
    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int x = a[i];
        while (x) {
            cnt[i]++;
            x /= 2;
        }
    }
    int limit = 30;

    auto work = [&](int b) -> long long {
        vector<int> v(n + 1);
        for (int i = 1; i <= n; i++) {
            v[i] = (a[i] >> b) & 1;
        }

        vector<int> pre(n + 1), suf(n + 2);
        vector<vector<int>> pre_flag(n + 1, vector<int>(2, 0));
        vector<vector<int>> suf_flag(n + 2, vector<int>(2, 0));

        pre_flag[0][0] = 1;
        suf_flag[n + 1][0] = 1;

        for (int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + v[i];
            pre_flag[i][0] = pre_flag[i - 1][0];
            pre_flag[i][1] = pre_flag[i - 1][1];
            pre_flag[i][pre[i] % 2]++;
        }
        for (int i = n; i >= 1; i--) {
            suf[i] = suf[i + 1] + v[i];
            suf_flag[i][0] = suf_flag[i + 1][0];
            suf_flag[i][1] = suf_flag[i + 1][1];
            suf_flag[i][suf[i] % 2]++;
        }

        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            if (cnt[i] == b + 1) {
                int f1 = pre[i - 1] % 2;
                int f2 = suf[i + 1] % 2;
                if (f1 == f2) {
                    ans += 1LL * pre_flag[i - 1][0] * suf_flag[i + 1][1] + 1LL * pre_flag[i - 1][1] * suf_flag[i + 1][0];
                } else {
                    ans += 1LL * pre_flag[i - 1][0] * suf_flag[i + 1][0] + 1LL * pre_flag[i - 1][1] * suf_flag[i + 1][1];
                }
            }
        }
        return ans;
    };

    long long ans = 0;
    for (int i = 0; i < 30; i++) {
        ans += work(i);
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