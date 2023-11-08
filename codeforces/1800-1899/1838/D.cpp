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

struct Tag {
    // 默认值
    Tag() {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {}
};

struct Info {
    // 默认值
    int sum;
    int l, r;
    Info() {
        sum = 0;
        l = r = -1;
    }

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {}

    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        Info res;
        res.sum = left_info.sum + right_info.sum;
        res.l = l, res.r = r;
        return res;
    }
};

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template <typename Info, typename Tag>
struct LazySegmentTree {
    LazySegmentTree(int n) : n(n), merge(Info::merge), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(vector<Info> &init) : LazySegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int l, int r, int rt) {
            if (l == r) {
                info[rt] = init[l];
                return;
            }
            int m = l + r >> 1;
            build(lson);
            build(rson);
            push_up(l, r, rt);
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
    vector<Info> info;
    vector<Tag> tag;
    const function<Info(const Info &, const Info &, int, int)> merge;
    void push_up(int l, int r, int rt) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1], l, r);
    }

    void apply(int p, const Tag &v, int l, int r) {
        info[p].apply(v, l, r);
        tag[p].apply(v, l, r);
    }

    void push_down(int l, int r, int rt) {
        int m = l + r >> 1;
        apply(rt << 1, tag[rt], l, m);
        apply(rt << 1 | 1, tag[rt], m + 1, r);
        tag[rt] = Tag();
    }

    void update(int L, const Info &v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m) {
            update(L, v, lson);
        } else {
            update(L, v, rson);
        }
        push_up(l, r, rt);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson), l, r);
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void rangeUpdate(int L, int R, const Tag &v, int l, int r, int rt) {
        if (L <= l && r <= R) {
            apply(rt, v, l, r);
            return;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m) {
            rangeUpdate(L, R, v, lson);
        }
        if (R > m) {
            rangeUpdate(L, R, v, rson);
        }
        push_up(l, r, rt);
    }

    int find_first_knowingly(const function<bool(const Info &)> f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        int res;
        if (f(info[rt << 1])) {
            res = find_first_knowingly(f, lson);
        } else {
            res = find_first_knowingly(f, rson);
        }
        push_up(l, r, rt);
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
        push_down(l, r, rt);
        int res = -1;
        if (L <= m) {
            res = find_first(L, R, f, lson);
        }
        if (R > m && res == -1) {
            res = find_first(L, R, f, rson);
        }
        push_up(l, r, rt);
        return res;
    }

    int find_last_knowingly(const function<bool(const Info &)> f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        int res;
        if (f(info[rt << 1 | 1])) {
            res = find_last_knowingly(f, rson);
        } else {
            res = find_last_knowingly(f, lson);
        }
        push_up(l, r, rt);
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
        push_down(l, r, rt);
        int res = -1;
        if (R > m) {
            res = find_last(L, R, f, rson);
        }
        if (L <= m && res == -1) {
            res = find_last(L, R, f, lson);
        }
        push_up(l, r, rt);
        return res;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    string s;
    cin >> n >> q >> s;

    if (n % 2) {
        while (q--) {
            int t;
            cin >> t;
            cout << "NO" << endl;
        }
        return 0;
    }

    LazySegmentTree<Info, Tag> seg1(n / 2), seg2(n / 2);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0 && s[i] == '(') {
            Info info;
            info.l = info.r = i / 2;
            info.sum = 1;
            seg1.update(i / 2, info);
        } else if (i % 2 == 1 && s[i] == ')') {
            Info info;
            info.l = info.r = i / 2;
            info.sum = 1;
            seg2.update(i / 2, info);
        }
    }

    map<char, char> other;
    other['('] = ')';
    other[')'] = '(';
    while (q--) {
        int idx;
        cin >> idx;
        idx--;
        s[idx] = other[s[idx]];
        debug(s);

        if (idx % 2 == 0) {
            if (s[idx] == '(') {
                Info info;
                info.l = info.r = idx / 2;
                info.sum = 1;
                seg1.update(idx / 2, info);
            } else {
                Info info;
                info.l = info.r = idx / 2;
                info.sum = 0;
                seg1.update(idx / 2, info);
            }
        } else if (idx % 2 == 1) {
            if (s[idx] == ')') {
                Info info;
                info.l = info.r = idx / 2;
                info.sum = 1;
                seg2.update(idx / 2, info);
            } else {
                Info info;
                info.l = info.r = idx / 2;
                info.sum = 0;
                seg2.update(idx / 2, info);
            }
        }

        const function<bool(const Info &info)> f = [&](const Info &info) -> bool {
            int l = info.l, r = info.r;
            int len = r - l + 1;
            return info.sum != len;
        };

        int l1 = seg1.find_first(0, n / 2 - 1, f);
        if (l1 == -1) l1 = n / 2;
        int l2 = seg2.find_first(0, n / 2 - 1, f);
        if (l2 == -1) l2 = n / 2;
        auto it = seg2.rangeQuery(0, 0);
        int l = min(l1, l2);
        debug(q, l, l1, l2);
        if (l == n / 2) {
            cout << "YES" << endl;
            continue;
        }
        int idxl = l * 2;
        if (s[idxl] != '(' || s[idxl + 1] != '(') {
            cout << "NO" << endl;
            continue;
        }

        int r1 = seg1.find_last(0, n / 2 - 1, f);
        int r2 = seg2.find_last(0, n - 1, f);

        int r = max(r1, r2);

        int idxr = r * 2;

        if (s[idxr] != ')' || s[idxr + 1] != ')') {
            cout << "NO" << endl;
            continue;
        }

        cout << "YES" << endl;
    }
}