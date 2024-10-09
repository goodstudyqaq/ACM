#include <bits/stdc++.h>

#include "./math/matrix/matrix.hpp"
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
    Matrix<long long> mat;
    Tag(Matrix<long long> mat = Matrix<long long>().I(3)) : mat(mat) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        mat = mat * v.mat;
    }
};

struct Info {
    // 默认值
    Matrix<long long> mat;
    Info(Matrix<long long> mat = Matrix<long long>(3)) : mat(mat) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        mat = mat * v.mat;
    }
    static Info merge(const Info &left_info, const Info &right_info, int l, int r) {
        return Info(left_info.mat + right_info.mat);
    }
};

void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= i;
    }

    vector<int> ans(n - k + 1);

    map<int, int> cnt;
    set<pii> S;
    int r = 0;
    for (int i = 0; i <= n - k; i++) {
        while (r < i + k) {
            int before_cnt = cnt[a[r]];
            S.erase({before_cnt, a[r]});
            cnt[a[r]]++;
            S.insert({cnt[a[r]], a[r]});
            r++;
        }

        auto it = prev(S.end());
        ans[i] = k - it->first;

        S.erase({cnt[a[i]], a[i]});
        cnt[a[i]]--;
        if (cnt[a[i]]) {
            S.insert({cnt[a[i]], a[i]});
        }
    }

    vector<vector<pii>> queries(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        r = r - k + 1;
        l--, r--;
        queries[l].push_back({r, i});
    }

    LazySegmentTree<Info, Tag> st(n - k + 1);
    Matrix<long long> tmp(3);
    tmp[2][2] = 1;
    for (int i = 0; i < n - k + 1; i++) {
        st.assign(i, Info(tmp));
    }

    auto get_mat = [&](int val) {
        Matrix<long long> mat(3);
        mat[0][0] = mat[1][0] = mat[1][1] = mat[2][2] = 1;
        mat[2][0] = mat[2][1] = val;
        return mat;
    };

    vector<int> stk;
    vector<int> res(q);
    debug(ans);
    for (int i = n - k; i >= 0; i--) {
        int last = ans[i];
        int last_idx = i;
        // debug(i, stk);
        while (stk.size() && ans[stk.back()] >= ans[i]) {
            auto mat = get_mat(last);
            // debug(last_idx, stk.back(), last);
            st.rangeUpdate(last_idx, stk.back(), Tag(mat));
            last = ans[i] - ans[stk.back()];
            last_idx = stk.back();
            stk.pop_back();
        }
        if (stk.size()) {
            st.rangeUpdate(last_idx, stk.back(), Tag(get_mat(last)));
            st.rangeUpdate(stk.back(), n - k + 1, Tag(get_mat(0)));
        } else {
            st.rangeUpdate(last_idx, n - k + 1, Tag(get_mat(last)));
        }
        stk.push_back(i);

        for (auto it : queries[i]) {
            auto [r, idx] = it;
            auto tmp = st.rangeQuery(i, r + 1);
            // debug(i, r);

            // for (int i = 0; i < 3; i++) {
            //     for (int j = 0; j < 3; j++) {
            //         cout << tmp.mat[i][j] << ' ';
            //     }
            //     cout << endl;
            // }

            res[idx] = tmp.mat[2][0];
        }
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << endl;
    }
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