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
    vector<int> a(n);
    vector<int> mi(2, 1e9 + 1);
    vector<int> idx(2);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] < mi[i % 2]) {
            mi[i % 2] = a[i];
            idx[i % 2] = i;
        }
    }

    if (n % 2) {
        cout << "Mike" << endl;
        return;
    }
    if (mi[0] != mi[1]) {
        if (mi[0] < mi[1]) {
            cout << "Joe" << endl;
        } else {
            cout << "Mike" << endl;
        }
    } else {
        if (idx[0] < idx[1]) {
            cout << "Joe" << endl;
        } else {
            cout << "Mike" << endl;
        }
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