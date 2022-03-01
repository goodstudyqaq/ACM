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

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
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

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
const int inf = 105;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    int n, k;
    cin >> n >> k;
    vector<int> l, r;
    l.resize(k + 1);
    r.resize(k + 1);
    for (int i = 1; i <= k; i++) {
        cin >> l[i] >> r[i];
    }
    deque<int> Q1;
    vector<vector<int> > dp(2, vector<int>(2 * n + 1, inf));
    dp[0][0] = 0;
    for (int i = 1; i <= k; i++) {
        int f = i % 2;
        for (int j = 0; j <= 2 * n; j++) dp[f][j] = dp[f ^ 1][j];
        Q1.clear();
        for (int j = 0; j <= r[i]; j++) {
            while (Q1.size() && Q1.front() < j - r[i] + l[i]) Q1.pop_front();
            while (Q1.size() && dp[f ^ 1][j] < dp[f ^ 1][Q1.back()]) Q1.pop_back();
            Q1.push_back(j);
            dp[f][j] = min(dp[f][j], dp[f ^ 1][Q1.front()] + 2);
        }
        Q1.clear();
        for (int j = r[i]; j >= 0; j--) {
            while (Q1.size() && Q1.front() < l[i] - j) Q1.pop_front();
            while (Q1.size() && dp[f ^ 1][r[i] - j] < dp[f ^ 1][Q1.back()]) Q1.pop_back();
            Q1.push_back(r[i] - j);
            dp[f][j] = min(dp[f][j], dp[f ^ 1][Q1.front()] + 1);
        }
        debug(dp[f]);
    }
    if (dp[k % 2][n] != inf) {
        cout << "Full" << endl;
        cout << dp[k % 2][n] << endl;
    } else {
        cout << "Hungry" << endl;
    }
    return 0;
}