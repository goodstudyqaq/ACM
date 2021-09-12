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

vector<int> black;
vector<vector<int>> V;

struct Node {
    int idx;
    int up, down;
    bool operator<(const Node& b) const {
        if (1LL * up * b.down != 1LL * down * b.up)
            return 1LL * up * b.down < 1LL * down * b.up;
        return idx < b.idx;
    }
};

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    int n, m, k;
    cin >> n >> m >> k;
    black.resize(n + 1, 0);
    V.resize(n + 1);
    for (int i = 1; i <= k; i++) {
        int u;
        cin >> u;
        black[u] = 1;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    set<Node> now, ans;
    int ans_up = -1, ans_down = 1;
    vector<Node> nodes(n + 1);

    for (int i = 1; i <= n; i++) {
        if (black[i]) continue;
        int all = V[i].size();
        int white = 0;
        for (auto v : V[i]) {
            if (black[v]) continue;
            white++;
        }
        nodes[i] = (Node){i, white, all};
        now.insert(nodes[i]);
    }
    while (!now.empty()) {
        auto it = now.begin();
        if (1LL * ans_up * it->down < 1LL * ans_down * it->up) {
            ans_up = it->up;
            ans_down = it->down;
            ans = now;
        }
        int idx = it->idx;

        now.erase(it);
        for (auto v : V[idx]) {
            if (black[v]) continue;
            if (now.count(nodes[v])) {
                now.erase(nodes[v]);
                nodes[v].up--;
                now.insert(nodes[v]);
            }
        }
    }
    debug(ans_up, ans_down);
    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it.idx << ' ';
    }
    cout << endl;
    return 0;
}