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

int len;
struct Query {
    int l, r, idx;
    int block;
    Query(int _l, int _r, int _idx)
        : l(_l), r(_r), idx(_idx) {
        block = l / len;
    }
    Query() {}
    bool operator<(const Query& b) const {
        if (block != b.block) return block < b.block;
        return r < b.r;
    }
};
const int maxm = 1048576;
int M[maxm + 1];
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m, k;
    cin >> n >> m >> k;
    len = sqrt(n);
    vector<int> a(n + 1), sum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] ^ a[i];
    }

    vector<Query> q(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        q[i] = Query(l, r, i);
    }
    sort(q.begin(), q.end());

    long long ans = 0;
    vector<long long> res(m);

    int L = 0, R = -1;
    // 左闭右闭

    auto del = [&](int val) {
        int val2 = val ^ k;
        M[val]--;
        ans -= M[val2];

        debug(ans, L, R);
    };

    auto add = [&](int val) {
        int val2 = val ^ k;
        ans += M[val2];
        M[val]++;
        debug(ans, L, R);
    };

    for (int i = 0; i < m; i++) {
        Query it = q[i];
        while (R < it.r) {
            // 加
            R++;
            add(sum[R]);
        }
        while (L > it.l) {
            // 加
            L--;
            add(sum[L]);
        }
        while (L < it.l) {
            // 删
            del(sum[L]);
            L++;
        }
        while (R > it.r) {
            // 删
            del(sum[R]);
            R--;
        }

        res[it.idx] = ans;
    }

    for (int i = 0; i < m; i++) {
        cout << res[i] << '\n';
    }
}