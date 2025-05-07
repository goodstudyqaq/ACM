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
    int n, k;
    string s;
    cin >> n >> k >> s;
    bool same = true;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[0]) {
            same = false;
            break;
        }
    }
    if (same) {
        cout << "NO\n";
        return;
    }
    if (k == 0) {
        for (int i = 0; i < n; i++) {
            if (s[i] < s[n - i - 1]) {
                cout << "YES\n";
                return;
            } else if (s[i] > s[n - i - 1]) {
                cout << "NO\n";
                return;
            }
        }
        cout << "NO\n";
        return;
    } else {
        cout << "YES\n";
        return;
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