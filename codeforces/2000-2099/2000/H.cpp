#include <bits/stdc++.h>

#include "./structure/segment-tree/segment-tree.hpp"

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