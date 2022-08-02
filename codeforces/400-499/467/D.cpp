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
vector<int> DFN, LOW, vis;
int id;
vector<int> belong;
int cnt;
vector<int> stk;
int tot1;
vector<int> r_num, s_sz;
vector<int> mi_rnum, mi_sz;

void tarjan(int u) {
    DFN[u] = LOW[u] = ++id;
    stk[tot1++] = u;
    vis[u] = 1;
    for (auto v : V[u]) {
        if (!DFN[v]) {
            tarjan(v);
            LOW[u] = min(LOW[u], LOW[v]);
        } else if (vis[v]) {
            LOW[u] = min(LOW[u], DFN[v]);
        }
    }
    if (LOW[u] == DFN[u]) {
        cnt++;
        int v;
        do {
            v = stk[tot1 - 1];
            vis[v] = 0;
            belong[v] = cnt;
            if (mi_rnum[cnt] > r_num[v]) {
                mi_rnum[cnt] = r_num[v];
                mi_sz[cnt] = s_sz[v];
            } else if (mi_rnum[cnt] == r_num[v] && mi_sz[cnt] > s_sz[v]) {
                mi_sz[cnt] = s_sz[v];
            }
            tot1--;
        } while (v != u);
    }
}

void cal(string& s, int idx) {
    int rnum = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'r') {
            rnum++;
        }
    }
    r_num[idx] = rnum;
    s_sz[idx] = s.size();
}

vector<vector<int>> V2;
vector<int> vis2;

void dfs(int u) {
    debug(u);
    vis2[u] = 1;
    for (auto v : V2[u]) {
        dfs(v);
        if (mi_rnum[u] > mi_rnum[v]) {
            mi_rnum[u] = mi_rnum[v];
            mi_sz[u] = mi_sz[v];
        } else if (mi_rnum[u] == mi_rnum[v] && mi_sz[u] > mi_sz[v]) {
            mi_sz[u] = mi_sz[v];
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
    vector<string> s;
    s.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        for (int j = 0; j < s[i].size(); j++) {
            if (s[i][j] >= 'A' && s[i][j] <= 'Z') {
                s[i][j] = s[i][j] - 'A' + 'a';
            }
        }
    }

    int m;
    cin >> m;
    vector<pair<string, string>> q;
    q.resize(m + 1);

    map<string, int> M;
    int m_cnt = 0;
    for (int i = 1; i <= m; i++) {
        string a, b;
        cin >> a >> b;
        for (int j = 0; j < a.size(); j++) {
            if (a[j] >= 'A' && a[j] <= 'Z') {
                a[j] = a[j] - 'A' + 'a';
            }
        }
        for (int j = 0; j < b.size(); j++) {
            if (b[j] >= 'A' && b[j] <= 'Z') {
                b[j] = b[j] - 'A' + 'a';
            }
        }
        q[i] = {a, b};
        if (!M.count(a)) {
            M[a] = ++m_cnt;
        }
        if (!M.count(b)) {
            M[b] = ++m_cnt;
        }
    }
    V.resize(m_cnt + 1);
    r_num.resize(m_cnt + 1);
    s_sz.resize(m_cnt + 1);
    for (int i = 1; i <= m; i++) {
        string a = q[i].first, b = q[i].second;
        int a_idx = M[a];
        int b_idx = M[b];
        V[a_idx].push_back(b_idx);
        cal(a, a_idx);
        cal(b, b_idx);
    }

    DFN.resize(m_cnt + 1, 0);
    LOW.resize(m_cnt + 1);
    vis.resize(m_cnt + 1, 0);
    belong.resize(m_cnt + 1);
    stk.resize(m_cnt + 1);
    mi_rnum.resize(m_cnt + 1, 5e5 + 10);
    mi_sz.resize(m_cnt + 1);

    for (int i = 1; i <= m_cnt; i++) {
        if (DFN[i] == 0) {
            id = 0;
            tarjan(i);
        }
    }

    // 缩点
    V2.resize(m_cnt + 1);
    vis2.resize(m_cnt + 1, 0);
    for (int i = 1; i <= m_cnt; i++) {
        int u = belong[i];
        for (auto j : V[i]) {
            int v = belong[j];
            if (u != v)
                V2[u].push_back(v);
        }
    }

    for (int i = 1; i <= cnt; i++) {
        if (vis2[i] == 0) {
            debug(i);
            dfs(i);
        }
    }
    long long r_ans = 0, sz_ans = 0;

    for (int i = 1; i <= n; i++) {
        debug(s[i], M.count(s[i]));
        if (!M.count(s[i])) {
            sz_ans += s[i].size();
            for (int j = 0; j < s[i].size(); j++) {
                if (s[i][j] == 'r') r_ans++;
            }
        } else {
            int idx = M[s[i]];
            idx = belong[idx];
            r_ans += mi_rnum[idx];
            sz_ans += mi_sz[idx];
        }
    }
    cout << r_ans << ' ' << sz_ans << endl;
    return 0;
}