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
const int maxn = 2e5 + 5;
pii edges[maxn];

set<int> V[maxn];

set<int> S;
int n, m, k;
void work(int u) {
    S.erase(u);
    for (auto v : V[u]) {
        V[v].erase(u);
        if (V[v].size() < k && S.count(v)) {
            work(v);
        }
    }
}
int ans[maxn];

int main() {
    // freopen("data.in", "r", stdin);
    scanf("%d %d %d", &n, &m, &k);
    int u, v;
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &u, &v);
        edges[i] = {u, v};
        V[u].insert(v);
        V[v].insert(u);
    }
    for (int i = 1; i <= n; i++) {
        S.insert(i);
    }

    for (int v = 1; v <= n; v++) {
        if (V[v].size() < k && S.count(v)) {
            work(v);
        }
    }

    for (int i = m; i >= 1; i--) {
        ans[i] = S.size();
        pii tmp = edges[i];
        V[tmp.first].erase(tmp.second);
        V[tmp.second].erase(tmp.first);

        if (S.count(tmp.first) && V[tmp.first].size() < k) {
            work(tmp.first);
        }
        if (S.count(tmp.second) && V[tmp.second].size() < k) {
            work(tmp.second);
        }
    }
    for (int i = 1; i <= m; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}