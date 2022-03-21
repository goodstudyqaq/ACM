#include <bits/stdc++.h>
namespace Theorem {
/* 一些定理
1. [1, n] 能够被 n 整除的数的个数约为 n ^ (1/3) 个
2. [n / 2, n] 质数个数约为 m / (2 * log(n))
3. Π(x) ~ x / ln(x) Π(x) = [1, n] 素数个数
3. x = y 个连续的数的和的条件为
    1. y 是个奇数，那么只要 x % y = 0 即可
    2. y 是个偶数，那么和可以写成 2k + y / 2，所以 x 一定要是 y / 2 的奇数倍才可以，即 2x 是 y 的奇数倍
    设 x.b = x 的 2 的个数 x.l = 除 2 以外的因子的积那么有
    1. if y % 2 => x.l % y.l = 0
    2. else => x.l % y.l = 0 && x.b + 1 >= y.b 
*/

};  // namespace Theorem
namespace pcf {
// 求 [1, n] 素数个数
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define isprime(x) (((x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))

const int maxn = 100;      // pre-calc max n for phi(m, n)
const int maxm = 100010;   // pre-calc max m for phi(m, n)
const int maxp = 666666;   // max primes counter
const int max = 10000010;  // max prime

long long dp[maxn][maxm];
unsigned int ar[(max >> 6) + 5] = {0};
int len = 0, primes[maxp], counter[max];

void sieve() {
    setbit(ar, 0), setbit(ar, 1);
    for (int i = 3; (i * i) < max; i++, i++) {
        if (!chkbit(ar, i)) {
            int k = i << 1;
            for (int j = (i * i); j < max; j += k) setbit(ar, j);
        }
    }

    for (int i = 1; i < max; i++) {
        counter[i] = counter[i - 1];
        if (isprime(i)) primes[len++] = i, counter[i]++;
    }
}

void init() {
    sieve();
    for (int n = 0; n < maxn; n++) {
        for (int m = 0; m < maxm; m++) {
            if (!n)
                dp[n][m] = m;
            else
                dp[n][m] = dp[n - 1][m] - dp[n - 1][m / primes[n - 1]];
        }
    }
}

long long phi(long long m, int n) {
    if (n == 0) return m;
    if (primes[n - 1] >= m) return 1;
    if (m < maxm && n < maxn) return dp[n][m];
    return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
}

long long lehmer(long long m) {
    if (m < max) return counter[m];

    long long w, res = 0;
    int i, a, s, c, x, y;
    s = sqrt(0.9 + m), y = c = cbrt(0.9 + m);
    a = counter[y], res = phi(m, a) + a - 1;
    for (i = a; primes[i] <= s; i++) res = res - lehmer(m / primes[i]) + lehmer(primes[i]) - 1;
    return res;
}
long long solve(long long n) {
    int i, j, k, l;
    long long x, y, res = 0;

    for (i = 0; i < pcf::len; i++) {
        x = pcf::primes[i], y = n / x;
        if ((x * x) > n) break;
        res += (pcf::lehmer(y) - pcf::lehmer(x));
    }

    for (i = 0; i < pcf::len; i++) {
        x = pcf::primes[i];
        if ((x * x * x) > n) break;
        res++;
    }

    return res;
}
}  // namespace pcf

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