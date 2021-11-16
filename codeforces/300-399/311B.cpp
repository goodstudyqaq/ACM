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

vector< int > V;
vector< long long > pre_sum;
vector< vector< long long > > dp;

double getslope(int idx1, int idx2, int j) {
    double res = 1.0 * (dp[idx2][j] + pre_sum[idx2] - dp[idx1][j] - pre_sum[idx1]) / (1.0 * (idx2 - idx1));
    return res;
}

double getk(int idx) {
    return V[idx];
}
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, p;
    cin >> n >> m >> p;
    V.resize(m + 1);
    pre_sum.resize(m + 1);
    dp.resize(m + 1, vector< long long >(p + 1, 1e15));
    vector< int > d(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        cin >> d[i];
        d[i] += d[i - 1];
    }
    for (int i = 1; i <= m; i++) {
        int h, t;
        cin >> h >> t;
        int val = t - d[h];
        V[i] = val;
    }

    sort(V.begin() + 1, V.begin() + 1 + m);

    for (int i = 1; i <= m; i++) {
        pre_sum[i] = pre_sum[i - 1] + V[i];
        debug(i, V[i], pre_sum[i]);
    }
    vector< int > Q(m + 1);

    for (int j = 1; j <= p; j++) {
        int first = 0, tail = 0;
        Q[0] = 0;
        dp[0][j - 1] = 0;
        for (int i = 1; i <= m; i++) {
            while (first < tail && getslope(Q[first], Q[first + 1], j - 1) <= getk(i)) {
                first++;
            }
            dp[i][j] = dp[Q[first]][j - 1] + 1LL * (i - Q[first]) * V[i] - (pre_sum[i] - pre_sum[Q[first]]);
            while (first < tail && getslope(Q[tail], i, j - 1) <= getslope(Q[tail - 1], Q[tail], j - 1)) {
                tail--;
            }
            Q[++tail] = i;
            debug(i, j, dp[i][j]);
        }
    }
    cout << dp[m][p] << endl;
    return 0;
}