#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
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

template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a;
        swap(a, m);
        u -= t * v;
        swap(u, v);
    }
    assert(m == 1);
    return u;
}

template <typename T>
class Modular {
   public:
    using Type = typename decay<decltype(T::value)>::type;

    constexpr Modular() : value() {}
    template <typename U>
    Modular(const U& x) {
        value = normalize(x);
    }

    template <typename U>
    static Type normalize(const U& x) {
        Type v;
        if (-mod() <= x && x < mod())
            v = static_cast<Type>(x);
        else
            v = static_cast<Type>(x % mod());
        if (v < 0) v += mod();
        return v;
    }

    const Type& operator()() const { return value; }
    template <typename U>
    explicit operator U() const { return static_cast<U>(value); }
    constexpr static Type mod() { return T::value; }

    Modular& operator+=(const Modular& other) {
        if ((value += other.value) >= mod()) value -= mod();
        return *this;
    }
    Modular& operator-=(const Modular& other) {
        if ((value -= other.value) < 0) value += mod();
        return *this;
    }
    template <typename U>
    Modular& operator+=(const U& other) { return *this += Modular(other); }
    template <typename U>
    Modular& operator-=(const U& other) { return *this -= Modular(other); }
    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }
    Modular operator++(int) {
        Modular result(*this);
        *this += 1;
        return result;
    }
    Modular operator--(int) {
        Modular result(*this);
        *this -= 1;
        return result;
    }
    Modular operator-() const { return Modular(-value); }

    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
        uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
        uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
        asm(
            "divl %4; \n\t"
            : "=a"(d), "=d"(m)
            : "d"(xh), "a"(xl), "r"(mod()));
        value = m;
#else
        value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
        return *this;
    }
    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, long long>::value, Modular>::type& operator*=(const Modular& rhs) {
        long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
        value = normalize(value * rhs.value - q * mod());
        return *this;
    }
    template <typename U = T>
    typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
        value = normalize(value * rhs.value);
        return *this;
    }

    Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

    friend const Type& abs(const Modular& x) { return x.value; }

    template <typename U>
    friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

    template <typename U>
    friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

    template <typename V, typename U>
    friend V& operator>>(V& stream, Modular<U>& number);

   private:
    Type value;
};

template <typename T>
bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U>
bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U>
bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }

template <typename T>
bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U>
bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U>
bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }

template <typename T>
bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }

template <typename T>
Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U>
Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U>
Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }

template <typename T>
Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U>
Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U>
Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }

template <typename T>
Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U>
Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U>
Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }

template <typename T>
Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U>
Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U>
Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

template <typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
    assert(b >= 0);
    Modular<T> x = a, res = 1;
    U p = b;
    while (p > 0) {
        if (p & 1) res *= x;
        x *= x;
        p >>= 1;
    }
    return res;
}

template <typename T>
bool IsZero(const Modular<T>& number) {
    return number() == 0;
}

template <typename T>
string to_string(const Modular<T>& number) {
    return to_string(number());
}

// U == std::ostream? but done this way because of fastoutput
template <typename U, typename T>
U& operator<<(U& stream, const Modular<T>& number) {
    return stream << number();
}

// U == std::istream? but done this way because of fastinput
template <typename U, typename T>
U& operator>>(U& stream, Modular<T>& number) {
    typename common_type<typename Modular<T>::Type, long long>::type x;
    stream >> x;
    number.value = Modular<T>::normalize(x);
    return stream;
}

/*
using ModType = int;
 
struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modular<VarMod>;
*/

constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

/*vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);
 
Mint C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  while ((int) fact.size() < n + 1) {
    fact.push_back(fact.back() * (int) fact.size());
    inv_fact.push_back(1 / fact.back());
  }
  return fact[n] * inv_fact[k] * inv_fact[n - k];
}*/

typedef long double ld;
const ld eps = 1e-10;
const int maxn = 20;
const int mod = 998244353;
int sgn(ld x) {
    if (fabs(x) < eps)
        return 0;
    else if (x > 0)
        return 1;
    return -1;
}

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
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    Matrix A, C, D;
    int n, m;
    cin >> n >> m;

    vector<vector<int>> V(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    int LIMIT = 1 << n;
    vector<Mint> f(LIMIT);
    for (int i = 1; i < LIMIT; i++) {
        vector<int> vis(n, -1);
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                vis[j] = cnt++;
            }
        }
        if (cnt == 1) continue;
        A = Matrix(cnt);
        C = Matrix(cnt);
        D = Matrix(cnt);

        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                int idx1 = vis[j];
                for (auto v : V[j]) {
                    if (vis[v] == -1) continue;
                    int idx2 = vis[v];
                    A.mat[idx1][idx2]++;
                    D.mat[idx1][idx1]++;
                }
            }
        }

        for (int j = 0; j < cnt; j++) {
            for (int k = 0; k < cnt; k++) {
                C.mat[j][k] = D.mat[j][k] - A.mat[j][k];
            }
        }
        C.n--, C.m--;
        Mint tmp = C.det(mod);
        f[i] = tmp;
    }
    debug(f);

    vector<vector<Mint>> g = vector(LIMIT, vector(n, Mint(0)));
    g[0][0] = 1;
    // g[s][i]
    vector<Mint> ans(n);
    for (int s = 0; s < LIMIT; s++) {
        for (int i = 0; i < n; i++) {
            if (g[s][i] == 0) continue;
            ans[i] += g[s][i];
            for (int s2 = 1; s2 < LIMIT; s2++) {
                if (((s & s2) == 0) && s < s2) {  // 要有偏序，不然重复计算
                    int num = __builtin_popcount(s2);
                    g[s | s2][i + num - 1] += Mint(f[s2]) * Mint(g[s][i]);
                }
            }
        }
    }
    debug(g);

    vector<Mint> fact(n);
    fact[0] = 1;
    for (int i = 1; i < n; i++) {
        fact[i] = fact[i - 1] * i;
    }
    debug(ans);
    for (int i = 1; i < n; i++) {
        ans[i] = ans[i] * fact[i] / Mint(power(Mint(m), i));
        cout << ans[i] << endl;
    }
    return 0;
}