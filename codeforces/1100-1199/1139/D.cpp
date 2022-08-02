#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast< int >(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template < size_t N >
string to_string(bitset< N > v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast< char >('0' + v[i]);
    }
    return res;
}

template < typename A >
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template < typename A, typename B >
string to_string(pair< A, B > p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

const int maxn = 1e5 + 1;
const int mod = 1e9 + 7;

bool check[maxn];
int prime[maxn];
int mu[maxn];

void Moblus() {
    mu[1] = 1;
    int tot = 0;
    for (int i = 2; i < maxn; i++) {
        if (!check[i]) {
            prime[tot++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < tot; j++) {
            if (i * prime[j] > maxn) break;
            check[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}
vector< int > factor[maxn];

void init() {
    for (int i = 1; i < maxn; i++) {
        for (int j = i; j < maxn; j += i) {
            factor[j].push_back(i);
        }
    }
}

int quick(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2)
            res = 1LL * res * a % mod;
        b /= 2;
        a = 1LL * a * a % mod;
    }
    return res;
}

vector< int > dp;

int m;
int get_num(int i, int k) {
    // j \in [1, m] 中 gcd(i, j) = k 的个数
    // 简化成  j \in [1, m / k] 中 gcd(i / k, j) = 1 的个数
    int LIMIT = m / k;
    i = i / k;

    // 枚举 i 的因子， 进行容斥
    int res = 0;
    for (auto it : factor[i]) {
        res += mu[it] * (LIMIT / it);
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    Moblus();
    cin >> m;
    int inv_m = quick(m, mod - 2);
    dp.resize(m + 1);
    dp[1] = 1;
    for (int i = 2; i <= m; i++) {
        // 首先枚举 i 的因子
        int tmp = 1;
        for (auto it : factor[i]) {
            if (it == i) continue;
            // 得到个数
            int num = get_num(i, it);
            tmp = (tmp + 1LL * dp[it] * num % mod * inv_m % mod) % mod;
        }
        // dp[i] 的个数
        int num = m / i;
        tmp = 1LL * tmp * m % mod * quick(m - num, mod - 2) % mod;
        dp[i] = tmp;
        // debug(i, dp[i]);
    }

    int res = 0;
    for (int i = 1; i <= m; i++) {
        res = (res + dp[i]) % mod;
    }
    res = 1LL * res * inv_m % mod;
    cout << res << endl;
    return 0;
}