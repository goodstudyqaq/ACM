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

const int maxn = 505;
bitset<maxn> dp[61][2][maxn];
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        dp[0][t][u][v] = 1;
    }

    for (int i = 1; i <= 60; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if (dp[i - 1][0][j][k]) dp[i][0][j] |= dp[i - 1][1][k];
                if (dp[i - 1][1][j][k]) dp[i][1][j] |= dp[i - 1][0][k];
            }
        }
    }

    if (dp[60][0][1].count() != 0) {
        cout << -1 << endl;
        return 0;
    }
    long long ans = 0;
    bitset<maxn> now;
    now[1] = 1;
    bool f = 0;
    for (int i = 59; i >= 0; i--) {
        bitset<maxn> go;
        for (int j = 1; j <= n; j++) {
            if (now[j]) {
                go = go | dp[i][f][j];
            }
        }
        if (go.count()) {
            ans += (1LL << i);
            now = go;
            f = f ^ 1;
        }
    }
    if (ans > 1e18) {
        ans = -1;
    }
    cout << ans << endl;
    return 0;
}