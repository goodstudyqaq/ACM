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

vector<long long> zebra;
void init() {
    long long val = 1;
    long long limit = 1e18;
    while (val <= limit) {
        zebra.push_back(val);
        val *= 4;
        val++;
    }
    debug(zebra.size());
}

void solve() {
    long long l, r, k;
    cin >> l >> r >> k;
    
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}