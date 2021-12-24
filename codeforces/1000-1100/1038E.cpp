#include <bits/stdc++.h>

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

const int maxn = 5;
const int maxm = 205;
struct Edge {
    int to, next;
    int index;
    int w;
    bool flag;
    Edge(int _t, int _n, int _idx, int _w, bool _f) : to(_t), next(_n), index(_idx), w(_w), flag(_f) {}
    Edge() {}
} edges[maxm];
int head[maxn], tot;

void init() {
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int w, int index) {
    edges[tot] = Edge(v, head[u], index, w, 0);
    head[u] = tot++;
    edges[tot] = Edge(u, head[v], index, w, 0);
    head[v] = tot++;
}
int du[maxn];
int ans;
vector<int> vis;
void dfs(int u) {
    vis[u] = 1;
    for (int i = head[u]; ~i; i = edges[i].next) {
        if (!edges[i].flag) {
            edges[i].flag = true;
            edges[i ^ 1].flag = true;
            ans += edges[i].w;
            dfs(edges[i].to);
        }
    }
}

void work1() {
    int res = 0;
    for (int i = 1; i <= 4; i++) {
        if (!vis[i]) {
            ans = 0;
            dfs(i);
            res = max(res, ans);
        }
    }
    cout << res << endl;
}

void work2() {
    int res = 0;
    for (int i = 1; i <= 4; i++) {
        if (du[i] % 2 && !vis[i]) {
            ans = 0;
            dfs(i);
            res = max(res, ans);
        }
    }
    cout << res << endl;
}

int n;

void init2() {
    for (int i = 1; i <= 4; i++) {
        vis[i] = 0;
    }
    for (int i = 0; i < tot; i++) {
        edges[i].flag = 0;
    }
}

void work3() {
    int res = 0;
    for (int i = 0; i < tot; i += 2) {
        int u = edges[i].to;
        int v = edges[i ^ 1].to;
        if (u == v)
            continue;
        edges[i].flag = 1;
        edges[i ^ 1].flag = 1;
        for (int j = 1; j <= 4; j++) {
            if (j != u && j != v && !vis[j]) {
                ans = 0;
                dfs(j);
                res = max(res, ans);
            }
        }

        init2();
    }
    cout << res << endl;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    cin >> n;
    vis.resize(5, 0);
    for (int i = 1; i <= n; i++) {
        int c1, v, c2;
        cin >> c1 >> v >> c2;
        addedge(c1, c2, v, i);
        du[c1]++;
        du[c2]++;
    }

    int odd_num = 0;
    for (int i = 1; i <= 4; i++) {
        if (du[i] % 2)
            odd_num++;
    }
    debug(odd_num);
    if (odd_num == 0) {
        work1();
    } else if (odd_num == 2) {
        work2();
    } else {
        work3();
    }
    return 0;
}