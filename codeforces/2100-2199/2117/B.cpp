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
    list<int> l;
    int n;
    cin >> n;
    bool f = 0;
    for (int i = n; i >= 1; i--) {
        if (f == 0) {
            l.push_back(i);
        }  else {
            l.push_front(i);
        }
        f ^= 1;
    }
    for (auto it : l) {
        cout << it << ' ';
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