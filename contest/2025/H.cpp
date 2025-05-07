#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

vector<Mint> fact(1);
vector<Mint> inv_fact(1);

Mint C(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    fact[0] = inv_fact[0] = 1;
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
    fact[0] = inv_fact[0] = 1;

    while ((int)fact.size() < n + 1) {
        fact.push_back(fact.back() * (int)fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[n - k];
}

const int maxn = 2e5 + 5;
using LL = Mint;
LL n, m, p, tree[maxn << 2], add[maxn << 2], mul[maxn << 2], a[maxn];
LL merge(int l, int r) {
    return (tree[l] + tree[r]);
}
void buildtree(int i, int l, int r) {
    mul[i] = 1, add[i] = 0;
    if (l == r) {
        tree[i] = a[l];
        return;
    }
    int mid = l + r >> 1;
    buildtree(i << 1, l, mid);
    buildtree(i << 1 | 1, mid + 1, r);
    tree[i] = merge(i << 1, i << 1 | 1);
}
void pushdown(int i, int l, int r) {
    int mid = l + r >> 1, ls = i << 1, rs = i << 1 | 1;
    tree[ls] = (tree[ls] * mul[i] + add[i] * (mid - l + 1));
    mul[ls] = (mul[ls] * mul[i]);
    add[ls] = (add[ls] * mul[i] + add[i]);
    tree[rs] = (tree[rs] * mul[i] + add[i] * (r - mid));
    mul[rs] = (mul[rs] * mul[i]);
    add[rs] = (add[rs] * mul[i] + add[i]);
    add[i] = 0, mul[i] = 1;
}
void update1(int i, int l, int r, int x, int y, Mint k) {
    if (l == x and r == y) {
        tree[i] = (tree[i] * k);
        mul[i] = (mul[i] * k);
        add[i] = (add[i] * k);
        return;
    }
    pushdown(i, l, r);
    int mid = l + r >> 1;
    if (y <= mid) {
        update1(i << 1, l, mid, x, y, k);
    } else {
        if (x > mid) {
            update1(i << 1 | 1, mid + 1, r, x, y, k);
        } else {
            update1(i << 1, l, mid, x, mid, k);
            update1(i << 1 | 1, mid + 1, r, mid + 1, y, k);
        }
    }
    tree[i] = merge(i << 1, i << 1 | 1);
}
void update2(int i, int l, int r, int x, int y, Mint k) {
    if (l == x and r == y) {
        tree[i] = (tree[i] + (r - l + 1) * k);
        add[i] = (add[i] + k);
        return;
    }
    pushdown(i, l, r);
    int mid = l + r >> 1;
    if (y <= mid) {
        update2(i << 1, l, mid, x, y, k);
    } else {
        if (x > mid) {
            update2(i << 1 | 1, mid + 1, r, x, y, k);
        } else {
            update2(i << 1, l, mid, x, mid, k);
            update2(i << 1 | 1, mid + 1, r, mid + 1, y, k);
        }
    }
    tree[i] = merge(i << 1, i << 1 | 1);
}
LL calc(int i, int l, int r, int x, int y) {
    if (l == x and r == y) {
        return tree[i];
    }
    pushdown(i, l, r);
    int mid = l + r >> 1;
    if (y <= mid) {
        return calc(i << 1, l, mid, x, y);
    } else {
        if (x > mid) {
            return calc(i << 1 | 1, mid + 1, r, x, y);
        } else {
            return (calc(i << 1, l, mid, x, mid) + calc(i << 1 | 1, mid + 1, r, mid + 1, y));
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    buildtree(1, 1, n);
    for (int i = 0; i < m; i++) {
        int l, r, x;
        cin >> l >> r >> x;

        int len = r - l + 1;
        Mint tmp = Mint(len - 1) / Mint(len);
        update1(1, 1, n, l, r, tmp);
        tmp = Mint(x) / Mint(len);
        update2(1, 1, n, l, r, tmp);
    }
    for (int i = 1; i <= n; i++) {
        cout << calc(1, 1, n, i, i) << ' ';
    }
    cout << endl;
}