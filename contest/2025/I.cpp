#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

    int n, q;
    cin >> n >> q;
    vector<long long> r(n);
    vector<long long> sum(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }
    sort(r.begin(), r.end());
    for (int i = 0; i < n; i++) {
        sum[i] = r[i];
        if (i) sum[i] += sum[i - 1];
    }
    for (int i = 0; i < q; i++) {
        long long x;
        cin >> x;
        int idx = upper_bound(sum.begin(), sum.end(), x) - sum.begin();
        cout << idx << '\n';
    }
}