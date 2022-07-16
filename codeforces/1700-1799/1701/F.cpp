#include <bits/stdc++.h>

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

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

struct node {
    ll mat[3][3];
    bool flag;
    void clear() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mat[i][j] = 0;
            }
        }
    }

    void merge(node &b) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mat[i][j] += b.mat[i][j];
            }
        }
    }
    void reset() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mat[i][j] = 0;
            }
        }
        mat[0][0] = mat[1][1] = mat[2][2] = 1;
    }
};

node multi(node &a, node &b) {
    node res;
    res.clear();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
        }
    }
    return res;
}

void set_node(node &a, node &b) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a.mat[i][j] = b.mat[i][j];
        }
    }
}

const int maxn = 2e5 + 5;
node nodes[maxn << 2], lazy[maxn << 2];
node beg;

/*
beg = [
    [1, 0, 0],
    [0, 1, 0],
    [0, 0, 1], 
], false

*/

void push_up(int rt) {
    nodes[rt].flag = true;
    nodes[rt].clear();
    if (nodes[rt << 1].flag) {
        nodes[rt].merge(nodes[rt << 1]);
    }
    if (nodes[rt << 1 | 1].flag) {
        nodes[rt].merge(nodes[rt << 1 | 1]);
    }
}

bool check(node &a) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a.mat[i][j] != beg.mat[i][j]) return true;
        }
    }
    return false;
}

void push_down(int rt) {
    if (lazy[rt].flag == true) {
        node tmp = multi(nodes[rt << 1], lazy[rt]);
        set_node(nodes[rt << 1], tmp);
        tmp = multi(nodes[rt << 1 | 1], lazy[rt]);
        set_node(nodes[rt << 1 | 1], tmp);

        tmp = multi(lazy[rt << 1], lazy[rt]);
        set_node(lazy[rt << 1], tmp);
        lazy[rt << 1].flag = check(lazy[rt << 1]);

        tmp = multi(lazy[rt << 1 | 1], lazy[rt]);
        set_node(lazy[rt << 1 | 1], tmp);
        lazy[rt << 1 | 1].flag = check(lazy[rt << 1 | 1]);

        lazy[rt].reset();
        lazy[rt].flag = false;
    }
}

void build(int l, int r, int rt) {
    nodes[rt].reset();
    nodes[rt].flag = false;
    lazy[rt].reset();
    lazy[rt].flag = false;

    if (l == r) return;
    int m = l + r >> 1;
    build(lson);
    build(rson);
    push_up(rt);
}

void update(int L, int R, node &v, int l, int r, int rt) {
    if (L <= l && r <= R) {
        node tmp = multi(nodes[rt], v);
        set_node(nodes[rt], tmp);
        tmp = multi(lazy[rt], v);
        set_node(lazy[rt], tmp);
        lazy[rt].flag = check(lazy[rt]);
        return;
    }
    push_down(rt);
    int m = l + r >> 1;
    if (L <= m) {
        update(L, R, v, lson);
    }
    if (R > m) {
        update(L, R, v, rson);
    }
    push_up(rt);
}

void update2(int L, bool v, int l, int r, int rt) {
    if (l == r) {
        nodes[rt].flag = v;
        return;
    }
    push_down(rt);
    int m = l + r >> 1;
    if (L <= m) {
        update2(L, v, lson);
    } else {
        update2(L, v, rson);
    }
    push_up(rt);
}

node query() {
    return nodes[1];
}

void solve() {
    int q, d;
    cin >> q >> d;

    const int maxn = 2e5;
    vector<bool> vis(maxn + 1);

    node m1;
    node m2;
    m1.clear();
    m2.clear();
    beg.mat[0][0] = beg.mat[1][1] = beg.mat[2][2] = 1;
    beg.flag = false;
    m1.mat[0][0] = m1.mat[1][0] = m1.mat[1][1] = m1.mat[2][0] = m1.mat[2][2] = 1;
    m1.mat[2][1] = 2;

    m2.mat[0][0] = m2.mat[1][1] = m2.mat[2][2] = m2.mat[2][0] = 1;
    m2.mat[1][0] = -1;
    m2.mat[2][1] = -2;
    build(1, maxn, 1);
    for (int i = 1; i <= q; i++) {
        int a;
        cin >> a;
        int left = max(a - d, 1);
        if (vis[a] == 0) {
            if (a > 1) {
                update(left, a - 1, m1, 1, maxn, 1);
            }
            update2(a, true, 1, maxn, 1);
            vis[a] = 1;
        } else {
            if (a > 1) {
                update(left, a - 1, m2, 1, maxn, 1);
            }
            update2(a, false, 1, maxn, 1);
            vis[a] = 0;
        }
        node res = query();
        ll ans = (res.mat[2][0] - res.mat[1][0]) / 2;
        cout << ans << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    solve();
}