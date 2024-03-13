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

template <typename T>
struct BIT {
#define lowbit(x) x & -x
    int n;
    vector<T> a;
    // [1, n]
    BIT(int n) : n(n), a(n + 1) {}
    BIT() {}

    void init(int _n) {
        n = _n;
        a = vector<T>(n + 1);
    }
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    // [1, x]
    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }

    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }

    int search(T val) {  // 找到最后一个 res，使得 [1, res] 的前缀和 <= val
        int level = largest_bit(n);
        int res = 0;
        for (int i = level; i >= 0; i--) {
            if (res + (1 << i) <= n && val >= a[res + (1 << i)]) {  // 注意 val >= a[res + (1 << i)], 如果求的是 < val，那么相应也要去掉 = 号
                res += (1 << i);
                val -= a[res];
            }
        }
        return res;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, k;
    cin >> n >> k;
    int K = k / 2;
    map<int, vector<int>> M;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        M[a[i]].push_back(i);
    }

    BIT<int> bits(n + 1);

    typedef pair<int, int> pii;
    auto get_interval = [&](int idx) -> pii {
        if (idx >= n - K) {
            return {-1, -1};
        }
        int L = max(1, idx - K + 1);
        int R = min(idx, n - k + 1);

        int sum1 = L + L + k - 1;
        int sum2 = R + R + k - 1;

        return {sum1 - idx, sum2 - idx};
    };

    long long ans = 0;
    for (auto it : M) {
        int sz = it.second.size();

        vector<int> v[2];

        for (int i = 0; i < sz; i++) {
            int idx = it.second[i];
            v[idx % 2].push_back(idx);
        }

        for (int f = 0; f < 2; f++) {
            int sz = v[f].size();
            for (int i = 0; i < sz; i++) {
                int idx = v[f][i];
                bits.add(idx, 1);
            }

            for (int i = 0; i < sz; i++) {
                int idx = v[f][i];
                auto [l, r] = get_interval(idx);
                debug(idx, l, r);
                if (l == -1) {
                    break;
                }

                int tmp = bits.query(r) - bits.query(l - 1);
                ans += (r - l + 2) / 2 - tmp;
            }

            for (int i = 0; i < sz; i++) {
                int idx = v[f][i];
                bits.add(idx, -1);
            }
        }
    }
    cout << ans << endl;
    return 0;
}