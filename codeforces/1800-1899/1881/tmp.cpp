#line 1 "G.cpp"
#include <bits/stdc++.h>

#line 2 "/Users/guoshen/code/library2/structure/segment-tree/lazy-segment-tree.hpp"
using namespace std;

/*
struct Tag {
    // 默认值
    Tag() {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
    }
};

struct Info {
    // 默认值
    Info() {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        return Info();
    }
};
*/

template <typename Info, typename Tag>
struct LazySegmentTree {
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
    LazySegmentTree(int n) : n(n), merge(Info::merge), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(vector<Info> &init) : LazySegmentTree(init.size()) {
        initSegmentTree(init);
    }

    void initSegmentTree(vector<Info> &init) {
        function<void(int, int, int)> build = [&](int l, int r, int rt) {
            tag[rt] = Tag();
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

    void assign(int L, const Info &v) {
        assign(L, v, 0, n - 1, 1);
    }

    void rangeUpdate(int L, int R, const Tag &v) {
        return rangeUpdate(L, R - 1, v, 0, n - 1, 1);
    }

    Info rangeQuery(int L, int R) {
        return rangeQuery(L, R - 1, 0, n - 1, 1);
    }

    int find_first(int ll, int rr, const function<bool(const Info &)> &f) {  // 找到第一个满足 f 的位置 idx, 可以理解在原数组中[ll, idx - 1] 都不满足 f
        return find_first(ll, rr - 1, f, 0, n - 1, 1);
    }

    int find_last(int ll, int rr, const function<bool(const Info &)> &f) {  // 从后往前找，找到第一个满足 f 的位置
        return find_last(ll, rr - 1, f, 0, n - 1, 1);
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

    void assign(int L, const Info &v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m) {
            assign(L, v, lson);
        } else {
            assign(L, v, rson);
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

    int find_first_knowingly(const function<bool(const Info &)> &f, int l, int r, int rt) {
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

    int find_first(int L, int R, const function<bool(const Info &)> &f, int l, int r, int rt) {
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

    int find_last_knowingly(const function<bool(const Info &)> &f, int l, int r, int rt) {
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

    int find_last(int L, int R, const function<bool(const Info &)> &f, int l, int r, int rt) {
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

#undef lson
#undef rson
};
#line 4 "G.cpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

struct Tag {
    // 默认值
    int offset;
    Tag(int offset = 0) : offset(offset) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.offset) {
            (offset += v.offset) %= 26;
        }
    }
};

const int inf = 1e9;

struct Info {
    // 默认值
    int min_dis[26], left_idx[26], right_idx[26];
    Info() {
        for (int i = 0; i < 26; i++) {
            left_idx[i] = right_idx[i] = -1;
            min_dis[i] = inf;
        }
    }

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.offset) {
            int tmp[26];

            for (int i = 0; i < 26; i++) {
                tmp[(i + v.offset) % 26] = min_dis[i];
            }

            for (int i = 0; i < 26; i++) {
                min_dis[i] = tmp[i];
            }

            for (int i = 0; i < 26; i++) {
                tmp[(i + v.offset) % 26] = left_idx[i];
            }

            for (int i = 0; i < 26; i++) {
                left_idx[i] = tmp[i];
            }

            for (int i = 0; i < 26; i++) {
                tmp[(i + v.offset) % 26] = right_idx[i];
            }

            for (int i = 0; i < 26; i++) {
                right_idx[i] = tmp[i];
            }
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        Info res = Info();

        for (int i = 0; i < 26; i++) {
            res.left_idx[i] = left_info.left_idx[i];
            if (res.left_idx[i] == -1) {
                res.left_idx[i] = right_info.left_idx[i];
            }

            res.right_idx[i] = right_info.right_idx[i];
            if (res.right_idx[i] == -1) {
                res.right_idx[i] = left_info.right_idx[i];
            }

            res.min_dis[i] = min(left_info.min_dis[i], right_info.min_dis[i]);

            if (left_info.right_idx[i] != -1 && right_info.left_idx[i] != -1) {
                res.min_dis[i] = min(res.min_dis[i], right_info.left_idx[i] - left_info.right_idx[i]);
            }
        }
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    LazySegmentTree<Info, Tag> st(n);
    vector<Info> infos(n);
    for (int i = 0; i < n; i++) {
        infos[i].left_idx[s[i] - 'a'] = i;
        infos[i].right_idx[s[i] - 'a'] = i;
    }
    st.initSegmentTree(infos);

    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            st.rangeUpdate(l, r + 1, Tag(x));
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            auto it = st.rangeQuery(l, r + 1);
            bool ok = true;
            for (int i = 0; i < 26; i++) {
                if (it.min_dis[i] <= 2) {
                    ok = false;
                    break;
                } 
            }
            if (ok) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
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
    return 0;
}
