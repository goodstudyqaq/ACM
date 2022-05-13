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
    map<int, int> M;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        M[a[i]]++;
    }

    int now = M.size();
    for (int i = 1; i <= now; i++) {
        cout << now << ' ';
    }
    int val = now + 1;
    for (int j = now + 1; j <= n; j++) {
        cout << val << ' ';
        val++;
    }
    cout << endl;
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