#line 1 "E1.cpp"
#include <bits/stdc++.h>

#line 6 "E1.cpp"

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
#line 8 "E1.cpp"

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
    int mi;
    Info(int mi = 1e9) : mi(mi) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info(min(left_info.mi, right_info.mi));
    }
    string to_string() {
        return "";
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(2 * n), b(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[n + i] = a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        b[n + i] = b[i];
    }

    vector<long long> sum(2 * n);
    vector<long long> X;
    X.push_back(0);
    for (int i = 0; i < 2 * n; i++) {
        sum[i] = a[i] - b[i];
        if (i) {
            sum[i] += sum[i - 1];
        }
        X.push_back(sum[i]);
    }
    sort(X.begin(), X.end());
    X.resize(unique(X.begin(), X.end()) - X.begin());

    int sz = X.size();
    SegmentTree<Info> seg(sz);

    int ans = 1;
    for (int i = 2 * n - 1; i >= 0; i--) {
        if (i < n) {
            long long val = a[i] - b[i];
            if (val > 0) {
                long long tmp = i == 0 ? 0 : sum[i - 1];
                int idx = upper_bound(X.begin(), X.end(), tmp) - X.begin();
                auto it = seg.rangeQuery(0, idx).mi;
                // debug(i, it);
                if (it != 1e9) {
                    ans = max(ans, it - i + 1);
                }
            }

        }
        long long val = sum[i];
        int idx = lower_bound(X.begin(), X.end(), val) - X.begin();
        seg.update(idx, Info(i));
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
