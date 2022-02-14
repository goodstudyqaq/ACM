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

typedef pair< int, int > pii;
vector< pii > p;
vector< int > ans;
int n;

vector< int > head;

struct Edge {
    int to, next;
    int index, go_idx;
    bool flag;
};
vector< Edge > edges;
vector< int > du;
int tot;
void addedge(int u, int v, int idx) {
    edges[tot] = (Edge){v, head[u], 2 * idx - 1, 2 * idx, true};
    du[u]++;
    head[u] = tot++;
    edges[tot] = (Edge){u, head[v], 2 * idx, 2 * idx - 1, true};
    head[v] = tot++;
    du[v]++;
}

void dfs(int u) {
    debug(u);
    for (int& i = head[u]; ~i; i = edges[i].next) {
        auto e = edges[i];
        if (!e.flag) continue;
        int go = e.to;
        edges[i].flag = edges[i ^ 1].flag = false;
        dfs(go);
        ans.push_back(e.go_idx);
        ans.push_back(e.index);
    }
}

void init(int dig) {
    head.clear();
    head.resize(1 << dig, -1);
    du.clear();
    du.resize(1 << dig, 0);
    tot = 0;
    ans.clear();
}

bool check(int dig) {
    init(dig);
    for (int i = 1; i <= n; i++) {
        p[i].first %= (1 << dig);
        p[i].second %= (1 << dig);
        debug(i, p[i]);
        addedge(p[i].first, p[i].second, i);
    }
    int LIMIT = 1 << dig;
    for (int i = 0; i < LIMIT; i++) {
        if (du[i] % 2) return 0;
    }
    dfs(p[1].first);
    debug(ans.size());
    return ans.size() == 2 * n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    cin >> n;
    p.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i].first >> p[i].second;
    }
    edges.resize(1e6 + 5);
    for (int i = 20; i >= 0; i--) {
        if (check(i)) {
            cout << i << endl;
            for (auto it : ans) {
                cout << it << ' ';
            }
            cout << endl;
            return 0;
        }
    }
    return 0;
}
