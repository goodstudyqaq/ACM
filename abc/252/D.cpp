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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<ll> a(n);
    map<ll, ll> M;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        M[a[i]]++;
    }
    map<ll, ll> M2;
    ll ans = 0;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int v = a[i];
        sum -= M2[v] * M[v];
        M[v]--;
        ll tmp1 = 1LL * (n - i - 1) * (i - M2[v]);
        ll tmp2 = sum;
        ll tmp3 = 1LL * (i - M2[v]) * M[v];
        ll tmp = tmp1 - tmp2 - tmp3;
        ans += tmp;
        M2[v]++;
        sum += M2[v] * M[v];
        debug(i, ans);
    }
    cout << ans << endl;
    return 0;
}