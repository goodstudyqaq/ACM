#include <bits/stdc++.h>

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

    int n, k;
    cin >> n >> k;
    long long now = 1;
    long long mx = 1;
    for (int i = 1; i <= k; i++) {
        mx *= 10;
    }
    mx--;

    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;

        // now * a <= now

        if (mx / a >= now) {
            now *= a;
        } else {
            now = 1;
        }
    }
    cout << now << '\n';
}