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

vector< int > w, fa;
vector< vector< int > > V;
typedef pair< int, int > pii;
priority_queue< pii > Q;
void dfs(int u, int d) {
    // debug(u, d);
    Q.push({d, u});
    for (auto v : V[u]) {
        dfs(v, d + 1);
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, L;
    long long S;
    cin >> n >> L >> S;
    w.resize(n + 1);
    fa.resize(n + 1);
    V.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        if (w[i] > S) {
            cout << -1 << endl;
            return 0;
        }
    }
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        V[fa[i]].push_back(i);
    }
    dfs(1, 1);

    int ans = 0;
    vector< bool > vis;
    vis.resize(n + 1);
    while (!Q.empty()) {
        auto u = Q.top();
        Q.pop();
        if (vis[u.second]) continue;
        vis[u.second] = true;
        ans++;
        int now_cnt = 1;
        long long now_val = w[u.second];
        int now = u.second;
        while (fa[now] != 0 && now_cnt + 1 <= L && now_val + w[fa[now]] <= S) {
            now_cnt++;
            now_val += w[fa[now]];
            now = fa[now];
            vis[now] = 1;
        }
    }
    cout << ans << endl;
    return 0;
}