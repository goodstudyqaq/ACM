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
    vector<string> s(2);
    cin >> s[0] >> s[1];

    int res = 0;

    int l = 0;

    while (l < n && s[0][l] == 'x' && s[1][l] == 'x') l++;
    int r = n - 1;
    while (r >= 0 && s[0][r] == 'x' && s[1][r] == 'x') r--;


    for (int i = 0; i < 2; i++) {
        for (int j = l + 1; j < r; j++) {
            if (s[i][j] == '.' && s[i ^ 1][j] == '.' && s[i][j - 1] == 'x' && s[i][j + 1] == 'x') {
                res++;
            }
        }
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
    return 0;
}