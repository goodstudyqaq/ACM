/*
现在有m个set，set里的结点两两相连，边的权值告诉你了，另外边有颜色，的边的颜色等于当前set的下标。
如果有一个环上的边的颜色存在多种，那么是不合法的。求删掉若干个变，使得当前图是合法的。
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
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
const int maxn = 1e5 + 5;
const int maxm = 2e5 + 5;
int a[maxn], b[maxn];
int f[maxn * 2];

int find(int u) {
    return f[u] == u ? f[u] : f[u] = find(f[u]);
}

struct Edge {
    int u, v, w;
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
    Edge() {}
    bool operator<(const Edge& e) const {
        return w > e.w;
    }
} edges[maxm];
int ecnt;
int main() {
    // freopen("data.in", "r", stdin);
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
    }

    for (int i = 1; i <= n + m; i++) {
        f[i] = i;
    }

    long long sum = 0;
    for (int i = 1; i <= m; i++) {
        int k, s;
        scanf("%d", &k);
        for (int j = 1; j <= k; j++) {
            scanf("%d", &s);
            edges[++ecnt] = Edge(s, n + i, a[i] + b[s]);
            debug(i, s, a[i] + b[s]);
            sum = sum + 1LL * a[i] + 1LL * b[s];
        }
    }

    sort(edges + 1, edges + 1 + ecnt);
    long long sum2 = 0;
    for (int i = 1; i <= ecnt; i++) {
        Edge& e = edges[i];
        int u = e.u;
        int v = e.v;
        int w = e.w;
        debug(u, v, w);
        int fu = find(u);
        int fv = find(v);
        if (fu != fv) {
            sum2 = sum2 + 1LL * w;
            f[fu] = fv;
        }
    }
    debug(sum, sum2);
    cout << sum - sum2 << endl;
}