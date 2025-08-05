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
    int n, m;
    cin >> n >> m;
    vector<pii> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i].second;
        a[i].first = a[i].second / 100;
    }
    sort(a.begin(), a.end());
    debug(a);

    int ans = 0;
    int need = n;
    for (int i = 0; i < m && need; i++) {
        int l = a[i].second, r = a[m - 1 - i].second;
        for (int j = 0; j < 6; j++) {
            if (j % 2 == 0) {
                cout << l << ' ';
            } else {
                cout << r << ' ';
            }
        }
        ans += abs(a[i].first - a[m - 1 - i].first) * 5;
        need--;
        
        cout << '\n';
        if (need) {
            swap(l, r);
            for (int j = 0; j < 6; j++) {
                if (j % 2 == 0) {
                    cout << l << ' ';
                } else {
                    cout << r << ' ';
                }
            }
            ans += abs(a[i].first - a[m - 1 - i].first) * 5;
            cout << '\n';
            need--;
        }
    }
    debug(ans);
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