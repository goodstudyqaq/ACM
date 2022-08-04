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
    string t;
    cin >> t;
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    int m = t.size();

    const int inf = numeric_limits<int>::max() / 2;
    vector<int> dp(m + 1, inf);

    auto check = [&](int l, int r, int idx) {
        if (s[idx].size() != r - l + 1) return false;
        int sz = s[idx].size();
        for (int i = 0; i < sz; i++) {
            if (s[idx][i] != t[l + i]) return false;
        }
        return true;
    };

    dp[0] = 0;
    vector<int> last(m + 1), chose(m + 1);
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < i; j++) {
            // [j + 1, i]
            for (int k = 0; k < n; k++) {
                if (check(j, i - 1, k)) {
                    for (int t = j + 1; t <= i; t++) {
                        if (dp[t] > dp[j] + 1) {
                            dp[t] = dp[j] + 1;
                            last[t] = j;
                            chose[t] = k;
                        }
                    }
                }
            }
        }
    }
    int ans = dp[m];
    if (ans == inf) ans = -1;
    cout << ans << endl;
    if (ans != -1) {
        int now = m;
        while (now) {
            int the_last = last[now];
            int the_chose = chose[now];
            cout << the_chose + 1 << ' ' << the_last + 1 << endl;
            now = the_last;
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
}