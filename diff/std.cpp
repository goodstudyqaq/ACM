#include <bits/stdc++.h>
#include <algorithm>
#include <numeric>

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

    int n, k;
    cin >> n >> k;
    int limit = 1 << n;
    int ans = 0;
    
    auto work = [&](int val) {
        int ans = 0;
        while (val) {
            if (val % 2) ans++;
            val /= 2;
        }
        return ans;
    };
    
    auto check = [&](int x, int y) {
        int v1 = work(x);
        int v2 = work(y);
        int v3 = work(x + y);
        return v1 + v2 - v3 == k;
    };

    for (int x = 0; x < limit; x++) {
        for (int y = 0; y < limit; y++) {
            if (check(x, y)) ans++;
        }
    }
    cout << ans << endl;
}