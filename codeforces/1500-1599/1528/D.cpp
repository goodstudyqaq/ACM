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
vector<vector<pii>> V;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    int n, m;
    cin >> n >> m;
    V.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        V[a].push_back({b, c});
    }

    vector<bool> vis(n + 1);
    vector<int> d(n + 1);
    const int inf = 0x3f3f3f3f;
    for (int idx = 0; idx < n; idx++) {
        V[n].clear();
        vis.clear();
        vis.resize(n + 1, 0);
        d.clear();
        d.resize(n + 1, inf);
        V[n] = V[idx];
        d[n] = 0;
        for (int i = 0; i <= n; i++) {
            int x, m = inf;
            for (int y = 0; y <= n; y++) {
                if (!vis[y] && d[y] <= m) m = d[x = y];
            }
            vis[x] = 1;
            for (auto it : V[x]) {
                d[(m + it.first) % n] = min(d[(m + it.first) % n], m + it.second);
            }
            if (x < n) {
                d[(x + 1) % n] = min(d[(x + 1) % n], m + 1);
            }
        }
        d[idx] = 0;
        for (int i = 0; i < n; i++) {
            cout << d[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}