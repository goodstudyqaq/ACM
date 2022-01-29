#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
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

const int mod = 1e9 + 7;
int quick(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2) res = 1LL * res * a % mod;
        b /= 2;
        a = 1LL * a * a % mod;
    }
    return res;
}

vector< int > A, B;
void init(int n) {
    A.resize(n + 1);
    B.resize(n + 1);
    A[0] = 1;
    for (int i = 1; i <= n; i++) {
        A[i] = 1LL * A[i - 1] * i % mod;
    }
    B[n] = quick(A[n], mod - 2);
    for (int i = n - 1; i >= 0; i--) {
        B[i] = 1LL * B[i + 1] * (i + 1) % mod;
    }
}

int C(int n, int m) {
    if (n < m) return 0;
    if (m < 0) return 0;
    debug(n, m);
    return 1LL * A[n] * B[m] % mod * B[n - m] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    init(1e6);
    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;

        if (n == m) {
            cout << 1LL * n * k % mod << endl;
            continue;
        }

        int tmp_two = quick(2, n - 1);
        int inv_two = quick(tmp_two, mod - 2);
        int res = 0;
        for (int i = 1; i < n; i++) {
            // 计算 (i, j) 到 (n, m) 的贡献
            int tmp = C(n - i - 1, m - i);
            if (tmp == 0) {
                continue;
            }
            tmp = 1LL * tmp * inv_two % mod * i % mod * k % mod;
            res = (res + tmp) % mod;
            inv_two = 1LL * inv_two * 2 % mod;
        }
        cout << res << '\n';
    }
    return 0;
}
