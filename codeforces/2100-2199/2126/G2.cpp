#include <bits/stdc++.h>

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
    int lm, rm, sum;
    Info(int lm = -1, int rm = -1, int sum = -1) : lm(lm), rm(rm), sum(sum) {
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int lm = max(left_info.lm, left_info.sum + right_info.lm);
        int rm = max(right_info.rm, right_info.sum + left_info.rm);
        int sum = left_info.sum + right_info.sum;
        return Info(lm, rm, sum);
    }
    string to_string() {
        return "";
    }
};
// 能开多大就开多大
// 线段树 -> 4 * N. 每次操作就要增加 log(N) 个点，要操作 N 次那么总共要的就是 :4N + Nlog(N).
// N = 2e5 4N + Nlog(N) = 8e5 + 34e5 = 42e5
const int maxn = 64e5;
int left_son[maxn], right_son[maxn];
int cnt = 0;

Info info[maxn];

struct PersistentSegmentTree {
#define lson l, m, left_son[rt]
#define rson m + 1, r, right_son[rt]
    PersistentSegmentTree(int n) : n(n), merge(Info::merge) {}
    int build(vector<Info>& init) {
        function<int(int, int)> build = [&](int l, int r) -> int {
            if (l == r) {
                int p = new_node();
                info[p] = init[l];
                return p;
            }
            int m = l + r >> 1;
            int p = new_node();
            left_son[p] = build(l, m);
            right_son[p] = build(m + 1, r);
            push_up(p, l, r);
            return p;
        };
        return build(0, n - 1);
    }
    int update(int L, const Info& v, int rt) {
        return update(L, v, 0, n - 1, rt);
    }

    int assign(int L, const Info& v, int rt) {
        return assign(L, v, 0, n - 1, rt);
    }

    Info rangeQuery(int L, int R, int rt) {
        return rangeQuery(L, R - 1, 0, n - 1, rt);
    }

   private:
    int n;
    const function<Info(const Info&, const Info&, int, int)> merge;

    int new_node() {
        left_son[cnt] = -1;
        right_son[cnt] = -1;
        info[cnt] = Info();
        return cnt++;
    }

    void push_up(int rt, int l, int r) {
        info[rt] = merge(info[left_son[rt]], info[right_son[rt]], l, r);
    }

    int update(int L, const Info& v, int l, int r, int rt) {
        if (l == r) {
            int p = new_node();
            info[p] = merge(info[rt], v, l, r);
            return p;
        }
        int m = l + r >> 1;
        int p = new_node();
        if (L <= m) {
            left_son[p] = update(L, v, lson);
            right_son[p] = right_son[rt];
        } else {
            right_son[p] = update(L, v, rson);
            left_son[p] = left_son[rt];
        }
        push_up(p, l, r);
        return p;
    }

    int assign(int L, const Info& v, int l, int r, int rt) {
        if (l == r) {
            int p = new_node();
            info[p] = v;
            return p;
        }
        int m = l + r >> 1;
        int p = new_node();
        if (L <= m) {
            left_son[p] = assign(L, v, lson);
            right_son[p] = right_son[rt];
        } else {
            right_son[p] = assign(L, v, rson);
            left_son[p] = left_son[rt];
        }
        push_up(p, l, r);
        return p;
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
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> f(n);
    iota(f.begin(), f.end(), 0);
    sort(f.begin(), f.end(), [&](int x, int y) {
        return a[x] > a[y];
    });

    PersistentSegmentTree st(n);
    vector<Info> init(n);
    vector<int> rts(n + 1);
    rts[0] = st.build(init);

    for (int i = 0; i < n; i++) {
        int idx = f[i];
        rts[i + 1] = st.assign(idx, Info(1, 1, 1), rts[i]);
    }

    vector<int> nxt(n, n), pre(n, -1);
    vector<int> stk;

    for (int i = 0; i < n; i++) {
        int val = a[i];
        while (stk.size() && a[stk.back()] >= val) {
            nxt[stk.back()] = i;
            stk.pop_back();
        }
        if (stk.size()) {
            pre[i] = stk.back();
        }
        stk.push_back(i);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int L = pre[i], R = nxt[i];
        // (l, r)
        int l = 0, r = n - 1;
        // l = 0, r = 0;
        int res = -1;
        while (l <= r) {
            int m = l + r >> 1;
            int rt = rts[m + 1];
            int tmp1 = st.rangeQuery(L + 1, i + 1, rt).rm;
            int tmp2 = st.rangeQuery(i, i + 1, rt).sum;
            int tmp3 = st.rangeQuery(i, R, rt).lm;
            int tmp = tmp1 + tmp3 - tmp2;
            // debug(tmp1, tmp2, tmp3);

            if (tmp >= 0) {
                res = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        int med = a[f[res]];

        // debug(L, R, i, f[res], med, a[i], med - a[i]);
        ans = max(ans, med - a[i]);
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