#line 1 "3865.cpp"
#include <bits/stdc++.h>

#line 2 "/Users/guoshen/code/library2/structure/others/linear-sparse-table.hpp"

#line 2 "/Users/guoshen/code/library2/structure/others/sparse-table.hpp"
using namespace std;

/* 幂等半群的区间查询, 
1. fold 查询 [l, r) 的值

需要补充一些二分函数，O(log) 找到值
*/
// F = function<int(int, int)>
template <typename T, typename F>
struct SparseTable {
    F f;
    vector<vector<T> > st;
    vector<int> lookup;

    SparseTable() = default;

    explicit SparseTable(const vector<T> &v, const F &f) : f(f) {
        const int n = (int)v.size();
        const int b = 32 - __builtin_clz(n);
        st.assign(b, vector<T>(n));
        for (int i = 0; i < v.size(); i++) {
            st[0][i] = v[i];
        }
        for (int i = 1; i < b; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
        lookup.resize(v.size() + 1);
        for (int i = 2; i < lookup.size(); i++) {
            lookup[i] = lookup[i >> 1] + 1;
        }
    }

    inline T fold(int l, int r) const {
        int b = lookup[r - l];
        return f(st[b][l], st[b][r - (1 << b)]);
    }
};

template <typename T, typename F>
SparseTable<T, F> get_sparse_table(const vector<T> &v, const F &f) {
    return SparseTable<T, F>(v, f);
}
#line 4 "/Users/guoshen/code/library2/structure/others/linear-sparse-table.hpp"
using namespace std;
/*
基于状压的线性 RMQ 算法
线性算法:
块大小为 w, 在 Word-RAM 模型中 w = Ω(logn), w 位整数
位运算复杂度为 O(1). n n 对于块的结果形成的序列, 使用稀疏表, 由于 w log w ≤ n 这 部分复杂度为 O(n). 对每个块计算块内前缀最小值和后缀最小值, 这部分复杂 度为 O(n).
对每个块在块内计算每个单调栈的二进制表示, 通过位运算 可以使得计算单调栈均摊复杂度和询问复杂的都是 O(1). 复杂度为 O(n) − O(1)

https://www.luogu.com.cn/problem/P3793

 */

template <typename T, typename F>
struct LinearSparseTable {
    F f;
    vector<T> V;
    vector<T> newV;
    vector<T> pre_max, suf_max;
    // md_vector<T, 2> pre_max, suf_max;
    map<int, int> two;
    int w;
    vector<int> statues;
    SparseTable<T, F> st;

    LinearSparseTable() = default;

    explicit LinearSparseTable(const vector<T> &v, const F &f, const int _w = 30) : V(v), f(f), w(_w) {
        int n = v.size();
        int block_num = (n + w - 1) / w;
        newV = vector<T>(block_num);
        for (int i = 0; i < block_num; i++) {
            int l = i * w;
            int r = min(i * w + w, n);
            newV[i] = v[l];
            for (int j = l; j < r; j++) {
                newV[i] = f(newV[i], v[j]);
            }
        }

        // 对 newV 做稀疏表
        st = SparseTable<T, F>(newV, f);

        // 对每个块求前缀最大值和后缀最大值
        pre_max = vector<T>(n);
        suf_max = vector<T>(n);
        for (int i = 0; i < n; i++) {
            if (i % w == 0) {
                pre_max[i] = v[i];
            } else {
                pre_max[i] = f(v[i], pre_max[i - 1]);
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1 || (i % w) == w - 1) {
                suf_max[i] = v[i];
            } else {
                suf_max[i] = f(v[i], suf_max[i + 1]);
            }
        }

        // 对每个块用单调栈作状压
        statues = vector<int>(n);
        vector<int> stk;
        int status = 0;
        for (int i = 0; i < n; i++) {
            if (i % w == 0) {
                stk.clear();
                status = 0;
            }
            while (stk.size() && v[stk.back()] <= v[i]) {
                status -= (1 << (stk.back() % w));
                stk.pop_back();
            }
            stk.push_back(i);
            status += (1 << (i % w));
            statues[i] = status;
        }
        int now = 1;
        for (int i = 0; i < w; i++) {
            two[now] = i;
            now *= 2;
        }
    }

    inline T fold(int l, int r) const {
        auto lowbit = [&](int x) {
            return x & -x;
        };
        // [l, r)
        r--;
        assert(l <= r);
        int b1 = l / w;
        int b2 = r / w;
        if (b1 == b2) {
            int s = statues[r];
            s = s >> (l % w);
            s = s << (l % w);
            int _low = lowbit(s);
            int idx = two.at(_low);
            return V[idx + b1 * w];
        } else {
            // b1 后缀, b2 前缀
            T res = f(suf_max[l], pre_max[r]);

            if (b1 + 1 <= b2 - 1) {
                res = f(res, st.fold(b1 + 1, b2));
            }
            return res;
        }
    }
};
#line 4 "3865.cpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, m;
    cin >> n >> m;
    vector<int> V(n);
    for (int i = 0; i < n; i++) {
        // cin >> V[i];
        V[i] = read();
    }
    using F = function<int(int, int)>;
    LinearSparseTable<int, F> lst(V, [&](int x, int y) {
        return x > y ? x : y;
    });

    while (m--) {
        int l = read();
        int r = read();
        l--, r--;
        printf("%d\n", lst.fold(l, r + 1));
        // cout << lst.fold(l, r + 1) << endl;
    }
    return 0;
}
