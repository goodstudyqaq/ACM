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
typedef array<int, 2> a2;

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
    string s;
    cin >> s;
    vector<int> ans(n);

    for (int i = 0; i < n;) {
        if (s[i] == '1') {
            ans[i] = i;
            i++;
            continue;
        }
        int go = i;
        while (go < n && s[go] == '0') go++;

        int len = go - i;

        if (len == 1) {
            cout << "NO\n";
            return;
        }

        for (int j = go - 1; j >= i; j--) {
            ans[j] = i + go - 1 - j;
        }

        i = go;
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << ' ';
    }
    cout << '\n';
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