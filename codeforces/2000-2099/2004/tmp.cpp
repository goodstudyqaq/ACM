#line 1 "G.cpp"
#include <bits/stdc++.h>

#line 4 "G.cpp"

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

    md_vector& operator=(const md_vector<T, dimensions>& other) {
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
#line 6 "G.cpp"

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

typedef md_vector<int, 2> mat;

template <typename T>
struct MinQueue {
    vector<pair<T, T>> st1, st2;
    // 注意顺序
    function<T(T&, T&, bool)> f;

    MinQueue() = default;

    MinQueue(function<T(T&, T&, bool)> &f) : f(f) {}

    void push(T &a) {
        if (!st1.empty()) {
            st1.push_back({a, f(st1.back().second, a, 1)});
        } else {
            st1.push_back({a, a});
        }
    }

    void pop() {
        if (st2.empty()) {
            st2 = st1;
            reverse(st2.begin(), st2.end());
            st1.clear();

            st2[0].second = st2[0].first;
            for (int i = 1; i < st2.size(); i++) {
                st2[i].second = f(st2[i].first, st2[i - 1].second, 0);
            }
        }
        st2.pop_back();
    }

    T get() {
        if (st1.empty()) {
            return st2.back().second;
        }
        if (st2.empty()) {
            return st1.back().second;
        }

        T res = f(st2.back().second, st1.back().second, 0);
        return res;
    }
};
void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
    }

    const int inf = numeric_limits<int>::max() / 2;
    vector<md_vector<int, 2>> transfer(10, md_vector<int, 2>({10, 10}, inf));

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            transfer[i][j][0] = j;
            transfer[i][j][j] = j;
        }
        transfer[i][0][i] = 0;
    }
    function<mat(mat&, mat&, bool)> mul = [&](mat& a, mat& b, bool fl) {
        const int inf = numeric_limits<int>::max() / 2;
        mat c({10, 10}, inf);
        if (fl) {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    c[j][i] = min({c[j][i], a[j][0] + b[0][i], a[j][i] + b[i][i]});
                    c[j][0] = min(c[j][0], a[j][i] + b[i][0]);
                }
            }
        } else {
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    c[i][j] = min({c[i][j], a[i][0] + b[0][j], a[i][i] + b[i][j]});
                    c[0][j] = min(c[0][j], a[0][i] + b[i][j]);
                }
            }
        }
        return c;
    };

    MinQueue<mat> mq(mul);
    for (int i = 0; i < n; i++) {
        mq.push(transfer[a[i]]);
        if (i >= k - 1) {
            cout << mq.get()[0][0] << ' ';
        }
        if (i >= k - 1) {
            mq.pop();
        }
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
