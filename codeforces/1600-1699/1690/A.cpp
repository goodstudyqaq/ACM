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

    if (n % 3 == 0) {
        int tmp = n / 3;
        cout << tmp << ' ' << tmp + 1 << ' ' << tmp - 1 << endl;
    } else if (n % 3 == 1) {
        int tmp = n / 3;
        cout << tmp << ' ' << tmp + 2 << ' ' << tmp - 1 << endl;
    } else {
        int tmp = n / 3;
        cout << tmp + 1 << ' ' << tmp + 2 << ' ' << tmp - 1 << endl;
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