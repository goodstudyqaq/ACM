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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    const int mod = 1e9 + 7;
    int n, m;
    cin >> n >> m;

    vector< vector< int > > dp;
    vector< vector< int > > sum1, sum2;
    dp.resize(n + 1, vector< int >(m + 1));
    sum1.resize(n + 1, vector< int >(m + 1));
    sum2.resize(n + 1, vector< int >(m + 1));
    for (int i = 2; i <= m; i++) {
        dp[1][i] = 1;
        sum1[1][i] = (sum1[1][i - 1] + dp[1][i]) % mod;
        sum2[1][i] = (sum2[1][i - 1] + sum1[1][i]) % mod;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            dp[i][j] = sum2[i - 1][j];
            sum1[i][j] = (sum1[i][j - 1] + dp[i][j]) % mod;
            sum2[i][j] = (sum2[i][j - 1] + sum1[i][j]) % mod;
        }
    }
    for (int i = 1; i <= m; i++) sum2[0][i] = 1;
    debug(sum2);
    debug(dp);
    int res = 0;
    for (int w = 2; w <= m; w++) {
        int f1 = m + 1 - w;
        int tmp1 = 0, tmp2 = 0;
        for (int i = n; i >= 1; i--) {
            int f3 = dp[i][w];
            int other = n - i;
            tmp1 = (tmp1 + (sum2[other][w] - dp[other][w]) % mod) % mod;
            (tmp2 += tmp1) %= mod;
            int val = 1LL * f1 * f3 % mod * tmp2 % mod;
            debug(w, i, val, f1, f3, tmp2);
            (res += val) %= mod;
        }
    }
    res = (res + mod) % mod;
    cout << res << endl;
}
