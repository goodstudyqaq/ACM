# Math
## 一些定理
1. [1, n] 能够被 n 整除的数的个数约为 n ^ (1/3) 个
2. [n / 2, n] 质数个数约为 m / (2 * log(n))
3. Π(x) ~ x / ln(x) Π(x) = [1, n] 素数个数
3. x = y 个连续的数的和的条件为
    1. y 是个奇数，那么只要 x % y = 0 即可
    2. y 是个偶数，那么和可以写成 2k + y / 2，所以 x 一定要是 y / 2 的奇数倍才可以，即 2x 是 y 的奇数倍
    设 x.b = x 的 2 的个数 x.l = 除 2 以外的因子的积那么有
    1. if y % 2 => x.l % y.l = 0
    2. else => x.l % y.l = 0 && x.b + 1 >= y.b 
4. |i−i′|+|j−j′|≤k⇔max(|(i+j)−(i′+j′)|,|(i−j)−(i′−j′)|)≤k
5. 一个环上选边使得覆盖所有点的方案数为 lucas 数。
    - https://atcoder.jp/contests/abc247/tasks/abc247_f
    - https://en.wikipedia.org/wiki/Lucas_number
    - f[0] = 2, f[1] = 1, f[n] = f[n - 1] + f[n - 2]