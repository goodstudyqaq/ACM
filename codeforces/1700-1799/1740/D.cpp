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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
    }

    set<int> S;

    int now_idx = 1;

    ll mx_sz = 1LL * n * m - 3;

    if (k <= mx_sz) {
        cout << "YA" << endl;
        return;
    }
    for (int i = k; i >= 1; i--) {
        while (S.size() < mx_sz && now_idx <= k && S.count(i) == 0) {
            S.insert(a[now_idx]);
            now_idx++;
        }
        if (S.count(i) == 0) {
            cout << "TIDAK" << endl;
            return;
        }
        S.erase(i);
    }
    cout << "YA" << endl;
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