#line 1 "G3.cpp"
#include <bits/stdc++.h>

using namespace std;
template <typename T>
struct Matrix {
    // array<array<T, 3>, 3> A;
    T A[3][3];
    int n, m;

    Matrix() {}
    Matrix(int n, int m) : n(n), m(m) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                A[i][j] = 0;
            }
        }
    }
    Matrix(int n) : n(n), m(n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                A[i][j] = 0;
            }
        }
    }

    int height() const {
        return n;
    }

    int width() const {
        return m;
    }

    inline const auto operator[](int k) const {
        return A[k];
    }
    inline auto operator[](int k) {
        return A[k];
    }

    static Matrix I(int n) {
        Matrix<T> mat(n);
        for (int i = 0; i < n; i++) {
            mat[i][i] = 1;
        }
        return mat;
    }

    Matrix &operator+=(const Matrix &b) {
        int n = height(), m = width();
        assert(n == b.height() && m == b.width());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] += b[i][j];
            }
        }
        return (*this);
    }

    Matrix &operator-=(const Matrix &b) {
        int n = height(), m = width();
        assert(n == b.height() && m == b.width());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] -= b[i][j];
            }
        }
        return (*this);
    }

    Matrix &operator*=(const Matrix &b) {
        int n = height(), m = b.width(), p = width();

        // assert(p == b.height());

        Matrix<T> C(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < p; k++) {
                    C[i][j] += (*this)[i][k] * b[k][j];
                }
            }
        }
        swap(this->A, C.A);
        return (*this);
    }

    Matrix &operator^=(long long k) {
        Matrix<T> b = Matrix<T>::I(height());
        while (k) {
            if (k & 1) b *= *this;
            *this *= *this;
            k >>= 1LL;
        }
        swap(this->A, b.A);
        return (*this);
    }

    Matrix operator+(const Matrix &b) const {
        return (Matrix(*this) += b);
    }

    Matrix operator-(const Matrix &b) const {
        return (Matrix(*this) -= b);
    }
    Matrix operator*(const Matrix &b) const {
        return (Matrix(*this) *= b);
    }
    Matrix operator^(const long long k) const {
        return (Matrix(*this) ^= k);
    }

    bool operator==(const Matrix &b) const {
        if (height() != b.height() || width() != b.width()) {
            return false;
        }
        int n = height();
        int m = width();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (A[i][j] != b[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
};
#line 2 "/Users/guoshen/code/library2/structure/segment-tree/lazy-segment-tree.hpp"
using namespace std;

template <typename Info, typename Tag>
struct LazySegmentTree {
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
    LazySegmentTree(int n) : n(n), merge(Info::merge), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(vector<Info> &init) : LazySegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int l, int r, int rt) {
            if (l == r) {
                info[rt] = init[l];
                return;
            }
            int m = l + r >> 1;
            build(lson);
            build(rson);
            push_up(l, r, rt);
        };
        build(0, n - 1, 1);
    }

    void assign(int L, const Info &v) {
        assign(L, v, 0, n - 1, 1);
    }

    void rangeUpdate(int L, int R, const Tag &v) {
        return rangeUpdate(L, R - 1, v, 0, n - 1, 1);
    }

    Info rangeQuery(int L, int R) {
        return rangeQuery(L, R - 1, 0, n - 1, 1);
    }

    int find_first(int ll, int rr, const function<bool(const Info &)> &f) {  // 找到第一个满足 f 的位置 idx, 使用这个函数的前提是在 [ll, idx - 1] 的任意区间都不满足 f,而对于任意 r，[ll, r], r >= idx 都满足 f。
        return find_first(ll, rr - 1, f, 0, n - 1, 1);
    }

    int find_last(int ll, int rr, const function<bool(const Info &)> &f) {  // 从后往前找，找到第一个满足 f 的位置
        return find_last(ll, rr - 1, f, 0, n - 1, 1);
    }

   private:
    const int n;
    vector<Info> info;
    vector<Tag> tag;
    const function<Info(const Info &, const Info &, int, int)> merge;
    void push_up(int l, int r, int rt) {
        info[rt] = merge(info[rt << 1], info[rt << 1 | 1], l, r);
    }

    void apply(int p, const Tag &v, int l, int r) {
        info[p].apply(v, l, r);
        tag[p].apply(v, l, r);
    }

    void push_down(int l, int r, int rt) {
        int m = l + r >> 1;
        apply(rt << 1, tag[rt], l, m);
        apply(rt << 1 | 1, tag[rt], m + 1, r);
        tag[rt] = Tag();
    }

    void assign(int L, const Info &v, int l, int r, int rt) {
        if (l == r) {
            info[rt] = v;
            return;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m) {
            assign(L, v, lson);
        } else {
            assign(L, v, rson);
        }
        push_up(l, r, rt);
    }

    Info rangeQuery(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return info[rt];
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m && R > m) {
            return merge(rangeQuery(L, R, lson), rangeQuery(L, R, rson), l, r);
        } else if (L <= m) {
            return rangeQuery(L, R, lson);
        } else {
            return rangeQuery(L, R, rson);
        }
    }

    void rangeUpdate(int L, int R, const Tag &v, int l, int r, int rt) {
        if (L <= l && r <= R) {
            apply(rt, v, l, r);
            return;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        if (L <= m) {
            rangeUpdate(L, R, v, lson);
        }
        if (R > m) {
            rangeUpdate(L, R, v, rson);
        }
        push_up(l, r, rt);
    }

    int find_first_knowingly(const function<bool(const Info &)> f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        int res;
        if (f(info[rt << 1])) {
            res = find_first_knowingly(f, lson);
        } else {
            res = find_first_knowingly(f, rson);
        }
        push_up(l, r, rt);
        return res;
    }

    int find_first(int L, int R, const function<bool(const Info &)> f, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (!f(info[rt])) {
                return -1;
            }
            return find_first_knowingly(f, l, r, rt);
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        int res = -1;
        if (L <= m) {
            res = find_first(L, R, f, lson);
        }
        if (R > m && res == -1) {
            res = find_first(L, R, f, rson);
        }
        push_up(l, r, rt);
        return res;
    }

    int find_last_knowingly(const function<bool(const Info &)> f, int l, int r, int rt) {
        if (l == r) {
            return l;
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        int res;
        if (f(info[rt << 1 | 1])) {
            res = find_last_knowingly(f, rson);
        } else {
            res = find_last_knowingly(f, lson);
        }
        push_up(l, r, rt);
        return res;
    }

    int find_last(int L, int R, const function<bool(const Info &)> f, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (!f(info[rt])) {
                return -1;
            }
            return find_last_knowingly(f, l, r, rt);
        }
        int m = l + r >> 1;
        push_down(l, r, rt);
        int res = -1;
        if (R > m) {
            res = find_last(L, R, f, rson);
        }
        if (L <= m && res == -1) {
            res = find_last(L, R, f, lson);
        }
        push_up(l, r, rt);
        return res;
    }

#undef lson
#undef rson
};
#line 5 "G3.cpp"

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

const Matrix<long long> mat_i = Matrix<long long>().I(3);
const Matrix<long long> mat_zero = Matrix<long long>(1, 3);

struct Tag {
    // 默认值
    Matrix<long long> mat;
    Tag(Matrix<long long> mat = mat_i) : mat(mat) {}
    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.mat == mat_i) {
            return;
        }
        mat *= v.mat;
    }
};

struct Info {
    // 默认值
    Matrix<long long> mat;
    Info(Matrix<long long> mat = mat_zero) : mat(mat) {}

    // apply 之前需要判断 v 是否为默认值
    void apply(const Tag &v, int l, int r) {
        if (v.mat == mat_i) {
            return;
        }
        mat *= v.mat;
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

    map<int, int> cnt, mp;
    auto add = [&](int x) {
        if (--mp[cnt[x]] == 0) {
            mp.erase(cnt[x]);
        }
        cnt[x]++;
        mp[cnt[x]]++;
    };
    auto del = [&](int x) {
        if (--mp[cnt[x]] == 0) {
            mp.erase(cnt[x]);
        }
        cnt[x]--;
        mp[cnt[x]]++;
    };
    for (int i = 0; i < k; ++i) {
        cnt[a[i]]++;
    }
    for (auto [_, v] : cnt) {
        mp[v]++;
    }

    vector<int> ans(n - k + 1);

    for (int i = 0; i + k - 1 < n; ++i) {
        ans[i] = k - mp.rbegin()->first;
        if (i + k < n) {
            del(a[i]);
            add(a[i + k]);
        }
    }


    vector<vector<pii>> queries(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        r = r - k + 1;
        l--, r--;
        queries[l].emplace_back(r, i);
    }

    Matrix<long long> tmp(1, 3);
    tmp[0][2] = 1;

    vector<Info> infos(n - k + 1, Info(tmp));

    LazySegmentTree<Info, Tag> st(infos);

    auto get_mat = [&](int val) {
        Matrix<long long> mat(3);
        mat[0][0] = mat[1][0] = mat[1][1] = mat[2][2] = 1;
        mat[2][0] = mat[2][1] = val;
        return mat;
    };

    vector<int> stk;
    vector<long long> res(q);
    for (int i = n - k; i >= 0; i--) {
        int last = ans[i];
        int last_idx = i;
        // debug(i, stk);
        while (stk.size() && ans[stk.back()] >= ans[i]) {
            auto mat = get_mat(last);
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
            res[idx] = tmp.mat[0][0];
        }
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << '\n';
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
