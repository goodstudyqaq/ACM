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
    return 1LL * A[n] * B[m] % mod * B[n - m] % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    int n;
    long long T;
    cin >> n >> T;
    init(n);
    vector< long long > sumt;
    sumt.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> sumt[i];
        sumt[i] += sumt[i - 1];
    }

    int now_n = 0, now_m = 0;
    int now_val = 1;
    int two = 1;
    int inv_two = quick(2, mod - 2);
    int res = 0;
    for (int i = 1; i <= n; i++) {
        long long tmp = T - sumt[i];
        two = 1LL * two * inv_two % mod;
        if (tmp < 0) break;
        tmp = min(tmp, 1LL * i);
        //从 (now_n, now_m) 变成 (i, tmp);
        now_val = (1LL * now_val * 2 % mod - C(now_n, now_m)) % mod;
        now_n++;
        if (now_m < tmp) {
            while (now_m < tmp) {
                now_m++;
                now_val = (now_val + C(now_n, now_m)) % mod;
            }
        }
        if (now_m > tmp) {
            while (now_m > tmp) {
                now_val = (now_val - C(now_n, now_m)) % mod;
                now_m--;
            }
        }
        debug(i, now_val, res);
        res = (res + 1LL * now_val * two % mod) % mod;
    }
    res = (res + mod) % mod;
    cout << res << endl;
    return 0;
}
