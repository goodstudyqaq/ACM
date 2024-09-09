#include <bits/stdc++.h>
#include <stdint.h>

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
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 1; i < n; i++) {
        cin >> a[i];
    }

    int xor_sum = 0;
    for (int i = 0; i < n; i++) {
        xor_sum ^= i;
    }

    vector<int> b(n);
    if (n % 2) {
        for (int i = 2; i < n; i += 2) {
            xor_sum ^= a[i];
        }

        b[0] = xor_sum;

    } else {
        vector<int> X;
        int x = a[1];
        for (int i = 1; i < n; i++) {
            debug(x);
            X.push_back(x);
            if (i + 1 < n)
                x ^= a[i + 1];
        }

        int res = 0;
        for (int i = 0; i < 20; i++) {
            vector<int> cnt(2);
            for (int j = 0; j < n; j++) {
                cnt[(j >> i) & 1]++;
            }

            vector<int> cnt2(2);
            for (auto j : X) {
                cnt2[(j >> i) & 1]++;
            }

            if (cnt[1] == cnt2[1]) {
                // 它是 0
            } else {
                res += (1 << i);
            }
        }

        b[0] = res;
    }

    for (int i = 1; i < n; i++) {
        b[i] = b[i - 1] ^ a[i];
    }

    for (int i = 0; i < n; i++) {
        cout << b[i] << ' ';
    }
    cout << endl;
}