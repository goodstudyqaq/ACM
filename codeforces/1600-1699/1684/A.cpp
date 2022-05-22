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
    cin >> n;

    int x = n;
    vector<int> v;
    while (x) {
        v.push_back(x % 10);
        x /= 10;
    }

    if (v.size() == 2) {
        cout << v[0] << endl;
        return;
    }

    int mi = 10;
    for (int i = 0; i < v.size(); i++) {
        mi = min(mi, v[i]);
    }
    cout << mi << endl;
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