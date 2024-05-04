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
const int maxn = 3e6 + 1;
int M[maxn];
int M2[maxn];

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n + 1), xiora(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        xiora[i] = a[i] ^ xiora[i - 1];
    }
    len = sqrt(n);
    vector<Query> q;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        q.push_back(Query{l, r, i});
    }
    sort(q.begin(), q.end());

    int L = 1, R = 0;
    long long ans = 0;
    vector<long long> res(m);
    // M[0] = 1;

    for (int i = 0; i < m; i++) {
        Query it = q[i];
        while (L < it.l) {
            // del
            int val = xiora[L - 1];
            int val2 = xiora[L];
            ans -= M2[val ^ k];
            M2[val2]--;
            M[val]--;
            L++;
        }
        while (L > it.l) {
            // add
            L--;
            int val = xiora[L - 1];
            int val2 = xiora[L];
            M2[val2]++;
            M[val]++;
            ans += M2[val ^ k];
        }
        while (R < it.r) {
            // add
            R++;
            int val = xiora[R - 1];
            int val2 = xiora[R];
            M2[val2]++;
            M[val]++;
            ans += M[val2 ^ k];
            // debug(R, ans);
        }
        while (R > it.r) {
            // del
            int val = xiora[R - 1];
            int val2 = xiora[R];
            ans -= M[val2 ^ k];
            M2[val2]--;
            M[val]--;
            R--;
        }
        res[it.idx] = ans;
        // debug(it.l, it.r, M[1], M[0]);
    }

    for (int i = 0; i < m; i++) {
        cout << res[i] << endl;
    }
    return 0;
}