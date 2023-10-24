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
    string ans(n + 1, '0');
    if (n % 2 == 0) {
        int no = 0;
        for (int i = 0; i < n / 2; i++) {
            no += (s[i] != s[n - i - 1]);
        }
        int same = n - no * 2;
        for (int i = no; i <= n && i - no <= same; i += 2) ans[i] = '1';
        cout << ans << endl;
    } else {
        int no = 0;
        for (int i = 0; i < n / 2; i++) {
            no += (s[i] != s[n - i - 1]);
        }
        int same = n - no * 2;
        for (int i = no; i <= n && i - no <= same; i++) ans[i] = '1';
        cout << ans << endl;
    }
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