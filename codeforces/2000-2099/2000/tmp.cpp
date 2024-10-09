#line 1 "H.cpp"
#include <bits/stdc++.h>

#line 2 "/Users/guoshen/code/library2/structure/segment-tree/segment-tree.hpp"
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

    //    private:
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
#undef lson
#undef rson
};

template <typename Info>
string to_string(SegmentTree<Info> st) {
    return "\n" + st.to_string();
}
#line 4 "H.cpp"

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
struct Info {
    // 默认值
    int lmx, rmx, mx;
    Info(int lmx = 0, int rmx = 0, int mx = 0) : lmx(lmx), rmx(rmx), mx(mx) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int m = l + r >> 1;
        int left_len = m - l + 1;
        int right_len = r - m;
        int lmx, rmx, mx;
        if (left_info.lmx == left_len) {
            lmx = left_info.lmx + right_info.lmx;
        } else {
            lmx = left_info.lmx;
        }

        if (right_info.rmx == right_len) {
            rmx = right_info.rmx + left_info.rmx;
        } else {
            rmx = right_info.rmx;
        }

        mx = max({lmx, rmx, left_info.rmx + right_info.lmx, left_info.mx, right_info.mx});
        return Info(lmx, rmx, mx);
    }
    string to_string() {
        return "";
    }
};
const int maxn = 4e6 + 1;
vector<Info> v(maxn, Info(1, 1, 1));
SegmentTree<Info> st(v);

void solve() {
    int n;
    cin >> n;
    set<int> S;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        S.insert(a);
        st.assign(a, Info());
    }

    function<int(int, int, int, int)> query = [&](int x, int l, int r, int rt) -> int {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        if (st.info[rt << 1].mx >= x) {
            return query(x, l, m, rt << 1);
        } else if (st.info[rt << 1].rmx + st.info[rt << 1 | 1].lmx >= x) {
            int tmp = st.info[rt << 1].rmx;
            return m - tmp + 1;
        } else {
            return query(x, m + 1, r, rt << 1 | 1);
        }
    };

    int m;
    cin >> m;

    while (m--) {
        char c;
        int x;
        cin >> c >> x;
        if (c == '+') {
            S.insert(x);
            st.assign(x, Info());
        } else if (c == '-') {
            S.erase(x);
            st.assign(x, Info(1, 1, 1));
        } else {
            cout << query(x, 0, maxn - 1, 1) << ' ';
        }
    }
    cout << endl;

    for (auto it : S) {
        st.assign(it, Info(1, 1, 1));
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    st.assign(0, Info());
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
