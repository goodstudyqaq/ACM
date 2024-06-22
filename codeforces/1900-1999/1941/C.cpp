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
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'p') {
            if (i + 2 < n && s[i + 1] == 'i' && s[i + 2] == 'e') {
                res++;
            } else if (i - 2 >= 0 && s[i - 1] == 'a' && s[i - 2] == 'm') {
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