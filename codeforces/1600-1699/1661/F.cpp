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

template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

long long cal(long long a, long long b) {
    return (b - a) * (b - a);
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    long long INF = inf<long long>;

    int n;
    cin >> n;
    long long sum = 0;
    vector<int> a;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += cal(a[i - 1], a[i]);
    }
    long long m;
    cin >> m;
    if (sum <= m) {
        cout << 0 << endl;
        return 0;
    }

    typedef pair<long long, long long> pp;

    // 二分变化率
    long long l = 1, r = 1e18 + 5;
    long long ans = -1;

    auto get_val = [&](long long len, int cut) -> long long {
        long long tmp = len / cut;
        long long tmp2 = len % cut;
        return 1LL * (cut - tmp2) * tmp * tmp + 1LL * tmp2 * (tmp + 1) * (tmp + 1);
    };

    auto check = [&](long long change) -> pp {
        long long ct = 0, cnt = 0;

        for (int i = 1; i <= n; i++) {
            int Len = a[i] - a[i - 1];
            if (Len == 1) {
                ct += 1;
                continue;
            }

            int l = 1, r = a[i] - a[i - 1] - 1;
            int ans = 0;
            while (l <= r) {
                int mid = l + r >> 1;
                if (get_val(Len, mid) - get_val(Len, mid + 1) >= change) {
                    ans = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            // debug(i, Len, ans, get_val(Len, ans));
            ct += get_val(Len, ans + 1);
            cnt += ans;
        }
        return {ct, cnt};
    };

    while (l <= r) {
        long long mid = l + r >> 1;
        pp it = check(mid);
        if (it.first <= m) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    debug(ans);
    pp it = check(ans);
    debug(it);
    cout << it.second - (m - it.first) / ans << endl;
    return 0;
}