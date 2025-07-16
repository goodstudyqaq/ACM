#line 1 "H2.cpp"
#include <bits/stdc++.h>

#line 3 "/Users/guoshen/code/library2/structure/segment-tree/dynamic-segment-tree.hpp"
using namespace std;

/*
struct Info {
    // 默认值
    Info(int len) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        return Info();
    }

    string to_string() {
        return "";
    }
};

*/

struct Info {
    // 默认值
    int lsum, rsum, mx_sum, sum;

    Info(int lsum, int rsum, int mx_sum, int sum) : lsum(lsum), rsum(rsum), mx_sum(mx_sum), sum(sum) {}
    Info(int len = 1) {
        lsum = 0, rsum = 0, mx_sum = 0, sum = -len;
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        int lsum = max(left_info.lsum, left_info.sum + right_info.lsum);
        int rsum = max(right_info.rsum, right_info.sum + left_info.rsum);
        int mx_sum = max({0, left_info.mx_sum, right_info.mx_sum, left_info.rsum + right_info.lsum});
        lsum = max(0, lsum);
        rsum = max(0, rsum);
        int sum = left_info.sum + right_info.sum;
        return Info(lsum, rsum, mx_sum, sum);
    }

    string to_string() {
        return "";
    }
};

const int maxn = 64e5;
int pool[maxn], left_son[maxn], right_son[maxn];
int cnt = 0, top = 0;

Info info[maxn];

struct DynamicSegtree {
#define lson l, m, left_son[rt]
#define rson m + 1, r, right_son[rt]
    DynamicSegtree() : DynamicSegtree(0) {}
    DynamicSegtree(int n) : n(n) {
        rt = new_node(n);
    }

    void assign(int idx, Info info) {
        assign(idx, info, 0, n - 1, rt);
    }

    void del(int idx) {
        del(idx, 0, n - 1, rt, -1, 0);
    }

    Info rangeQuery(int l, int r) {
        return rangeQuery(l, r - 1, 0, n - 1, rt);
    }

   private:
    int n;
    int rt;
    // vector<Info> info;
    // vector<int> pool;
    // vector<int> left_son, right_son;

    int new_node(int len) {
        if (top) {
            int u = pool[top - 1];
            top--;
            left_son[u] = -1;
            right_son[u] = -1;
            info[u] = Info(len);
            return u;
        } else {
            int sz = cnt;
            info[sz] = Info(len);
            left_son[sz] = -1;
            right_son[sz] = -1;
            cnt++;
            return sz;
        }
    }

    void push_up(int rt, int l, int r) {
        int m = l + r >> 1;
        Info left = left_son[rt] == -1 ? Info(m - l + 1) : info[left_son[rt]];
        Info right = right_son[rt] == -1 ? Info(r - m) : info[right_son[rt]];
        info[rt] = Info::merge(left, right, l, r);
    }

    void assign(int L, const Info &v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            if (left_son[rt] == -1) {
                left_son[rt] = new_node(m - l + 1);
            }
            assign(L, v, lson);
        } else {
            if (right_son[rt] == -1) {
                right_son[rt] = new_node(r - m);
            }
            assign(L, v, rson);
        }
        push_up(rt, l, r);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        if (L <= m && R > m) {
            Info left = left_son[rt] == -1 ? Info(m - L + 1) : rangeQuery(L, R, lson);
            Info right = right_son[rt] == -1 ? Info(R - m) : rangeQuery(L, R, rson);
            return Info::merge(left, right, l, r);
        } else if (L <= m) {
            Info left = left_son[rt] == -1 ? Info(m - L + 1) : rangeQuery(L, R, lson);
            return left;
        } else {
            Info right = right_son[rt] == -1 ? Info(R - m) : rangeQuery(L, R, rson);
            return right;
        }
    }

    void del(int L, int l, int r, int rt, int pa, int flag) {
        /*
        pa: 该点的父亲
        flag: 该点是父亲的左节点：0，1：右节点
        */

        if (l == r) {
            info[rt] = Info(1);
            if (pa != -1) {
                pool[top++] = rt;
                if (flag == 0) {
                    left_son[pa] = -1;
                } else {
                    right_son[pa] = -1;
                }
            }
            return;
        }

        int m = l + r >> 1;
        if (L <= m) {
            del(L, lson, rt, 0);
        } else {
            del(L, rson, rt, 1);
        }

        if (left_son[rt] == -1 && right_son[rt] == -1 && pa != -1) {
            pool[top++] = rt;
            if (flag == 0) {
                left_son[pa] = -1;
            } else {
                right_son[pa] = -1;
            }
            info[rt] = Info(r - l + 1);
        } else {
            push_up(rt, l, r);
        }
    }

#undef lson
#undef rson
};
#line 4 "H2.cpp"

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

DynamicSegtree seg[300000];
int a[300000];

multiset<int> S;
void solve() {
    S.clear();
    top = 0;
    cnt = 0;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        seg[i] = DynamicSegtree(n);
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        seg[a[i]].assign(i, Info(1, 1, 1, 1));
    }

    for (int i = 0; i < n; i++) {
        S.insert(seg[i].rangeQuery(0, n).mx_sum);
    }
    debug(S);

    while (q--) {
        int idx, val;
        cin >> idx >> val;
        val--;
        idx--;
        S.extract(seg[a[idx]].rangeQuery(0, n).mx_sum);
        seg[a[idx]].del(idx);
        S.insert(seg[a[idx]].rangeQuery(0, n).mx_sum);

        S.extract(seg[val].rangeQuery(0, n).mx_sum);
        seg[val].assign(idx, Info(1, 1, 1, 1));
        S.insert(seg[val].rangeQuery(0, n).mx_sum);

        a[idx] = val;

        cout << *S.rbegin() / 2 << ' ';
    }
    cout << '\n';
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
