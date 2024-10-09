#line 1 "E3.cpp"
#include <bits/stdc++.h>

#line 2 "/Users/guoshen/code/library2/math/matrix/matrix.hpp"

#line 4 "/Users/guoshen/code/library2/structure/others/md-vector.hpp"
using namespace std;

// 多维动态大小数组，可以用于DP等场景。
template <typename T, size_t dimensions>
class md_vector;

namespace internal {
template <size_t dimensions>
size_t md_size(const array<size_t, dimensions>& dsize) {
    size_t base = 1;
    for (int i = 0; i < dimensions; i++) {
        base *= dsize[i];
    }
    return base;
}

template <typename T, size_t dimensions, size_t idx_dimensions>
class md_vector_index {
   public:
    md_vector_index(md_vector<T, dimensions>& vec, size_t base = 0) : vector_(vec), base_(base) {
    }

    auto operator[](size_t v) {
        assert(v < vector_.dsize_[idx_dimensions - 1]);
        return md_vector_index<T, dimensions, idx_dimensions + 1>(vector_, (base_ + v) * vector_.dsize_[idx_dimensions]);
    }

   private:
    md_vector<T, dimensions>& vector_;
    const size_t base_;
};

template <typename T, size_t dimensions>
class md_vector_index<T, dimensions, dimensions> {
   public:
    md_vector_index(md_vector<T, dimensions>& vec, size_t base = 0) : vector_(vec), base_(base) {
    }

    T& operator[](size_t v) {
        return vector_.data_[base_ + v];
    }

    md_vector<T, dimensions>& vector_;
    const size_t base_;
};

template <typename T, size_t dimensions, size_t idx_dimensions>
class const_md_vector_index {
   public:
    const_md_vector_index(const md_vector<T, dimensions>& vec, size_t base = 0) : vector_(vec), base_(base) {
    }

    auto operator[](size_t v) const {
        assert(v < vector_.dsize_[idx_dimensions - 1]);
        return const_md_vector_index<T, dimensions, idx_dimensions + 1>(vector_, (base_ + v) * vector_.dsize_[idx_dimensions]);
    }

   private:
    const md_vector<T, dimensions>& vector_;
    const size_t base_;
};

template <typename T, size_t dimensions>
class const_md_vector_index<T, dimensions, dimensions> {
   public:
    const_md_vector_index(const md_vector<T, dimensions>& vec, size_t base = 0) : vector_(vec), base_(base) {
    }

    const T& operator[](size_t v) const {
        return vector_.data_[base_ + v];
    }

    const md_vector<T, dimensions>& vector_;
    const size_t base_;
};
}  // namespace internal

template <typename T, size_t dimensions>
class md_vector {
   public:
    md_vector() {}
    md_vector(md_vector<T, dimensions>&& other) : data_(other.data_), dsize_(other.dsize_) {
    }
    md_vector(const md_vector<T, dimensions>& other) : data_(other.data_), dsize_(other.dsize_) {
    }

    md_vector(array<size_t, dimensions> dsize, T default_value = T())
        : dsize_(dsize), data_(internal::md_size(dsize), default_value) {
    }

    md_vector& operator=(md_vector<T, dimensions>&& other) {
        data_ = other.data_;
        dsize_ = other.dsize_;
        return *this;
    }
    md_vector& operator=(const md_vector<T, dimensions>& other) {
        data_ = other.data_;
        dsize_ = other.dsize_;
        return *this;
    }

    auto operator[](size_t v) {
        return internal::md_vector_index<T, dimensions, 1>(*this)[v];
    }

    const auto operator[](size_t v) const {
        return internal::const_md_vector_index<T, dimensions, 1>(*this)[v];
    }

    T& operator[](array<size_t, dimensions> idx) {
        size_t base = 0;
        for (int i = 0; i < dimensions; i++) {
            base *= dsize_[i];
            base += idx[i];
        }
        return data_[base];
    }

    vector<T> data_;
    array<size_t, dimensions> dsize_;
};

template <typename T, size_t dimensions>
istream& operator>>(istream& in, md_vector<T, dimensions>& vec) {
    return in >> vec.data_;
}

template <typename T, size_t dimensions>
void make_md_presum(md_vector<T, dimensions>& vec) {
    size_t diff = 1, base = 0;
    for (int currD = dimensions - 1; currD >= 0; currD--) {
        base = diff * vec.dsize_[currD];
        for (size_t i = 0; i + diff < vec.data_.size(); i++) {
            if (i % base + diff < base) {
                vec.data_[i + diff] += vec.data_[i];
            }
        }
        diff = base;
    }
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

    Matrix &operator*=(const Matrix &b) {
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

    Matrix operator+(const Matrix &b) const {
        return (Matrix(*this) += b);
    }

    Matrix operator-(const Matrix &b) {
        return (Matrix(*this) -= b);
    }
    Matrix operator*(const Matrix &b) const {
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
#line 4 "E3.cpp"

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

constexpr int md = 1e9 + 7;
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

void solve() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> score(2, vector<int>(m));
    Mint score1 = 0, score0 = 0;
    for (int i = 0; i < m; i++) {
        cin >> score[1][i];
        score1 += score[1][i];
    }
    for (int i = 0; i < m; i++) {
        cin >> score[0][i];
        score0 += score[0][i];
    }

    vector<Mint> val(4);
    for (int down = 0; down < 2; down++) {
        for (int up = 0; up < 2; up++) {
            int idx = down * 2 + up;
            Mint sum = 0;
            for (int j = 0; j < m; j++) {
                sum += Mint(score[down][j]) * score[up][j];
            }
            val[idx] = sum;
        }
    }
    if (n == 1) {
        Mint ans = Mint(score[0][0]) * score1 + Mint(score[1][0]) * (score0 + score1);
        cout << ans << endl;
        return;
    } else if (n == 2) {
        Mint ans = 0;
        for (int down = 0; down < 2; down++) {
            Mint tmp;
            if (down == 0) {
                tmp = score[1][0];
            } else {
                tmp = score[0][0] + score[1][0];
            }
            for (int up = 0; up < 2; up++) {
                Mint tmp2;
                if (up == 0) {
                    tmp2 = score1;
                } else {
                    tmp2 = score0 + score1;
                }
                ans += tmp * tmp2 * val[down * 2 + up];
            }
        }
        cout << ans << endl;
        return;
    }
    debug(val);

    Matrix<Mint> mat(4);

    for (int down1 = 0; down1 < 2; down1++) {
        for (int up1 = 0; up1 < 2; up1++) {
            int idx1 = down1 * 2 + up1;
            for (int down2 = 0; down2 < 2; down2++) {
                for (int up2 = 0; up2 < 2; up2++) {
                    int idx2 = down2 * 2 + up2;
                    if (up1 == 0 && down2 == 0) {
                        mat[idx1][idx2] = 0;
                    } else {
                        mat[idx1][idx2] = val[idx2];
                    }
                }
            }
        }
    }

    auto res = mat ^ (n - 2);

    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         cout << res[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    Mint ans = 0;
    for (int down1 = 0; down1 < 2; down1++) {
        for (int up1 = 0; up1 < 2; up1++) {
            int idx = down1 * 2 + up1;
            Mint tmp;
            if (down1 == 0) {
                tmp = score[1][0];
            } else {
                tmp = score[0][0] + score[1][0];
            }
            for (int down2 = 0; down2 < 2; down2++) {
                for (int up2 = 0; up2 < 2; up2++) {
                    int idx2 = down2 * 2 + up2;

                    Mint tmp2;
                    if (up2 == 0) {
                        tmp2 = score1;
                    } else {
                        tmp2 = score0 + score1;
                    }
                    Mint sub = tmp * val[idx] * tmp2 * res[idx][idx2];
                    debug(down1, up1, down2, up2, res[idx][idx2], tmp, tmp2, sub);
                    ans += sub;
                }
            }
        }
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}