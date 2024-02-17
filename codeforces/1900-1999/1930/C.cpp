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
    vector<int> a(n + 1);
    vector<int> V;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int val = a[i] + i;
        V.push_back(val);
    }
    sort(V.begin(), V.end());

    int use = V[n - 1];
    cout << use << ' ';
    for (int i = n - 2; i >= 0; i--) {
        if (V[i] >= use) {
            use--;
            cout << use << ' ';
        } else {
            cout << V[i] << ' ';
            use = V[i];
        }
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