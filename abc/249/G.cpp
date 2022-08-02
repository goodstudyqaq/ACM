#include <bits/stdc++.h>

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

vector<long long> convert(vector<long long> v, int bit) {
    int rk = 0;
    int n = v.size();
    vector<long long> res(n);
    for (int i = bit - 1; i >= 0; i--) {
        int go = rk;
        while (go < n && ((v[go] >> i) & 1) == 0) {
            go++;
        }
        if (go == n) continue;
        res[rk] = v[go];
        swap(v[rk], v[go]);
        for (int j = rk + 1; j < n; j++) {
            if ((v[j] >> i) & 1) {
                v[j] = v[j] ^ v[rk];
            }
        }
        rk++;
    }
    res.resize(rk);
    return res;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int N, K;
    cin >> N >> K;
    vector<long long> C(N);
    int bit = 30;
    for (int i = 0; i < N; i++) {
        long long a, b;
        cin >> a >> b;
        C[i] = (a << bit) + b;
    }

    auto matrix = convert(C, bit * 2);

    if (matrix.size() && (matrix.back() >> bit) > K) {
        cout << -1 << endl;
        return 0;
    }

    int m = -1;
    int sz = matrix.size();
    debug(sz);
    vector<long long> a(sz), b(sz);
    for (int i = 0; i < sz; i++) {
        a[i] = (matrix[i] >> bit);
        b[i] = (matrix[i] & ((1LL << bit) - 1));
        if (a[i]) m = i;
    }

    auto cal = [&](int idx, long long x) -> long long {
        vector<long long> tmp;
        for (int i = idx; i < matrix.size(); i++) {
            tmp.push_back(b[i]);
        }
        auto tmp1 = convert(tmp, bit);

        for (int i = 0; i < tmp1.size(); i++) {
            x = max(x, x ^ tmp1[i]);
        }
        return x;
    };

    long long ans = 0;
    long long fixed_a = 0, fixed_b = 0;
    for (int i = 0; i <= m; i++) {
        long long one = 1;
        while (1LL << (one + 1) <= a[i]) {
            one++;
        }
        if (((fixed_a ^ a[i]) | ((1LL << one) - 1)) <= K) {
            ans = max(ans, cal(i + 1, fixed_b ^ b[i]));
        } else if ((fixed_a | ((1LL << one) - 1)) <= K) {
            ans = max(ans, cal(i + 1, fixed_b));
            fixed_a ^= a[i];
            fixed_b ^= b[i];
        } else {
            if ((fixed_a >> one) & 1) {
                fixed_a ^= a[i];
                fixed_b ^= b[i];
            }
        }
    }
    debug(ans);
    if (fixed_a <= K) {
        ans = max(ans, cal(m + 1, fixed_b));
    }
    cout << ans << endl;
    return 0;
}