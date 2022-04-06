#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 105;
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