#include <bits/stdc++.h>
using namespace std;

void integer_chunk(int a) {
    /*
       求 a / i, i \in [1, a]
    */
    /*
    正着
    a / val 能求到一个上限 r， a / r = val 即最大的 r 使得 a / r = val
    */
    for (int i = 1; i <= a; i = (a / (a / i)) + 1) {
        int l = i, val = a / l;
        int r = a / val;
        // a / [l, r] 都等于 val
    }

    /*
    反着枚举
    大概的逻辑： a / i 能够得到当前的 val，而 val 也能理解成一个是得到 i 的最大的 r，即 val 是满足 a / val = i 的最大的值，那么 val + 1 是下一层的左端点，
    再进行一个 / 就能得到下一层的值，即也是能得到下一层的值的右端点。
    有点绕，估计面对这个问题的时候这个逻辑也是看不懂的。还是看下面的注释吧。
    */
    for (int i = a; i >= 1; i = (a / (a / i + 1))) {
        int r = i, val = a / r;
        int next_depth_r = a / (val + 1);
        int l = next_depth_r + 1;
        // a / [l, r] 都等于 val
    }
}
