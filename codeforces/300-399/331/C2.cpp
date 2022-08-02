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
typedef pair<long long, long long> pli;
map<pli, pli> m;

pli dfs(long long a, long long b) {
    debug(a, b);
    if (a < 10) {
        if (a >= b) {
            if (a == 0) return {0, 0};
            return {1, 0};
        } else {
            return {0, a};
        }
    }
    if (m.count({a, b})) return m[{a, b}];
    long long res = 0;
    long long left = 0;
    long long ten = 1;
    while (ten <= a / 10) {
        ten *= 10;
    }
    long long tmp1 = a % ten, tmp2 = a / ten;

    pli it = dfs(tmp1, max(b, tmp2));
    res += it.first;
    tmp1 = it.second;
    while (tmp2) {
        long long tmp3 = max(b, tmp2);
        tmp2--;
        // debug(tmp1, ten, tmp3);
        long long nxt_tmp1 = tmp1 + ten - tmp3;
        tmp1 = nxt_tmp1;
        res++;
        it = dfs(tmp1, max(b, tmp2));
        res += it.first;
        tmp1 = it.second;
    }
    return m[{a, b}] = {res, tmp1};
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    long long n;
    cin >> n;

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    pli ans = dfs(n, 0);
    cout << ans.first << endl;
    debug(ans.second);
    debug(m);
    return 0;
}