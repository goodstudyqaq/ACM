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
        for (int sub = (status - 1) & status, ok = true; ok; ok = (sub != status)) {
            // do(sub)
            sub = (sub - 1) & status;
        }

        // 非空真子集
        for (int sub = (status - 1) & status; sub; sub = (sub - 1) & status) {
            // do(sub)
        }
    }
};