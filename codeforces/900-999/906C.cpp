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

vector<int> pre, chose;

void dfs(int s) {
    if (s == -1) return;
    cout << chose[s] + 1 << ' ';
    dfs(pre[s]);
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        s[i] = 1 << i;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        s[u] |= (1 << v);
        s[v] |= (1 << u);
    }
    int LIMIT = 1 << n;
    const int inf = 1e9;
    vector<int> dp(LIMIT, inf);
    chose.resize(LIMIT);
    pre.resize(LIMIT, -1);

    bool f = true;
    for (int i = 0; i < n; i++) {
        if (s[i] != LIMIT - 1) {
            f = false;
            break;
        }
    }
    if (f) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[s[i]] = 1;
        chose[s[i]] = i;
    }
    for (int i = 1; i < LIMIT; i++)
        if (dp[i] != inf) {
            for (int j = 0; j < n; j++) {
                if ((i >> j) & 1 && dp[i | s[j]] > dp[i] + 1) {
                    dp[i | s[j]] = dp[i] + 1;
                    pre[i | s[j]] = i;
                    chose[i | s[j]] = j;
                }
            }
        }
    cout << dp[LIMIT - 1] << endl;
    dfs(LIMIT - 1);
    return 0;
}