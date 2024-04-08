#include <bits/stdc++.h>

#include <memory>

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

void solve() {
    long long n, k;
    cin >> n >> k;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    auto cal = [&](vector<int> &v) -> long long {
        BIT<int> bit(n);
        long long have = 0;
        for (int i = 1; i <= n; i++) {
            int val = v[i];
            have += i - bit.query(val) - 1;
            bit.add(val, 1);
        }
        return have;
    };

    long long have = cal(p);
    if (have > k || (k - have) % 2) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;

    vector<int> w;
    w = p;

    BIT<int> bit2(n);
    long long need = (k - have) / 2;
    have = 0;

    int idx = -1;
    long long have2 = 0;
    for (int i = 1; i <= n; i++) {
        int val = p[i];
        int tmp = bit2.query(val);
        int tmp2 = i - 1 - tmp;

        have += tmp - tmp2;

        if (have >= need) {
            idx = i;
            break;
        } else {
            have2 = have;
        }
        bit2.add(val, 1);
    }

    debug(idx, have, need);

    if (have == need) {
        for (int i = 1; i <= idx / 2; i++) {
            swap(w[i], w[idx + 1 - i]);
        }
    } else {
        int idx2 = idx - 1;
        for (int i = 1; i <= idx2 / 2; i++) {
            swap(w[i], w[idx2 + 1 - i]);
        }
    }

    vector<int> q(n + 1);
    for (int i = 1; i <= n; i++) {
        // q[p[i]] = w[i]
        q[p[i]] = w[i];
    }
    debug(q);
    debug(idx);

    if (have > need) {
        need = need - have2;
        int idx2 = p[idx];
        debug(idx2, need);

        for (int i = idx2 - 1; i >= 1; i--) {
            if (q[i] < q[idx2]) {
                need--;
            } else {
                need++;
            }
            if (need == 0) {
                int tmp = q[idx2];
                for (int j = idx2 - 1; j >= i; j--) {
                    q[j + 1] = q[j];
                }
                q[i] = tmp;
                break;
            }
        }
    }
    debug(q);
    for (int i = 1; i <= n; i++) {
        w[i] = q[p[i]];
    }

    debug(cal(q), cal(w));
    for (int i = 1; i <= n; i++) {
        cout << q[i] << ' ';
    }

    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}