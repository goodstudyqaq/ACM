#include <bits/stdc++.h>

#include <bitset>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    vector<int> a(n * 2 + 1);
    vector<long long> suma(n * 2 + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n * 2; i++) {
        suma[i] = suma[i - 1] + a[i];
    }

    bitset<200001> now;
    now.set(1);

    long long ans = 0;
    for (int i = 1; i <= 2 * n; i++) {
        if (now[i]) {
            ans = max(ans, suma[i] - i + 1);
        }
        now |= (now << a[i]);
        now[i] = 0;
    }
    cout << ans << endl;
}