#include <bits/stdc++.h>

#include <limits>

#include "./structure/segment-tree/lazy-segment-tree.hpp"

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
    long long num;
    Tag(long long num = -1) : num(num) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.num != -1) {
            num = v.num;
        }
    }
};

struct Info {
    // 默认值
    long long sum;
    Info(long long sum = 0) : sum(sum) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.num != -1) {
            sum = 1LL * (r - l + 1) * v.num;
        }
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        return Info(left_info.sum + right_info.sum);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n), sum(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum[i] = a[i];
        if (i) sum[i] += sum[i - 1];
    }

    LazySegmentTree<Info, Tag> st(n);
    st.assign(0, Info(a[0]));

    for (int i = 1; i < n; i++) {
        debug(i);
        int l = 0, r = i - 1;
        int ans = -1;
        while (l <= r) {
            int m = l + r >> 1;
            long long avg = sum[i];
            if (m) avg -= sum[m - 1];
            avg = avg / (i - m + 1);
            if (st.rangeQuery(m, m + 1).sum >= avg) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        debug(i, ans);
        if (ans == -1) {
            st.assign(i, Info(a[i]));
        } else {
            long long tmp = sum[i];
            if (ans) tmp -= sum[ans - 1];
            long long avg = tmp / (i - ans + 1);
            long long more = tmp % (i - ans + 1);
            debug(avg, more);
            int len = i - ans + 1;
            int left = ans;
            int right = i - more;
            st.rangeUpdate(left, right + 1, Tag(avg));
            if (more > 0) {
                st.rangeUpdate(right + 1, i + 1, Tag(avg + 1));
            }
        }
    }

    const long long inf = numeric_limits<long long>::max() / 2;
    long long mx = -inf, mi = inf;
    for (int i = 0; i < n; i++) {
        long long it = st.rangeQuery(i, i + 1).sum;
        debug(i, it);
        mx = max(mx, it);
        mi = min(mi, it);
    }
    cout << mx - mi << endl;
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