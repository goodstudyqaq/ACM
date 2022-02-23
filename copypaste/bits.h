/*
    有关位运算的一些 copypaste
*/
#include <bits/stdc++.h>
using namespace std;
struct LoopCollection {
    /*
        lowbit(x): x 的最低位 1 lowbit(100100) = 100
        lowbit(x) = x & (~x + 1)
        ~x 按位取反 ~0 = -1, ~1 = -2, ~2 = -3...
        显然 ~x + 1 = -x
        所以 lowbit(x) = x & -x
    */

    void loopSet(vector< int > a) {
        // 遍历 {0, 1, ..., n - 1} 的所有子集
        int n = a.size();
        int limit = 1 << n;
        auto f = [&](int sub) {
            for (int i = 0; i < n; i++) {
                if ((sub >> i) & 1) {
                    // do(a[i])...
                }
            }
        };
        for (int i = 0; i < limit; i++) {
            f(i);
        }
    }
    void loopSubset(int n, int status) {
        // 枚举 status 的全部子集
        // 作为结束条件，处理完 0 之后，会有 -1&set == set
        for (int sub = status, ok = true; ok; ok = (sub != status)) {
            // do(sub)
            sub = (sub - 1) & status;
        }

        // 非空子集
        for (int sub = status; sub; sub = (sub - 1) & status) {
            // do(sub)
        }

        // 真子集
        for (int sub = (status - 1) & status; sub != status; sub = (sub - 1) & status) {
            // do(sub)
        }

        // 非空真子集
        for (int sub = (status - 1) & status; sub; sub = (sub - 1) & status) {
            // do(sub)
        }
    }
    void loopMultiSubset(vector< int >& a) {
        // 求多个集合(状压)的所有非空子集组成的集合
        // https://ac.nowcoder.com/acm/contest/7607/B
        vector< bool > have(1e6 + 1, 0);
        function< void(int v) > f = [&](int v) {
            if (have[v]) return;
            have[v] = true;
            for (int w = v; w > 0; w &= w - 1) {
                // w 每次会干掉 v 的最低位的 1
                // v = 1001010 => w = 1001010, 1001000, 1000000
                f(v ^ (w & -w));
            }
        };
    }

    void loopSuperset(int n, int status) {
        // 枚举 status 的全部超集(父集) ss
        for (int ss = status; ss < (1 << n); ss = (ss + 1) | status) {
            // do(ss)...
        }
    }

    // Gosper’s Hack：枚举大小为 n 的集合的大小为 k 的子集（按字典序）
    // https://en.wikipedia.org/wiki/Combinatorial_number_system#Applications
    // 参考《挑战程序设计竞赛》p.156-158 的实现
    // 把除法改成右移 bits.TrailingZeros 可以快好几倍
    // 比如在 n 个数中求满足某种性质的最大子集，则可以从 n 开始倒着枚举子集大小，直到找到一个符合性质的子集
    // 例题（TS1）https://codingcompetitions.withgoogle.com/codejam/round/0000000000007706/0000000000045875
    void loopSubsetK(vector< int >& a, int k) {
        int n = a.size();
        int limit = 1 << n;
        for (int sub = (1 << k) - 1; sub < limit;) {
            // do(a, sub)...
            int lb = sub & -sub;
            int x = sub + lb;
            /*
                x 有两种情况
                1. 最低位 1 前面没有 1，那么 x 就是我们想要找的下一位数 (x ^ sub) / lb = 11, 11 >> 2 = 0
                2. 最低位 1 前面有 1, 比如 100111000, x = 101000000 (x ^ sub) / lb = 1111 比还需要的多 2 个，所以还是左移 2
                本质就是把中间的 1 补上去，其实可以归成一类
            */
            sub = x + ((x ^ sub) >> (__builtin_ctz(lb) + 2));
        }
    }

    void loopAllOne(int status) {
        // 枚举各个 1 位的位置
        // 每次统计尾 0 的个数，然后移除最右侧的 1
        for (int i = status; i > 0; i &= (i - 1)) {
            int p = __builtin_ctz(i);
            // do(p)...
        }
    }
};