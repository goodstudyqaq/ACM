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

vector<vector<int>> V;
vector<int> dep, fa;
void dfs(int u, int pre, int d) {
    dep[u] = d;
    fa[u] = pre;
    for (auto it : V[u]) {
        if (it == pre) continue;
        dfs(it, u, d + 1);
    }
}

int n;
bool check(int rt) {
    dfs(rt, 0, 0);
    vector<int> last_loc(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (i == rt) continue;
        int tmpd = dep[i];
        int sz = V[i].size();
        if (last_loc[tmpd] == -1) {
            last_loc[tmpd] = sz;
        } else if (last_loc[tmpd] != sz) {
            return 0;
        }
    }
    return 1;
}
int get_idx(int rt) {
    typedef pair<int, int> pii;
    queue<pii> Q;
    for (auto v : V[rt]) {
        Q.push({v, 0});
    }
    while (!Q.empty()) {
        auto it = Q.front();
        Q.pop();
        if (V[it.first].size() == 1) return it.first;
        if (V[it.first].size() > 2) continue;
        for (auto it2 : V[it.first]) {
            if (it2 == it.second) continue;
            Q.push({it2, it.first});
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    cin >> n;
    V.resize(n + 1);
    dep.resize(n + 1);
    fa.resize(n + 1);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    dfs(1, 0, 1);
    int chose_u = 1;
    for (int i = 1; i <= n; i++) {
        if (dep[i] > dep[chose_u]) {
            chose_u = i;
        }
    }
    dfs(chose_u, 0, 1);
    int chose_v = 1;
    for (int i = 1; i <= n; i++) {
        if (dep[i] > dep[chose_v]) {
            chose_v = i;
        }
    }

    vector<int> V2;
    int now = chose_v;
    while (now != chose_u) {
        V2.push_back(now);
        now = fa[now];
    }
    V2.push_back(chose_u);
    int rt = V2[V2.size() / 2];

    if (check(chose_u)) {
        cout << chose_u << endl;
        return 0;
    }
    if (check(chose_v)) {
        cout << chose_v << endl;
        return 0;
    }
    if (check(rt)) {
        cout << rt << endl;
        return 0;
    }
    int idx = get_idx(rt);
    if (idx != -1 && check(idx)) {
        cout << idx << endl;
        return 0;
    }
    cout << -1 << endl;
    return 0;
}