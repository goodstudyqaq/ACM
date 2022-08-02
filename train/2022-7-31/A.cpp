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

const int maxn = 1e5 + 5;
int f[maxn];
int find(int u) {
    return u == f[u] ? u : f[u] = find(f[u]);
}

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template <class Info, class Tag, class Merge = std::plus<Info>>
struct LazySegmentTree {
    LazySegmentTree(int n) : n(n), merge(Merge()), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(vector<Info> &init) : LazySegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int l, int r, int rt) {
            if (l == r) {
                info[rt] = init[l];
                return;
            }
            int m = l + r >> 1;
            build(lson);
            build(rson);
            push_up(rt);
        };
        build(0, n - 1, 1);
    }

    void update(int L, const Info &v) {
        update(L, v, 0, n - 1, 1);
    }

    void rangeUpdate(int L, int R, const Tag &v) {
        return rangeUpdate(L, R, v, 0, n - 1, 1);
    }

    Info rangeQuery(int L, int R) {
        return rangeQuery(L, R, 0, n - 1, 1);
    }

    int find_first(int ll, int rr, const function<bool(const Info &)> &f) {
        return find_first(ll, rr, f, 0, n - 1, 1);
    }

    int find_last(int ll, int rr, const function<bool(const Info &)> &f) {
        return find_last(ll, rr, f, 0, n - 1, 1);
    }

   private:
    const int n;
    const Merge merge;
    vector<Info> info;
    vector<Tag> tag;
    void push_up(int rt) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1]);
    }

    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push_down(int rt) {
        apply(rt << 1, tag[rt]);
        apply(rt << 1 | 1, tag[rt]);
        tag[rt] = Tag();
    }

    void update(int L, const Info &v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        push_down(rt);
        if (L <= m) {
            update(L, v, lson);
        } else {
            update(L, v, rson);
        }
        push_up(rt);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        push_down(rt);
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson));
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void rangeUpdate(int L, int R, const Tag &v, int l, int r, int rt) {
        if (L <= l && r <= R) {
            apply(rt, v);
            return;
        }
        int m = l + r >> 1;
        push_down(rt);
        if (L <= m) {
            rangeUpdate(L, R, v, lson);
        }
        if (R > m) {
            rangeUpdate(L, R, v, rson);
        }
        push_up(rt);
    }

    int find_first_knowingly(const function<bool(const Info &)> f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        push_down(rt);
        int res;
        if (f(info[rt << 1])) {
            res = find_first_knowingly(f, lson);
        } else {
            res = find_first_knowingly(f, rson);
        }
        push_up(rt);
        return res;
    }

    int find_first(int L, int R, const function<bool(const Info &)> f, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (!f(info[rt])) {
                return -1;
            }
            return find_first_knowingly(f, l, r, rt);
        }
        int m = l + r >> 1;
        push_down(rt);
        int res = -1;
        if (L <= m) {
            res = find_first(L, R, f, lson);
        }
        if (R > m && res == -1) {
            res = find_first(L, R, f, rson);
        }
        push_up(rt);
        return res;
    }

    int find_last_knowingly(const function<bool(const Info &)> f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        push_down(rt);
        int res;
        if (f(info[rt << 1 | 1])) {
            res = find_last_knowingly(f, rson);
        } else {
            res = find_last_knowingly(f, lson);
        }
        push_up(rt);
        return res;
    }

    int find_last(int L, int R, const function<bool(const Info &)> f, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (!f(info[rt])) {
                return -1;
            }
            return find_last_knowingly(f, l, r, rt);
        }
        int m = l + r >> 1;
        push_down(rt);
        int res = -1;
        if (R > m) {
            res = find_last(L, R, f, rson);
        }
        if (L <= m && res == -1) {
            res = find_last(L, R, f, lson);
        }
        push_up(rt);
        return res;
    }
};

struct Tag {
    int x;
    Tag(int _x) : x(_x) {}
    Tag() { x = 0; }
    void apply(const Tag &v) {
        if (v.x) {
            x += v.x;
        }
    }
};

struct Info {
    int x;
    Info(int _x) {
        x = _x;
    }

    Info() { x = 0; }

    void apply(const Tag &v) {
        if (v.x) {
            x += v.x;
        }
    }

    friend Info operator+(const Info &a, const Info &b) {
        return Info();
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<int>> V(n + 1);
    vector<pii> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
    }

    for (int i = 1; i <= n; i++) {
        f[i] = i;
    }
    vector<int> vis(m);
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            vis[i] = 1;
            f[fu] = fv;
            V[u].push_back(v);
            V[v].push_back(u);
        }
    }

    vector<int> dep(n + 1);
    vector<vector<int>> dp(n + 1, vector<int>(20));
    vector<int> L(n + 1), R(n + 1);
    int time = 0;
    function<void(int, int, int)> dfs = [&](int u, int pre, int d) {
        L[u] = time++;
        dep[u] = d;
        dp[u][0] = pre;
        for (auto v : V[u]) {
            if (v == pre) continue;
            dfs(v, u, d + 1);
        }
        R[u] = time;
    };
    dfs(1, -1, 0);

    auto rmq = [&]() {
        for (int i = 1; i < 20; i++) {
            for (int j = 1; j <= n; j++) {
                if ((1 << i) > dep[j]) continue;
                int k = dp[j][i - 1];
                dp[j][i] = dp[k][i - 1];
            }
        }
    };
    rmq();

    auto query = [&](int x, int y) {
        if (dep[x] > dep[y]) swap(x, y);
        for (int j = 19; j >= 0 && dep[x] != dep[y]; j--) {
            if (dep[y] - (1 << j) < dep[x]) continue;
            y = dp[y][j];
        }
        if (x == y) return x;
        for (int j = 19; j >= 0; j--) {
            if (dep[x] - (1 << j) < 0 || dp[x][j] == dp[y][j]) continue;
            x = dp[x][j], y = dp[y][j];
        }
        return dp[x][0];
    };
    auto jump = [&](int x, int d) {
        int now = x;
        for (int i = 19; i >= 0; i--) {
            if ((d >> i) & 1) {
                now = dp[now][i];
            }
        }
        return now;
    };

    LazySegmentTree<Info, Tag> seg(n);

    auto work = [&](int x, int y, int p) {
        int l1 = L[x], r1 = R[x] - 1;
        int l2 = L[y], r2 = R[y] - 1;
        // [0, n - 1]
        seg.rangeUpdate(0, n - 1, Tag(-1));
        seg.rangeUpdate(l1, r1, Tag(1));
        seg.rangeUpdate(l2, r2, Tag(1));
    };

    auto work2 = [&](int u, int v, int p) {
        if (u != p) swap(u, v);
        int c = jump(v, dep[v] - dep[u] - 1);
        int the_l = L[v], the_r = R[v] - 1;
        int l = L[c], r = R[c] - 1;
        seg.rangeUpdate(l, r, Tag(-1));
        seg.rangeUpdate(the_l, the_r, Tag(1));
    };

    for (int i = 0; i < m; i++) {
        if (vis[i] == 0) {
            auto [u, v] = edges[i];
            int p = query(u, v);
            if (p == u || p == v) {
                work2(u, v, p);
            } else {
                work(u, v, p);
            }
        }
    }

    string ans(n, '0');

    for (int i = 1; i <= n; i++) {
        if (seg.rangeQuery(L[i], L[i]).x == 0) {
            ans[i - 1] = '1';
        }
    }
    cout << ans << endl;
}