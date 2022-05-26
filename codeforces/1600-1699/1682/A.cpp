#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    char it = s[n / 2];

    int l = n / 2;
    while (l >= 0 && s[l] == it) {
        l--;
    }
    int r = n / 2;
    while (r < n && s[r] == it) {
        r++;
    }
    cout << r - l - 1 << endl;
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