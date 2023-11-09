// http://oj.daimayuan.top/course/15/problem/637
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
    md_vector(md_vector<T, dimensions>& other) : data_(other.data_), dsize_(other.dsize_) {
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

template <typename T>
struct MDBIT {
#define lowbit(x) x & -x
    const int n, m;
    md_vector<T, 2> a;
    // [1, n]
    MDBIT(int n, int m) : n(n), m(m) {
        a = md_vector<T, 2>({n + 1, m + 1});
    }
    void add(int x, int y, T v) {
        for (int p = x; p <= n; p += lowbit(p)) {
            for (int q = y; q <= m; q += lowbit(q)) {
                a[p][q] += v;
            }
        }
    }

    // [1, x]
    T query(int x, int y) {
        T res = 0;

        for (int p = x; p > 0; p -= lowbit(p)) {
            for (int q = y; q > 0; q -= lowbit(q)) {
                res += a[p][q];
            }
        }
        return res;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, m, q;
    cin >> n >> m >> q;
    md_vector<long long, 2> a({n + 1, m + 1});
    MDBIT<long long> md_bit(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            md_bit.add(i, j, a[i][j]);
        }
    }
    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, y, d;
            cin >> x >> y >> d;
            md_bit.add(x, y, d - a[x][y]);
            a[x][y] = d;
        } else {
            int x, y;
            cin >> x >> y;
            cout << md_bit.query(x, y) << endl;
        }
    }
    return 0;
}