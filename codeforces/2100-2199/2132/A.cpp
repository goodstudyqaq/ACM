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
    string a;
    cin >> n >> a;
    int m;
    cin >> m;
    string b;
    cin >> b;
    string c;
    cin >> c;

    int c_sz = c.size();
    for (int i = c_sz - 1; i >= 0; i--) {
        if (c[i] == 'V') {
            cout << b[i];
        }
    }
    cout << a;
    for (int i = 0; i < c_sz; i++) {
        if (c[i] == 'D') {
            cout << b[i];
        }
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