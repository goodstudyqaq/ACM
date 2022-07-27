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
const int maxn = 1005;
int mx[maxn << 2];
int lazy[maxn << 2];
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
vector<int> a;

void push_up(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}

void push_down(int rt) {
    if (lazy[rt] != 0) {
        mx[rt << 1] += lazy[rt];
        lazy[rt << 1] += lazy[rt];
        mx[rt << 1 | 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        lazy[rt] = 0;
    }
}

void build(int l, int r, int rt) {
    lazy[rt] = 0;
    if (l == r) {
        mx[rt] = a[l];
        return;
    }
    int m = l + r >> 1;
    build(lson);
    build(rson);
    push_up(rt);
}

void update(int L, int R, int val, int l, int r, int rt) {
    if (L <= l && r <= R) {
        mx[rt] += val;
        lazy[rt] += val;
        return;
    }
    push_down(rt);
    int m = l + r >> 1;
    if (L <= m) {
        update(L, R, val, lson);
    }
    if (R > m) {
        update(L, R, val, rson);
    }
    push_up(rt);
}

int query() {
    return mx[1];
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<vector<int>> V(m, vector<int>(2, -1));
    a.resize(m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'B') {
                if (V[j][0] == -1) {
                    V[j][0] = i;
                    V[j][1] = i;
                } else {
                    V[j][1] = i;
                }
            }
        }
    }

    int ans = 1e9;
    int x, y;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (V[j][0] == -1) {
                a[j] = -1e9;
            } else {
                a[j] = max(abs(V[j][0] - i), abs(V[j][1] - i));
            }
            a[j] += j;
        }
        build(0, m - 1, 1);

        for (int j = 0; j < m; j++) {
            int tmp = query();
            if (ans > tmp) {
                ans = tmp;
                x = i;
                y = j;
            }
            if (j != m - 1) {
                update(j + 1, m - 1, -1, 0, m - 1, 1);
                update(0, j, 1, 0, m - 1, 1);
            }
        }
    }
    debug(ans);
    cout << x + 1 << ' ' << y + 1 << endl;
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
}