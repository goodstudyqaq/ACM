#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 105;
typedef long long ll;
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

    //行列式辗转相除法
    /*
    https://atcoder.jp/contests/abc253/tasks/abc253_h
    矩阵树定理：维护一个度数矩阵D 和一个邻接矩阵A，Kirchhoff矩阵= D - A，然后把最后一行和最后一列删掉，算行列式，就是树的个数。
    */
    ll det(ll mod) {
        ll ret = 1;
        for (int i = 0; i < n; i++) {
            if (mat[i][i] < 0) {
                ret = -ret;
                for (int k = i; k < n; k++) mat[i][k] = -mat[i][k];
            }
            for (int j = i + 1; j < n; j++) {
                for (int k = i; k < n; k++) mat[i][k] %= mod, mat[j][k] %= mod;
                while (mat[j][i]) {
                    if (mat[j][i] < 0) {
                        ret = -ret;
                        for (int k = i; k < n; k++) mat[j][k] = -mat[j][k];
                    }
                    ll t = mat[i][i] / mat[j][i];
                    for (int k = i; k < n; k++) mat[i][k] = (mat[i][k] - t * mat[j][k]) % mod;
                    for (int k = i; k < n; k++) swap(mat[i][k], mat[j][k]);
                    ret = -ret;
                }
            }
            if (mat[i][i] == 0) return 0;
            ret = ret * mat[i][i] % mod;
        }
        return (ret + mod) % mod;
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