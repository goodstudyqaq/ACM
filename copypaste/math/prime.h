#include <bits/stdc++.h>
using namespace std;
namespace Prime {
//时间复杂度O(n)
const int maxn = 1e5 + 5;
bool is[maxn];
int prm[maxn], id;
// 每个数的最小质因子
int minp[maxn];
void get_prime() {
    /*
    数被筛掉的顺序：3 -> 3^2 -> 2*3^2 -> 2^2 * 3^2
    即从最大的质数去填
    */
    int k = 0;
    memset(is, 1, sizeof(is));
    is[0] = is[1] = 0;
    for (int i = 2; i < maxn; ++i) {
        if (is[i]) {
            prm[k++] = i;
            minp[i] = i;
        }
        for (int j = 0; j < k && (i * prm[j] < maxn); ++j) {
            is[i * prm[j]] = 0;
            minp[i * prm[j]] = prm[j];
            if (i % prm[j] == 0) break;
        }
    }
    id = k;
}
}  // namespace Prime
