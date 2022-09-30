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
    string s, t;
    cin >> s >> t;
    vector cnt = vector(26, vector(26, 0));

    for (int i = 0; i < n; i++) {
        int v1 = s[i] - 'a', v2 = t[n - i - 1] - 'a';
        if (v1 > v2) swap(v1, v2);
        // debug(i, v1, v2);
        cnt[v1][v2]++;
    }

    int c = 0;
    for (int i = 0; i < 26; i++) {
        // debug(i, cnt[i][i]);
        c += (cnt[i][i] % 2);
        for (int j = i + 1; j < 26; j++) {
            if (cnt[i][j] % 2) {
                // debug(i, j, cnt[i][j]);
                cout << "NO" << endl;
                return;
            }
        }
    }
    // debug(c);
    if (c > 1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
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
}