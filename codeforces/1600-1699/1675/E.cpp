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
    int n, k;
    string s;
    cin >> n >> k >> s;

    if (k >= 25) {
        string res(n, 'a');
        cout << res << endl;
        return;
    }
    int now = 0;

    char begin = 'a' + k;
    int idx = -1;
    char mx = 'a';
    for (int i = 0; i < n; i++) {
        if (s[i] > begin) {
            idx = i;
            break;
        }
        mx = max(mx, s[i]);
    }
    debug(idx);
    if (idx == -1) {
        string res(n, 'a');
        cout << res << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (s[i] <= mx) {
            s[i] = 'a';
        }
    }
    k -= (mx - 'a');
    char l = s[idx] - k;
    char r = s[idx];
    for (int i = 0; i < n; i++) {
        if (s[i] >= l && s[i] <= r) {
            s[i] = l;
        }
    }
    cout << s << endl;
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