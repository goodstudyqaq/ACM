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

vector< vector< int > > V;
vector< bool > vis;

vector< int > sz;
void dfs(int u, int pre) {
    if (vis[u]) sz[u] = 1;
    for (auto v : V[u]) {
        if (v == pre) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

int n, k;
int rt;
void dfs2(int u, int pre) {
    if (sz[u] > k) {
        for (auto v : V[u]) {
            if (v == pre) continue;
            if (sz[v] > k) {
                rt = v;
                dfs2(v, u);
                break;
            }
        }
    }
}

vector< int > V2;
void dfs3(int u, int pre) {
    if (vis[u]) {
        V2.push_back(u);
    }
    for (auto v : V[u]) {
        if (v == pre) continue;
        dfs3(v, u);
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    V.resize(n + 1);
    vis.resize(n + 1);
    sz.resize(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    for (int i = 1; i <= k * 2; i++) {
        int u;
        cin >> u;
        vis[u] = 1;
    }
    dfs(1, 0);
    rt = 1;
    dfs2(1, 0);
    debug(rt);

    cout << 1 << endl
         << rt << endl;
    dfs3(rt, 0);

    for (int i = 0; i < k; i++) {
        cout << V2[i] << ' ' << V2[i + k] << ' ' << rt << '\n';
    }
    return 0;
}