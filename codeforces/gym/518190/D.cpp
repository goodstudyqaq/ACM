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

struct Info {
    // 默认值
    int mx;
    int idx;
    Info(int _mx = 0, int _idx = -1) {
        mx = _mx;
        idx = _idx;
    }
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int mx = max(left_info.mx, right_info.mx);
        int idx = left_info.mx < right_info.mx ? right_info.idx : left_info.idx;
        return Info(mx, idx);
    };
};

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template <typename Info>
struct SegmentTree {
    SegmentTree(int n) : n(n), merge(Info::merge), info(4 << __lg(n)) {}
    SegmentTree(vector<Info> init) : SegmentTree(init.size()) {
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
        return rangeQuery(l, r, 0, n - 1, 1);
    }

    // 单点更新, 会将下标为 L 的点与 v 进行 merge 操作
    void update(int L, const Info& v) {
        return update(L, v, 0, n - 1, 1);
    }

    // 单点赋值, 会将下标为 L 的点直接赋值为 v
    void assign(int L, const Info& v) {
        return assign(L, v, 0, n - 1, 1);
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
};

struct State {
    int l, r, depth;
    bool operator<(const State& s) const {
        int len = r - l + 1;
        int len2 = s.r - s.l + 1;
        return len < len2;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long m;
    cin >> m;
    long long cpm = m;

    SegmentTree<Info> seg(n);

    for (int i = 0; i < n; i++) {
        seg.assign(i, Info(a[i], i));
    }

    priority_queue<State> Q;
    Q.push(State{0, n - 1, n});

    long long ans = 0;
    while (!Q.empty() && m) {
        auto it = Q.top();
        Q.pop();

        int l = it.l, r = it.r, dep = it.depth;
        auto resp = seg.rangeQuery(l, r);
        int idx = resp.idx, mx = resp.mx;

        if (mx == dep) {
            if (l < idx) {
                Q.push(State{l, idx - 1, dep});
            }
            if (r > idx) {
                Q.push(State{idx + 1, r, dep});
            }
        } else {
            long long tmp = 1LL * (r - l + 1) * (dep - mx);
            long long use = min(m, tmp);
            m -= use;
            if (m > 0) {
                ans += (dep - mx);
            } else {
                ans += (use - 1) / (r - l + 1) + 1;
            }

            if (l < idx) {
                Q.push(State{l, idx - 1, mx});
            }
            if (r > idx) {
                Q.push(State{idx + 1, r, mx});
            }
        }
    }
    // debug(ans);

    cout << cpm - ans << endl;
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