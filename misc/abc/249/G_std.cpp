#include <bits/stdc++.h>
using namespace std;

template <class T, int W>
int sweep(vector<T>& c) {
    int n = (int)c.size(), rank = 0;
    for (int d = W - 1; d >= 0; --d) {
        int k = rank;
        while (k < n and !(c[k] >> d & 1)) {
            k += 1;
        }
        if (k < n) {
            swap(c[k], c[rank]);
            for (int i = rank + 1; i < n; ++i) {
                if (c[i] >> d & 1) {
                    c[i] ^= c[rank];
                }
            }
            rank += 1;
        }
    }
    return rank;
}

template <class T, int W>
T maximize(vector<T> c, T x) {
    int n = sweep<T, W>(c);
    for (int i = 0; i < n; ++i) {
        x = max(x, x ^ c[i]);
    }
    return x;
}

constexpr int W = 30;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> c(n);
    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        c[i] = (a << W) | b;
    }

    n = sweep<long long, 2 * W>(c);
    if ((c.back() >> W) > k) {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        a[i] = c[i] >> W;
        b[i] = c[i] & ((1 << W) - 1);
    }
    int m = 0;
    while (m < n and a[m] > 0) {
        m += 1;
    }

    int ans = 0, fixed_a = 0, fixed_b = 0;
    for (int i = 0; i < m; ++i) {
        int msb = 1;
        while ((msb << 1) <= a[i]) {
            msb <<= 1;
        }
        if ((fixed_a | (msb - 1)) <= k) {
            ans = max(ans, maximize<int, 30>(vector<int>(b.begin() + i + 1, b.end()), fixed_b));
            fixed_a ^= a[i];
            fixed_b ^= b[i];
        } else if (((fixed_a ^ a[i]) | (msb - 1)) <= k) {
            ans = max(ans, maximize<int, 30>(vector<int>(b.begin() + i + 1, b.end()), fixed_b ^ b[i]));
        } else {
            if (fixed_a & msb) {
                fixed_a ^= a[i];
                fixed_b ^= b[i];
            }
        }
    }
    if (fixed_a <= k) {
        ans = max(ans, maximize<int, 30>(vector<int>(b.begin() + m, b.end()), fixed_b));
    }
    cout << ans << '\n';
    return 0;
}