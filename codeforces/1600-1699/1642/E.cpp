#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template <class Info, class Merge = std::plus<Info>>
struct SegmentTree {
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << __lg(n)) {}
    SegmentTree(vector<Info> init) : SegmentTree(init.size()) {
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

    Info rangeQuery(int l, int r) {
        return rangeQuery(l, r, 0, n - 1, 1);
    }

    void update(int L, Info v) {
        return update(L, v, 0, n - 1, 1);
    }

   private:
    const int n;
    const Merge merge;
    vector<Info> info;
    void push_up(int rt) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1]);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson));
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void update(int L, Info& v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = merge(info[rt], v);
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            update(L, v, lson);
        } else {
            update(L, v, rson);
        }
        push_up(rt);
    }
};

const int inf = (1 << 30) - 1;
struct Info {
    int x;
    Info(int _x) : x(_x) {}
    Info() {
        x = inf;
    }
};

Info operator+(const Info& a, const Info& b) {
    Info c;
    c.x = min(a.x, b.x);
    return c;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;

    set<int> S;
    for (int i = 0; i < n; i++) {
        S.insert(i);
    }
    SegmentTree<Info> seg(n);
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            if (x == 0) {
                while (true) {
                    auto it = S.lower_bound(l);
                    if (*it > r || it == S.end()) break;
                    S.erase(it);
                }
            } else {
                seg.update(l, Info(r));
            }
        } else {
            int j;
            cin >> j;
            j--;

            if (S.count(j) == 0) {
                cout << "NO" << endl;
            } else {
                int L = 0, R = n - 1;
                auto it = S.lower_bound(j);

                if (it != S.begin()) {
                    auto it2 = prev(it);
                    L = *it2 + 1;
                }
                auto it3 = next(it);
                if (it3 != S.end()) {
                    R = *it3 - 1;
                }
                debug(L, j);
                int tmp = seg.rangeQuery(L, j).x;
                if (tmp <= R) {
                    cout << "YES" << endl;
                } else {
                    cout << "N/A" << endl;
                }
            }
        }
    }
    return 0;
}