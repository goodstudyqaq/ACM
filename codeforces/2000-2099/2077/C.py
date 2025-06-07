# conv from https://judge.yosupo.jp/submission/41422
mod = 998244353
g = 3
ginv = 332748118
W = [pow(g, (mod - 1) >> i, mod) for i in range(24)]
Winv = [pow(ginv, (mod - 1) >> i, mod) for i in range(24)]
 
def fft(k, f):
    for l in range(k, 0, -1):
        d = 1 << l - 1
        U = [1]
        for i in range(d):
            U.append(U[-1] * W[l] % mod)
        for i in range(1 << k - l):
            for j in range(d):
                s = i * 2 * d + j
                f[s], f[s + d] = (f[s] + f[s + d]) % mod, U[j] * (f[s] - f[s + d]) % mod
 
 
def fftinv(k, f):
    for l in range(1, k + 1):
        d = 1 << l - 1
        for i in range(1 << k - l):
            u = 1
            for j in range(i * 2 * d, (i * 2 + 1) * d):
                f[j + d] *= u
                f[j], f[j + d] = (f[j] + f[j + d]) % mod, (f[j] - f[j + d]) % mod
                u *= Winv[l]
                u %= mod
 
 
def convolution(a, b):
    le = len(a) + len(b) - 1
    k = le.bit_length()
    n = 1 << k
    a = a + [0] * (n - len(a))
    b = b + [0] * (n - len(b))
    fft(k, a)
    fft(k, b)
    for i in range(n):
        a[i] *= b[i]
        a[i] %= mod
    fftinv(k, a)
 
    ninv = pow(n, mod - 2, mod)
    for i in range(le):
        a[i] *= ninv
        a[i] %= mod
 
    return a[:le]
 
 
fac_arr = [1]
finv_arr = [1]
 
 
def enlarge_fac():
    old_size = len(fac_arr)
    new_size = old_size * 2
    for i in range(old_size, new_size + 1):
        fac_arr.append((fac_arr[-1] * i) % mod)
        finv_arr.append(pow(fac_arr[-1], -1, mod))
 
 
def fac(n):
    while n >= len(fac_arr): enlarge_fac()
    return fac_arr[n]
 
 
def finv(n):
    while n >= len(finv_arr): enlarge_fac()
    return finv_arr[n]
 
 
def binom(n, k):
    if k < 0 or k > n: return 0
    return ((fac(n) * finv(k)) % mod * finv(n - k)) % mod
 
import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n, q = map(int, input().split())
    s = list(map(int, list(input()[:-1])))
    binomial = [binom(n, i) for i in range(n + 1)]
    A = [(i // 2) * ((i + 1) // 2) % mod for i in range(n + 1)]
    lookup = convolution(A, binomial)
    ones = sum(s)
    for _ in range(q):
        a = int(input()) - 1
        ones += 1 - 2 * s[a]
        s[a] = 1 - s[a]
        print((lookup[ones] + lookup[n - ones]) % mod)
        
# model solution, fft