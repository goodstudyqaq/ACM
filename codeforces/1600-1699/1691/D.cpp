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

const ll inf = numeric_limits<ll>::max() / 2;
struct Info {
    ll x;
    Info(ll _x = inf) {
        x = _x;
    }
};

Info operator+(const Info& a, const Info& b) {
    Info c;
    c.x = min(a.x, b.x);
    return c;
}

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > 0 && a[i - 1] > 0) {
            flag = true;
        }
    }

    if (flag) {
        cout << "NO" << endl;
        return;
    }

    auto get_flag = [&](ll v) {
        return v >= 0;
    };

    int now = 1;
    vector<ll> V;
    while (now <= n) {
        int go = now;
        ll sum = 0;
        while (go <= n && get_flag(a[go]) == get_flag(a[now])) {
            sum += a[go];
            go++;
        }
        V.push_back(sum);

        if (get_flag(a[now])) {
            int num = 0;
            for (int i = now; i < go; i++) {
                if (a[i] > 0) num++;
            }
            if (num > 1) {
                cout << "NO" << endl;
                return;
            }
        }

        now = go;
    }

    auto check = [&]() -> bool {
        int sz = V.size();

        vector<ll> sum(sz);
        vector<Info> beg(sz + 1);
        beg[0].x = 0;
        for (int i = 0; i < sz; i++) {
            sum[i] = V[i];
            if (i) sum[i] += sum[i - 1];
            beg[i + 1].x = sum[i];
        }
        SegmentTree<Info> segment(beg);
        vector<int> stk;
        for (int i = 0; i < sz; i++) {
            if (V[i] < 0) continue;
            while (stk.size() && V[stk.back()] <= V[i]) {
                stk.pop_back();
            }
            int Left;
            if (stk.size() == 0) {
                Left = -1;
            } else {
                Left = stk.back();
            }
            ll v1 = sum[i];
            ll num = V[i];
            Info v2 = segment.rangeQuery(Left + 1, i);
            if (v1 - v2.x > num) {
                debug(i, v1, v2.x, Left + 1, V);
                return false;
            }

            stk.push_back(i);
        }
        return true;
    };

    if (!check()) {
        cout << "NO" << endl;
        return;
    }
    reverse(V.begin(), V.end());
    if (!check()) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
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
}