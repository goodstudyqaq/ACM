/*
https://atcoder.jp/contests/abc246/tasks/abc246_h
1. 01 字符串的子序列个数可以用 dp 来做 $dp[i][0/1]$ 表示到 i 位置，以 0 / 1 结尾的子序列个数，那么有：
    1. 当 $s[i] = 0$ 时
        1. $dp[i][0] = dp[i - 1][0] + dp[i - 1][1] + 1$
        2. $dp[i][1] = dp[i  -1][1]$
    2. If $s[i] = 1$
        1. $dp[i][0] = dp[i - 1][0]$
        2. $dp[i][1] = dp[i - 1][0] + dp[i - 1][1] + 1$
    3. if $s[i] = ?$
        1. $dp[i][0] = dp[i - 1][0] + dp[i - 1][1] + 1$
        2. $dp[i][1] = dp[i - 1][0] + dp[i - 1][1] + 1$

https://atcoder.jp/contests/abc247/tasks/abc247_f
2. 一条线上选边覆盖所有点的方案数为 F(N) = F(N - 1) + F(N - 2) F(1) = 2 F(2) = 3 
3. 环上选边覆盖所有点的方案数为 g(1) = 1, g(2) = 3, g(3) = 4, g(N) = F(N - 1) + F(N - 3) g 是 lucas 数，也可以写成 L[0] = 2 L[1] = 1 L[n] = L[n - 1] + L[n - 2]
*/