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
6. 格雷码：格雷码是一个二进制数系，其中两个相邻数的二进制位只有一位不同。举个例子， 3 位二进制数的格雷码序列为： 000， 001，011，010，110，111，101，100
    - https://oi-wiki.org/misc/gray-code/
    - 一维格雷码：int g(int n) { return n ^ (n >> 1); }
    - 二维格雷码：https://www.notion.so/F-Anti-Theft-Road-Planning-a249b965b47247fbb7390c297b7f0b3d
7. Lucas 定理：Lucas 定理用于求解大组合数取模的问题，其中模数必须为素数。正常的组合数运算可以通过递推公式求解（详见 排列组合），但当问题规模很大，而模数是一个不大的质数的时候，就不能简单地通过递推求解来得到答案，需要用到 Lucas 定理。
    - 也可以用于判断组合数的奇偶性
    - C(n, m) 当且仅当 m | n = n 时为奇数