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

const int maxn = 1e6 + 1;
int M[maxn];


int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, t;
    cin >> n >> t;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    len = sqrt(n);

    vector<Query> q;
    for (int i = 0; i < t; i++) {
        int l, r;
        cin >> l >> r;
        q.push_back(Query{l, r, i});
    }
    sort(q.begin(), q.end());
    int L = 0, R = -1;
    long long ans = 0;
    vector<long long> res(t);
    for (int i = 0; i < t; i++) {
        Query it = q[i];
        while (L < it.l) {
            int val = a[L];
            ans = ans - 1LL * M[val] * M[val] * val;
            M[val]--;
            ans = ans + 1LL * M[val] * M[val] * val;
            L++;
        }
        while (L > it.l) {
            L--;
            int val = a[L];
            ans = ans - 1LL * M[val] * M[val] * val;
            M[val]++;
            ans = ans + 1LL * M[val] * M[val] * val;
        }
        while (R < it.r) {
            R++;
            int val = a[R];
            ans = ans - 1LL * M[val] * M[val] * val;
            M[val]++;
            ans = ans + 1LL * M[val] * M[val] * val;
        }
        while (R > it.r) {
            int val = a[R];
            ans = ans - 1LL * M[val] * M[val] * val;
            M[val]--;
            ans = ans + 1LL * M[val] * M[val] * val;
            R--;
        }
        res[it.idx] = ans;
    }

    for (int i = 0; i < t; i++) {
        cout << res[i] << endl;
    }
    return 0;
}