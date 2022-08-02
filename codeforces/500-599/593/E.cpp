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

typedef unsigned long long ll;
const int maxn = 25;
const int mod = 1e9 + 7;

struct Matrix {
    int n;
    ll mat[maxn][maxn];
    Matrix() {}
    Matrix(int _n) {
        n = _n;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = 0;
    }
    Matrix operator*(const Matrix &b) const {
        Matrix res = Matrix(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) {
                    ll tmp = (mat[i][k] * b.mat[k][j]) % mod;
                    (res.mat[i][j] += tmp) %= mod;
                }
        return res;
    }

    void out() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << mat[i][j] << " ";
            cout << endl;
        }
        cout << "**********" << endl;
    }
};

Matrix quick_mul(Matrix a, long long num) {
    Matrix e(a.n);
    for (int i = 0; i < e.n; i++)
        e.mat[i][i] = 1;
    Matrix tmp = a;
    while (num) {
        if (num % 2) e = e * tmp;
        num /= 2;
        tmp = tmp * tmp;
    }
    return e;
}

typedef pair<int, int> pii;
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> mp;
    mp.resize(n, vector<int>(m, 0));
    int num = n * m;
    Matrix now = Matrix(num);

    auto get_idx = [&](int x, int y) -> int {
        return x * m + y;
    };

    auto get_cor = [&](int idx) -> pii {
        return {idx / m, idx % m};
    };
    int d[5][2] = {-1, 0, 1, 0, 0, -1, 0, 1, 0, 0};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int idx1 = get_idx(i, j);
            for (int k = 0; k < 5; k++) {
                int tmpx = i + d[k][0];
                int tmpy = j + d[k][1];
                if (tmpx >= 0 && tmpx < n && tmpy >= 0 && tmpy < m) {
                    int idx2 = get_idx(tmpx, tmpy);
                    now.mat[idx1][idx2] = now.mat[idx2][idx1] = 1;
                }
            }
        }
    }
    Matrix mat = now;
    int now_t = 2;
    while (q--) {
        int tp, x, y, t;
        cin >> tp >> x >> y >> t;
        x--, y--;
        int idx = get_idx(x, y);
        int tmp_t = t - now_t;
        Matrix tmp = quick_mul(mat, tmp_t);
        now = now * tmp;
        now_t = t;
        if (tp == 1) {
            cout << now.mat[0][idx] << endl;
        } else if (tp == 2) {
            mp[x][y] = 1;
            for (int i = 0; i < 5; i++) {
                int tmpx = x + d[i][0];
                int tmpy = y + d[i][1];
                if (tmpx >= 0 && tmpx < n && tmpy >= 0 && tmpy < m) {
                    int idx2 = get_idx(tmpx, tmpy);
                    mat.mat[idx][idx2] = mat.mat[idx2][idx] = 0;
                }
            }
        } else {
            mp[x][y] = 0;
            for (int i = 0; i < 5; i++) {
                int tmpx = x + d[i][0];
                int tmpy = y + d[i][1];
                if (tmpx >= 0 && tmpx < n && tmpy >= 0 && tmpy < m) {
                    if (mp[tmpx][tmpy] == 0) {
                        int idx2 = get_idx(tmpx, tmpy);
                        mat.mat[idx][idx2] = mat.mat[idx2][idx] = 1;
                    }
                }
            }
        }
    }
    return 0;
}