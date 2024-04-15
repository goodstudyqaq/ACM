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
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> dp(n + 1);
    vector<int> pre(n + 1);
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + a[i];
        pre[i] = -1;
        for (int j = i; j >= 1; j--) {
            int num = i - j + 1;
            if (dp[i] < dp[j - 1] + num * num) {
                dp[i] = dp[j - 1] + num * num;
                pre[i] = j - 1;
            }
        }
    }

    vector<pair<int, int>> ans;

    function<void(int, int)> work = [&](int l, int r) {
        int num = r - l + 1;
        if (num == 1) {
            if (a[l] == 0) {
                ans.push_back({l, l});
            } else if (a[l] != 1) {
                ans.push_back({l, l});
                ans.push_back({l, l});
            }
            a[l] = 1;
            return;
        }
        // 把 a[l] 变成 0
        if (a[l] != 0) {
            ans.push_back({l, l});
            a[l] = 0;
        }
        for (int i = r; i >= l + 1; i--) {
            work(l + 1, i);
        }
        ans.push_back({l, r});
        for (int i = l; i <= r; i++) a[i] = num;
    };

    int now = n;

    while (now >= 1) {
        int go = pre[now];
        debug(now, go);
        if (go == -1) {
            now--;
        } else {
            int num = now - go;
            work(go + 1, now);
            now = go;
        }
    }
    cout << dp[n] << ' ' << ans.size() << endl;
    for (auto it : ans) {
        cout << it.first << ' ' << it.second << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}