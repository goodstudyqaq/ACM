#line 1 "D.cpp"
#include <bits/stdc++.h>

#line 2 "/Users/guoshen/code/library2/math/matrix/matrix.hpp"

#line 1 "/Users/guoshen/code/library2/structure/others/md-vector.hpp"
// http://oj.daimayuan.top/course/15/problem/637 二维树状数组模板题
#line 3 "/Users/guoshen/code/library2/structure/others/md-vector.hpp"
using namespace std;
// 多维动态大小数组，可以用于DP等场景。
template <typename T, int dimensions>
class md_vector;

template <int dimensions>
int md_size(const array<int, dimensions>& dsize) {
    int base = 1;
    for (int i = 0; i < dimensions; i++) {
        base *= dsize[i];
    }
    return base;
}

template <typename T, int dimensions, int idx_dimensions>
class md_vector_index {
   public:
    md_vector_index(md_vector<T, dimensions>& vec, int base = 0) : vector_(vec), base_(base) {
    }

    auto operator[](int v) {
        assert(v < vector_.dsize_[idx_dimensions - 1]);
        return md_vector_index<T, dimensions, idx_dimensions + 1>(vector_, (base_ + v) * vector_.dsize_[idx_dimensions]);
    }

   private:
    md_vector<T, dimensions>& vector_;
    int base_;
};

template <typename T, int dimensions>
class md_vector_index<T, dimensions, dimensions> {
   public:
    md_vector_index(md_vector<T, dimensions>& vec, int base = 0) : vector_(vec), base_(base) {
    }

    T& operator[](int v) {
        return vector_.data_[base_ + v];
    }

    md_vector<T, dimensions>& vector_;
    int base_;
};

template <typename T, int dimensions>
class md_vector {
   public:
    md_vector() {}
    md_vector(const md_vector<T, dimensions>& other) : data_(other.data_), dsize_(other.dsize_) {
    }

    md_vector(array<int, dimensions> dsize, T default_value = T())
        : dsize_(dsize), data_(md_size<dimensions>(dsize), default_value) {
    }

    md_vector& operator=(md_vector<T, dimensions>&& other) {
        data_ = other.data_;
        dsize_ = other.dsize_;
        return *this;
    }

    auto operator[](int v) {
        return md_vector_index<T, dimensions, 1>(*this)[v];
    }

    T& operator[](array<int, dimensions> idx) {
        int base = 0;
        for (int i = 0; i < dimensions; i++) {
            base *= dsize_[i];
            base += idx[i];
        }
        return data_[base];
    }

    vector<T> data_;
    array<int, dimensions> dsize_;
};

template <typename T, int dimensions>
istream& operator>>(istream& in, md_vector<T, dimensions>& vec) {
    return in >> vec.data_;
}

template <typename T, int dimensions>
void make_md_presum(md_vector<T, dimensions>& vec) {
    int diff = 1, base = 0;
    for (int currD = dimensions - 1; currD >= 0; currD--) {
        base = diff * vec.dsize_[currD];
        for (int i = 0; i + diff < vec.data_.size(); i++) {
            if (i % base + diff < base) {
                vec.data_[i + diff] += vec.data_[i];
            }
        }
        diff = base;
    }
}

template <typename T, int dimensions, int idx_dimensions>
string to_string(md_vector_index<T, dimensions, idx_dimensions>& vec) {
    int sz = vec.vector_.dsize_[idx_dimensions - 1];
    string s = "{";
    for (int i = 0; i < sz; i++) {
        s += to_string(vec[i]);
        if (i != sz - 1) {
            s += ", ";
        }
    }
    s += "}";
    return s;
}

template <typename T, int dimensions>
string to_string(md_vector<T, dimensions>& vec) {
    int sz = vec.dsize_[0];
    string s = "{";
    for (int i = 0; i < sz; i++) {
        auto it = vec[i];
        s += to_string(it);
        if (i != sz - 1) {
            s += ", ";
        }
    }
    s += "}";
    return s;
}
#line 4 "/Users/guoshen/code/library2/math/matrix/matrix.hpp"

using namespace std;
template <typename T>
struct Matrix {
    md_vector<T, 2> A;

    Matrix() {}
    Matrix(int n, int m) : A({n, m}) {}
    Matrix(int n) : A({n, n}) {}

    int height() const {
        return A.dsize_[0];
    }

    int width() const {
        return A.dsize_[1];
    }

    inline auto operator[](int k) { return A[k]; }

    static Matrix I(int n) {
        Matrix<T> mat(n);
        for (int i = 0; i < n; i++) {
            mat[i][i] = 1;
        }
        return mat;
    }

    Matrix &operator+=(Matrix &b) {
        int n = height(), m = width();
        assert(n == b.height() && m == b.width());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] += b[i][j];
            }
        }
        return (*this);
    }

    Matrix &operator-=(Matrix &b) {
        int n = height(), m = width();
        assert(n == b.height() && m == b.width());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] -= b[i][j];
            }
        }
        return (*this);
    }

    Matrix &operator*=(Matrix &b) {
        int n = height(), m = b.width(), p = width();

        assert(p == b.height());

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

    Matrix operator+(const Matrix &b) {
        return (Matrix(*this) += b);
    }

    Matrix operator-(const Matrix &b) {
        return (Matrix(*this) -= b);
    }
    Matrix operator*(const Matrix &b) {
        return (Matrix(*this) *= b);
    }
    Matrix operator^(const long long k) {
        return (Matrix(*this) ^= k);
    }

    T determinant() {
        // 行列式辗转相除法
        assert(this->height() == this->width());
        Matrix<T> B(*this);
        T res = 1;
        int n = this->height();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                while (B[j][i] != 0) {
                    T t = B[i][i] / B[j][i];
                    for (int k = i; k < n; k++) {
                        B[i][k] -= B[j][k] * t;
                        swap(B[i][k], B[j][k]);
                    }
                    res = -res;
                }
            }
            if (B[i][i] == 0) return 0;
            res *= B[i][i];
        }
        return res;
    }
};
#line 2 "/Users/guoshen/code/library2/math/mint.hpp"
using namespace std;
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

/*
constexpr int md = 998244353;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);

Mint C(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    while ((int)fact.size() < n + 1) {
        fact.push_back(fact.back() * (int)fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}

Mint A(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    while ((int)fact.size() < n + 1) {
        fact.push_back(fact.back() * (int)fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[n - k];
}

*/
#line 5 "D.cpp"

using namespace std;

constexpr int md = 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

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

void solve() {
    long long n, m;
    cin >> n >> m;
    if (n <= m - 1) {
        cout << 1 << endl;
        return;
    }
    if (n == m) {
        cout << 2 << endl;
        return;
    }

    Matrix<Mint> mat(m, m);
    mat[0][0] = 1;
    mat[0][m - 1] = 1;

    for (int i = 1; i < m; i++) {
        mat[i][i - 1] = 1;
    }

    long long times = n - m;
    auto mat2 = mat ^ times;
    Mint res = 0;
    for (int i = 0; i < m; i++) {
        res += mat2[0][i];
    }
    res += mat2[0][0];
    cout << res << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
