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
typedef pair<int, int> pii;

vector<int> id;
vector<vector<int>> V;
vector<vector<pii>> Q;

vector<set<int>> S;

vector<int> sz, dep, big, L, R, Node;
vector<int> ans;
int totdfn;
void dfs1(int u, int d) {
    L[u] = ++totdfn;
    Node[totdfn] = u;
    sz[u] = 1;
    dep[u] = d;
    int mx = -1;
    int mx_idx = -1;
    for (auto it : V[u]) {
        dfs1(it, d + 1);
        sz[u] += sz[it];
        if (sz[it] > mx) {
            mx = sz[it];
            mx_idx = it;
        }
    }
    if (mx_idx != -1) {
        big[u] = mx_idx;
    }
    R[u] = totdfn;
}
void add(int u, int dep) {
    S[dep].insert(u);
}

void dfs2(int u, bool keep) {
    // 1. 先遍历 u 的轻儿子，并计算答案，但不保留遍历后它对 cnt 数组的影响
    for (auto v : V[u]) {
        if (v != big[u]) {
            dfs2(v, false);
        }
    }

    // 2. 遍历它的重儿子，保留它对 cnt 数组的影响
    if (big[u]) {
        dfs2(big[u], true);
    }

    // 3. 考虑轻儿子的影响
    add(id[u], dep[u]);
    for (auto v : V[u]) {
        if (v != big[u]) {
            for (int i = L[v]; i <= R[v]; i++) {
                add(id[Node[i]], dep[Node[i]]);
            }
        }
    }

    for (auto q : Q[u]) {
        int v = q.first, idx = q.second;
        if (dep[u] + v >= S.size()) {
            ans[idx] = 0;
        } else {
            ans[idx] = S[dep[u] + v].size();
        }
    }
    if (keep == false) {
        for (int i = L[u]; i <= R[u]; i++) {
            S[dep[Node[i]]].erase(id[Node[i]]);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    id.resize(n + 1);
    V.resize(n + 1);
    Q.resize(n + 1);
    S.resize(n + 1);
    sz.resize(n + 1);
    dep.resize(n + 1);
    big.resize(n + 1, 0);
    L.resize(n + 1);
    R.resize(n + 1);
    Node.resize(n + 2);

    int rt = 0;
    map<string, int> M;
    int mcnt = 0;
    for (int i = 1; i <= n; i++) {
        string s;
        int father;
        cin >> s >> father;
        if (M.count(s)) {
            id[i] = M[s];
        } else {
            M[s] = ++mcnt;
            id[i] = M[s];
        }
        V[father].push_back(i);
    }

    int q;
    cin >> q;
    ans.resize(q + 1);
    for (int i = 1; i <= q; i++) {
        int v, k;
        cin >> v >> k;
        Q[v].push_back({k, i});
    }

    dfs1(0, 0);
    dfs2(0, false);
    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}