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
};

const int inf = 1e9;
struct Tag {
    int x;
    Tag(int _x) : x(_x) {}
    Tag() { x = -1; }
    void apply(const Tag &v) {
        x = max(x, v.x);
    }
};

struct Info {
    int x;
    Info(int _x = -1) {
        x = _x;
    }

    void apply(const Tag &v) {
        x = max(x, v.x);
    }

    friend Info operator+(const Info &a, const Info &b) {
        Info res;
        res.x = max(a.x, b.x);
        return res;
    }
};

struct node {
    int c, l, r;
};

void solve() {
    int n;
    cin >> n;
    vector<node> nodes(n);
    vector<int> x;
    for (int i = 0; i < n; i++) {
        cin >> nodes[i].c >> nodes[i].l >> nodes[i].r;
        x.push_back(nodes[i].l);
        x.push_back(nodes[i].r);
    }
    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());

    int x_sz = x.size();

    auto get_idx = [&](int val) {
        return lower_bound(x.begin(), x.end(), val) - x.begin();
    };

    for (int i = 0; i < n; i++) {
        nodes[i].l = get_idx(nodes[i].l);
        nodes[i].r = get_idx(nodes[i].r);
    }

    auto solve = [&](int flag, vector<node> &nodes) -> int {
        LazySegmentTree<Info, Tag> seg(x_sz);
        vector<node> new_nodes;
        int n = nodes.size();
        for (int i = 0; i < n; i++) {
            if (nodes[i].c == flag) {
                int l = nodes[i].l, r = nodes[i].r;
                debug(i, l, r);
                seg.rangeUpdate(l, r, Tag(r));
                new_nodes.push_back(nodes[i]);
            }
        }
        typedef pair<int, int> pii;
        typedef pair<pii, int> piii;

        vector<piii> V2;

        for (int i = 0; i < n; i++) {
            if (nodes[i].c == !flag) {
                int l_idx = nodes[i].l, r_idx = nodes[i].r;
                Info tmp = seg.rangeQuery(l_idx, r_idx);
                V2.push_back({{l_idx, r_idx}, -tmp.x});
            }
        }
        sort(V2.begin(), V2.end());

        int sz = V2.size();
        int ans = 0;
        debug(V2);
        debug(x);

        int now = 0;

        while (now < sz) {
            auto it = V2[now];
            int R = -it.second;
            if (R < 0) {
                ans++;
                new_nodes.push_back((node){!flag, it.first.first, it.first.second});
                now++;
                continue;
            }
            if (!flag) ans++;
            int go = now;

            while (go < sz && V2[go].first.first <= R) {
                int tmp_R = -V2[go].second;
                R = max(R, tmp_R);
                go++;
            }

            new_nodes.push_back((node){!flag, it.first.first, V2[go - 1].first.second});

            now = go;
        }
        nodes = new_nodes;
        return ans;
    };

    int res = solve(0, nodes);
    debug(res);
    debug(nodes.size());
    res += solve(1, nodes);
    cout << res << endl;
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