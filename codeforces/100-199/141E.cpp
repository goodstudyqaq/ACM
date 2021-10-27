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
typedef pair<pii, int> piii;
vector<piii> S, M;
vector<int> f;
int find(int u) {
    return u == f[u] ? u : f[u] = find(f[u]);
}
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        char t;
        cin >> u >> v >> t;
        if (t == 'S') {
            S.push_back({{u, v}, i});
        } else {
            M.push_back({{u, v}, i});
        }
    }

    if (n % 2 == 0) {
        cout << -1 << endl;
        return 0;
    }

    f.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        f[i] = i;
    }

    int s_sz = 0;
    for (auto it : S) {
        int u = it.first.first, v = it.first.second;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            f[fu] = fv;
            s_sz++;
        }
    }

    if (s_sz < (n - 1) / 2) {
        cout << -1 << endl;
        return 0;
    }

    int m_sz = 0;
    vector<bool> chose(m + 1, false);
    for (auto it : M) {
        int u = it.first.first, v = it.first.second;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            chose[it.second] = true;
            f[fu] = fv;
            m_sz++;
        }
    }
    if (s_sz + m_sz < (n - 1) / 2) {
        cout << -1 << endl;
        return 0;
    }

    for (int i = 1; i <= n; i++) f[i] = i;
    for (auto it : M) {
        int idx = it.second;
        if (chose[idx] == 0) continue;
        int u = it.first.first, v = it.first.second;
        int fu = find(u), fv = find(v);
        f[fu] = fv;
    }

    for (auto it : M) {
        if (m_sz == (n - 1) / 2) break;
        int idx = it.second;
        if (chose[idx]) continue;
        int u = it.first.first, v = it.first.second;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            f[fu] = fv;
            chose[idx] = true;
            m_sz++;
        }
    }
    if (m_sz != (n - 1) / 2) {
        cout << -1 << endl;
        return 0;
    }

    for (auto it : S) {
        int u = it.first.first, v = it.first.second;
        int fu = find(u), fv = find(v);
        if (fu != fv) {
            f[fu] = fv;
            chose[it.second] = true;
        }
    }

    cout << n - 1 << endl;
    for (int i = 1; i <= m; i++) {
        if (chose[i]) {
            cout << i << ' ';
        }
    }
    cout << endl;
    return 0;
}