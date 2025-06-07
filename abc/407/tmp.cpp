#line 1 "E.cpp"
#include <bits/stdc++.h>

#line 4 "E.cpp"

#line 2 "/Users/guoshen/code/library2/structure/segment-tree/segment-tree.hpp"

#line 4 "/Users/guoshen/code/library2/structure/segment-tree/segment-tree.hpp"
using namespace std;
/*
半群单点更新，区间查询操作
半群定义见 sparse-table.hpp
todo: find_first + find_last
 */
/*
struct Info {
    // 默认值
    Info() {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info();
    }
    string to_string() {
        return "";
    }
};
*/

template <typename Info>
struct SegmentTree {
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

    SegmentTree(int n) : n(n), merge(Info::merge), info(4 << __lg(n)) {}
    SegmentTree(const vector<Info>& init) : SegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int l, int r, int rt) {
            if (l == r) {
                info[rt] = init[l];
                return;
            }
            int m = l + r >> 1;
            build(lson);
            build(rson);
            push_up(rt, l, r);
        };
        build(0, n - 1, 1);
    }

    Info rangeQuery(int l, int r) {
        return rangeQuery(l, r - 1, 0, n - 1, 1);
    }

    // 单点更新, 会将下标为 L 的点与 v 进行 merge 操作
    void update(int L, const Info& v) {
        return update(L, v, 0, n - 1, 1);
    }

    // 单点赋值, 会将下标为 L 的点直接赋值为 v
    void assign(int L, const Info& v) {
        return assign(L, v, 0, n - 1, 1);
    }

    int find_first(int ll, int rr, const function<bool(const Info&)>& f) {
        return find_first(ll, rr - 1, f, 0, n - 1, 1);
    }

    int find_last(int ll, int rr, const function<bool(const Info&)>& f) {
        return find_last(ll, rr - 1, f, 0, n - 1, 1);
    }

    string to_string(int u, int l, int r, string prefix, bool is_lch) {
        if (l > r) {
            return "";
        }
        string m_prefix = prefix + (u != 1 ? ((is_lch ? "╭── " : "╰── ")) : "");
        string m_res = info[u].to_string() + "\n";
        string l_res, r_res;
        if (l < r) {
            string l_prefix = prefix + ((u != 1) ? (is_lch ? "    " : "│   ") : "");
            string r_prefix = prefix + ((u != 1) ? (!is_lch ? "    " : "│   ") : "");
            l_res = to_string(u * 2, l, l + r >> 1, l_prefix, true);
            r_res = to_string(u * 2 + 1, (l + r >> 1) + 1, r, r_prefix, false);
        }
        return l_res + m_prefix + m_res + r_res;
    }
    string to_string() {
        return to_string(1, 0, n - 1, "", false);
    }

   private:
    const int n;
    vector<Info> info;
    const function<Info(const Info&, const Info&, int, int)> merge;

    void push_up(int rt, int l, int r) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1], l, r);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson), l, r);
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void update(int L, const Info& v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = merge(info[rt], v, l, r);
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            update(L, v, lson);
        } else {
            update(L, v, rson);
        }
        push_up(rt, l, r);
    }

    void assign(int L, const Info& v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            assign(L, v, lson);
        } else {
            assign(L, v, rson);
        }
        push_up(rt, l, r);
    }

    int find_first_knowingly(const function<bool(const Info&)>& f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        int res;
        if (f(info[rt << 1])) {
            res = find_first_knowingly(f, lson);
        } else {
            res = find_first_knowingly(f, rson);
        }
        return res;
    }

    int find_first(int L, int R, const function<bool(const Info&)>& f, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (!f(info[rt])) {
                return -1;
            }
            return find_first_knowingly(f, l, r, rt);
        }
        int m = l + r >> 1;
        int res = -1;
        if (L <= m) {
            res = find_first(L, R, f, lson);
        }
        if (R > m && res == -1) {
            res = find_first(L, R, f, rson);
        }
        return res;
    }

    int find_last(int L, int R, const function<bool(const Info&)>& f, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (!f(info[rt])) {
                return -1;
            }
            return find_last_knowingly(f, l, r, rt);
        }
        int m = l + r >> 1;
        int res = -1;
        if (R > m) {
            res = find_last(L, R, f, rson);
        }
        if (L <= m && res == -1) {
            res = find_last(L, R, f, lson);
        }
        return res;
    }

#undef lson
#undef rson
};

template <typename Info>
string to_string(SegmentTree<Info> st) {
    return "\n" + st.to_string();
}
#line 6 "E.cpp"

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
const int inf = 1e9 + 1;
struct Info {
    // 默认值
    int mx_idx, mi_idx;
    int mx_val, mi_val;
    Info(int mx_val = -1, int mi_val = inf, int mx_idx = 0, int mi_idx = 0) : mx_val(mx_val), mi_val(mi_val), mx_idx(mx_idx), mi_idx(mi_idx) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int mx_val = max(left_info.mx_val, right_info.mx_val);
        int mi_val = min(left_info.mi_val, right_info.mi_val);
        int mx_idx = mx_val == left_info.mx_val ? left_info.mx_idx : right_info.mx_idx;
        int mi_idx = mi_val == right_info.mi_val ? right_info.mi_idx : left_info.mi_idx;
        return Info(mx_val, mi_val, mx_idx, mi_idx);
    }
    string to_string() {
        return "";
    }
};

void solve() {
    int n;
    cin >> n;
    int N = n * 2;
    vector<int> a(N);
    vector<Info> infos(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        infos[i] = Info{a[i], a[i], i, i};
    }
    SegmentTree<Info> seg(infos);

    int times = n;
    long long ans = 0;
    while (times--) {
        auto it = seg.rangeQuery(0, N);
        int idx1 = it.mx_idx;
        auto it2 = seg.rangeQuery(idx1 + 1, N);
        if (it2.mi_val == inf) {
            // 没有值
            it = seg.rangeQuery(0, idx1);
            idx1 = it.mx_idx;
            it2 = seg.rangeQuery(idx1 + 1, N);
        }
        debug(idx1);
        ans += it.mx_val;
        seg.assign(idx1, Info{});
        seg.assign(it2.mi_idx, Info{});
    }
    cout << ans << '\n';
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
