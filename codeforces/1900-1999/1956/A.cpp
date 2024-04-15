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

    int k, q;
    cin >> k >> q;
    vector<int> a(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
    }

    
    for (int i = 1; i <= q; i++) {
        int n;
        cin >> n;

        while (n >= a[1]) {
            int idx = 1;
            while (idx <= k && n >= a[idx]) idx++;
            n = n - (idx - 1);
        }
        cout << n << ' ';
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
    return 0;
}