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
    int n, k;
    string s;
    cin >> n >> k;
    cin >> s;

    int w_num = 0;
    for (int i = 0; i < k - 1; i++) {
        if (s[i] == 'W') w_num++;
    }

    int res = 1e9;
    for (int i = k - 1; i < n; i++) {
        if (s[i] == 'W') w_num++;
        res = min(res, w_num);
        int beg = i - k + 1;
        if (s[beg] == 'W') w_num--;
    }
    cout << res << endl;
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