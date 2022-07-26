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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    if (r1 <= l2 || r2 <= l1) {
        cout << 0 << endl;
    } else {
        cout << min(r1, r2) - max(l1, l2) << endl;
    }
    return 0;
}