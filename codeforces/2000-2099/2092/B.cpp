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
    string s, b;
    cin >> n >> s >> b;

    for (int i = 0; i < 2; i++) {
        int cnt = 0;
        for (int j = i; j < n; j += 2) {
            if (s[j] == '1') cnt++;
        }
        for (int j = i ^ 1; j < n; j += 2) {
            if (b[j] == '0') cnt--;
        }
        if (cnt > 0) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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