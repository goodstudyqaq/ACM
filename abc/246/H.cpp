#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template <class Info, class Merge = std::multiplies<Info>>
struct SegmentTree {
    const int n;
    const Merge merge;
    vector<Info> info;
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
    Info rangeQuery(int l, int r) {
        return rangeQuery(l, r, 0, n - 1, 1);
    }

    void update(int L, Info& val, int l, int r, int rt) {
        if (l == r) {
            info[rt] = val;
            return;
        }
        int m = l + r >> 1;
        if (L <= m) {
            update(L, val, lson);
        } else {
            update(L, val, rson);
        }
        push_up(rt);
    }

    void update(int L, Info& val) {
        update(L, val, 0, n - 1, 1);
    }
};

const int mod = 998244353;
struct Matrix {
    int n, m;
    vector<vector<long long>> mat;
    Matrix() {}
    Matrix(int _n) {
        n = _n;
        m = _n;
        mat.resize(n, vector<long long>(n, 0));
    }

    Matrix(int _n, int _m) {
        n = _n;
        m = _m;
        mat.resize(n, vector<long long>(m, 0));
    }

    Matrix operator*(const Matrix& b) const {
        assert(m == b.n);
        Matrix res = Matrix(n, b.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < b.m; j++)
                for (int k = 0; k < m; k++) {
                    long long tmp = (mat[i][k] * b.mat[k][j]) % mod;
                    (res.mat[i][j] += tmp) %= mod;
                }
        return res;
    }

    Matrix operator^(long long num) {
        assert(n == m);
        Matrix res = Matrix(n);
        for (int i = 0; i < n; i++) {
            res.mat[i][i] = 1;
        }
        Matrix tmp = *this;
        while (num) {
            if (num % 2) res = res * tmp;
            num /= 2;
            tmp = tmp * tmp;
        }
        return res;
    }
};

string to_string(Matrix& m) {
    string res = "\n";
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            res += to_string(m.mat[i][j]) + " ";
        }
        if (i != m.n - 1)
            res += "\n";
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    map<char, Matrix> M;
    Matrix m(3);
    m.mat[0][0] = m.mat[0][1] = m.mat[0][2] = 1;
    m.mat[1][1] = 1;
    m.mat[2][2] = 1;
    M['0'] = m;
    m = Matrix(3);
    m.mat[0][0] = 1;
    m.mat[1][0] = m.mat[1][1] = m.mat[1][2] = 1;
    m.mat[2][2] = 1;
    M['1'] = m;

    m = Matrix(3);
    m.mat[0][0] = m.mat[0][1] = m.mat[0][2] = 1;
    m.mat[1][0] = m.mat[1][1] = m.mat[1][2] = 1;
    m.mat[2][2] = 1;
    M['?'] = m;

    vector<Matrix> mats(n);
    for (int i = 0; i < n; i++) {
        mats[i] = M[s[i]];
    }
    SegmentTree<Matrix> seg(mats);

    Matrix begin(3, 1);
    begin.mat[2][0] = 1;
    while (q--) {
        int x;
        char c;
        cin >> x >> c;
        s[x - 1] = c;
        auto it = M[c];
        seg.update(x - 1, it);
        auto it2 = seg.rangeQuery(0, n - 1);
        auto it3 = it2 * begin;
        long long ans = (it3.mat[0][0] + it3.mat[1][0]) % mod;
        cout << ans << endl;
    }
    return 0;
}