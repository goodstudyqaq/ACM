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

const int maxn = 1e5 + 5;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
vector<piii> V[maxn];

int n, m;
int vis[maxn];
int del;
vector<int> del_edge;

bool dfs(int u, int val, bool write) {
    vis[u] = 1;
    for (auto e : V[u]) {
        int v = e.first.first;
        int w = e.first.second;
        if (w > val) {
            if (vis[v] == 0) {
                bool tmp = dfs(v, val, write);
                if (tmp) return true;
            } else if (vis[v] == 1) {
                return true;
            }
        } else {
            del++;
            if (write) {
                del_edge.push_back(e.second);
            }
        }
    }
    vis[u] = 2;
    return false;
}

bool check(int val, bool write) {
    for (int i = 1; i <= n; i++) {
        vis[i] = 0;
    }
    del = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            bool flag = dfs(i, val, write);
            if (flag) return false;
        }
    }
    return true;
}
int revtopu[maxn];

int topunum;
int main() {
    // freopen("data.in", "r", stdin);
    scanf("%d %d", &n, &m);
    int u, v, w;
    int mx = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        V[u].push_back({{v, w}, i});
        mx = max(mx, w);
    }
    int l = 0, r = mx;
    int ans = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid, false)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    vector<int> in(n + 5, 0);
    for (int i = 1; i <= n; i++) {
        for (auto e : V[i]) {
            if (e.first.second > ans) {
                in[e.first.first]++;
            }
        }
    }

    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) {
            Q.push(i);
        }
    }

    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        revtopu[x] = ++topunum;

        for (auto e : V[x]) {
            if (e.first.second > ans) {
                in[e.first.first]--;
                if (in[e.first.first] == 0) {
                    Q.push(e.first.first);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (auto e : V[i]) {
            if (e.first.second <= ans) {
                if (revtopu[i] > revtopu[e.first.first]) {
                    del_edge.push_back(e.second);
                }
            }
        }
    }
    printf("%d %d\n", ans, del_edge.size());
    for (auto v : del_edge) {
        printf("%d ", v);
    }
    puts("");
    return 0;
}