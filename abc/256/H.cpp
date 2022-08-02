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
typedef pair<pii, int> piii;
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

struct Tag {
    ll x;
    Tag(ll _x) : x(_x) {}
    Tag() { x = -1; }
    void apply(const Tag &v) {
        if (v.x != -1) {
            x = v.x;
        }
    }
};

struct Info {
    int l, r;
    ll sum;
    Info(int x, int idx) {
        l = r = idx;
        sum = x;
    }

    Info() { l = r = sum = 0; }

    void apply(const Tag &v) {
        if (v.x != -1) {
            sum = 1LL * v.x * (r - l + 1);
        }
    }

    friend Info operator+(const Info &a, const Info &b) {
        Info res;
        res.l = a.l, res.r = b.r;
        res.sum = a.sum + b.sum;
        return res;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    LazySegmentTree<Info, Tag> seg(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        seg.update(i - 1, Info(a[i], i - 1));
    }
    vector<piii> need_add(n);

    set<piii> S;
    int now = 1;

    while (now <= n) {
        int go = now;
        while (go <= n && a[go] == a[now]) {
            go++;
        }
        S.insert({{now, go - 1}, a[now]});
        now = go;
    }

    auto update = [&](int l, int r, int x, int flag) {
        auto it = S.lower_bound({{l + 1, -1}, -1});
        it--;
        auto it2 = S.lower_bound({{r + 1, -1}, -1});

        int ncnt = 0;
        auto add = [&](piii val) {
            if (ncnt > 0 && need_add[ncnt - 1].second == val.second) {
                need_add[ncnt - 1].first.second = val.first.second;
            } else {
                need_add[ncnt++] = val;
            }
        };

        while (it != it2) {
            int val = it->second;
            int the_l = max(l, it->first.first);
            int the_r = min(r, it->first.second);

            if (l > it->first.first) {
                add({{it->first.first, l - 1}, val});
            }
            if (flag == 1) {
                add({{the_l, the_r}, val / x});
            } else {
                add({{the_l, the_r}, x});
            }

            if (r < it->first.second) {
                add({{r + 1, it->first.second}, val});
            }
            it = S.erase(it);
        }
        it = S.lower_bound({{l + 1, -1}, -1});
        it2 = it;
        if (it != S.begin()) {
            it--;
            if (it->second == need_add[0].second) {
                need_add[0].first.first = it->first.first;
                S.erase(it);
            }
        }
        if (it2 != S.end()) {
            if (it2->second == need_add[ncnt - 1].second) {
                need_add[ncnt - 1].first.second = it2->first.second;
                S.erase(it2);
            }
        }
        for (int i = 0; i < ncnt; i++) {
            S.insert(need_add[i]);
            seg.rangeUpdate(need_add[i].first.first - 1, need_add[i].first.second - 1, Tag(need_add[i].second));
        }
    };

    auto query = [&](int l, int r) {
        return seg.rangeQuery(l - 1, r - 1).sum;

        // ll ans = 0;
        // auto it = S.lower_bound({{l + 1, -1}, -1});
        // it--;
        // auto it2 = S.lower_bound({{r + 1, -1}, -1});

        // while (it != it2) {
        //     int val = it->second;
        //     int the_l = max(l, it->first.first);
        //     int the_r = min(r, it->first.second);
        //     ans += 1LL * val * (the_r - the_l + 1);
        //     it++;
        // }
        // return ans;
    };

    while (q--) {
        int flag;
        cin >> flag;
        if (flag == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            update(l, r, x, flag);
        } else if (flag == 2) {
            int l, r, y;
            cin >> l >> r >> y;
            update(l, r, y, flag);
        } else {
            int l, r;
            cin >> l >> r;
            ll ans = query(l, r);
            cout << ans << endl;
        }
    }

    return 0;
}