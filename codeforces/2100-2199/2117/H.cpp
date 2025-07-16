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
    int lsum, rsum, mx_sum, sum;
    // 默认值
    Info(int lsum = 0, int rsum = 0, int mx_sum = 0, int sum = -1) : lsum(lsum), rsum(rsum), mx_sum(mx_sum), sum(sum) {}
    static Info merge(const Info& left_info, const Info& right_info, int l, int r) {
        int lsum = max(left_info.lsum, left_info.sum + right_info.lsum);
        int rsum = max(right_info.rsum, right_info.sum + left_info.rsum);
        int mx_sum = max({0, left_info.mx_sum, right_info.mx_sum, left_info.rsum + right_info.lsum});
        lsum = max(0, lsum);
        rsum = max(0, rsum);
        int sum = left_info.sum + right_info.sum;
        return Info{lsum, rsum, mx_sum, sum};
    }
    string to_string() {
        return "";
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<vector<int>> idx(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        idx[a[i]].push_back(i);
    }

    typedef array<int, 2> a2;
    typedef array<int, 3> a3;
    vector<a2> query(q);
    vector<vector<a3>> change(n + 1);

    vector<int> now = a;

    for (int i = 0; i < q; i++) {
        cin >> query[i][0] >> query[i][1];
        query[i][0]--;
        if (now[query[i][0]] != query[i][1]) {
            change[now[query[i][0]]].push_back({i, -1, query[i][0]});
            change[query[i][1]].push_back({i, 1, query[i][0]});
        }
        now[query[i][0]] = query[i][1];
    }

    vector<Info> infos(n);
    SegmentTree<Info> seg(infos);

    vector<int> ans(q + 1);

    multiset<int> S;

    vector<vector<a2>> change_set(q);

    for (int i = 1; i <= n; i++) {
        set<int> S2;
        for (auto pos : idx[i]) {
            seg.assign(pos, Info(1, 1, 1, 1));
            S2.insert(pos);
        }
        int res = seg.rangeQuery(0, n).mx_sum / 2;
        S.insert(res);

        for (auto c : change[i]) {
            auto [q_idx, val, c_idx] = c;

            int tmp_res = seg.rangeQuery(0, n).mx_sum / 2;

            change_set[q_idx].push_back({tmp_res, -1});

            if (val == 1) {
                // 把 c_idx 位置的值改成 i, 对于 i 来说这个位置的贡献变成 1
                seg.assign(c_idx, Info(1, 1, 1, 1));
                S2.insert(c_idx);
            } else {
                // 把 c_idx 位置的值改成其他值，那么对于 i 来说这个位置的贡献变成 -1
                seg.assign(c_idx, Info());
                S2.erase(c_idx);
            }
            tmp_res = seg.rangeQuery(0, n).mx_sum / 2;
            change_set[q_idx].push_back({tmp_res, 1});
        }

        for (auto it : S2) {
            seg.assign(it, Info());
        }
    }

    for (int i = 0; i < q; i++) {
        for (auto val : change_set[i]) {
            if (val[1] > 0) {
                S.insert(val[0]);
            } else {
                S.erase(S.find(val[0]));
            }
        }

        cout << *S.rbegin() << ' ';
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