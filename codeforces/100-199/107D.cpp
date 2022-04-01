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
const int maxn = 125;
const int mod = 12345;
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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    long long n, c;
    cin >> n >> c;
    vector<vector<int>> V;
    V.resize(26);
    for (int i = 1; i <= c; i++) {
        char it;
        int num;
        cin >> it >> num;
        V[it - 'A'].push_back(num);
    }

    int x = 1;

    vector<int> have;
    vector<vector<int>> V2;
    V2.resize(26);
    int v2_cnt = 0;
    for (int i = 0; i < 26; i++) {
        if (V[i].size()) {
            sort(V[i].begin(), V[i].end());
            int mx = 1;
            for (auto it : V[i]) {
                V2[v2_cnt].push_back(it);
                mx *= it;
            }
            v2_cnt++;
            have.push_back(mx);
            x *= mx;
        }
    }
    debug(have);
    int hz = have.size();
    // Matrix m = Matrix(x);
    debug(have);
    Matrix m = Matrix(x);
    debug(have);
    for (int i = 0; i < x; i++) {
        int tmp = have.size();
        vector<int> now(hz);
        int _x = i;
        for (int j = 0; j < hz; j++) {
            now[j] = _x % have[j];
            _x /= have[j];
        }
        debug(i, now);
        int now_x = 1;
        for (int j = 0; j < have.size(); j++) {
            if (now[j] < have[j] - 1) {
                int s2 = i + now_x;
                m.mat[i][s2]++;
                m.mat[i][s2] %= mod;
            } else {
                int s2 = i - now_x * now[j];
                m.mat[i][s2]++;
                m.mat[i][s2] %= mod;
            }
            now_x *= have[j];
        }
    }
    // m.out();
    Matrix res = quick_mul(m, n);
    debug(n);
    // res.out();
    long long ans = 0;
    for (int i = 0; i < x; i++) {
        vector<int> now(hz);
        int now_x = 1;
        bool f = true;
        for (int j = 0; j < have.size(); j++) {
            now[j] = (i / now_x) % have[j];
            now_x *= have[j];

            bool f2 = false;
            for (auto it : V2[j]) {
                if (now[j] % it == 0) {
                    f2 = true;
                }
            }
            if (!f2) {
                f = false;
                break;
            }
        }
        if (f) {
            (ans += res.mat[0][i]) %= mod;
        }
    }
    cout << ans << endl;
    return 0;
}