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

const int mod = 998244353;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
vector<vector<piii>> V;

const int maxn = 2e5 + 5;
//时间复杂度O(n)
bool is[maxn];
int prm[maxn], id;
void init() {
    int k = 0;
    memset(is, 1, sizeof(is));
    is[0] = is[1] = 0;
    for (int i = 2; i < maxn; ++i) {
        if (is[i]) prm[k++] = i;
        for (int j = 0; j < k && (i * prm[j] < maxn); ++j) {
            is[i * prm[j]] = 0;
            if (i % prm[j] == 0) break;
        }
    }
    id = k;
}

void getFactors(long long x, vector<pii>& g) {
    g.clear();
    long long tmp = x;
    for (int i = 0; prm[i] <= tmp / prm[i]; i++) {
        if (tmp % prm[i] == 0) {
            pii it = {prm[i], 0};
            while (tmp % prm[i] == 0) {
                it.second++;
                tmp /= prm[i];
            }
            g.push_back(it);
        }
    }
    if (tmp != 1) {
        pii it = {tmp, 1};
        g.push_back(it);
    }
}

int res[maxn];
map<int, int> now;

int quick(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2) res = 1LL * res * a % mod;
        b /= 2;
        a = 1LL * a * a % mod;
    }
    return res;
}

void dfs(int u, int pre) {
    for (auto it : V[u]) {
        int v = it.first;
        if (v == pre) continue;

        vector<pii> g1, g2;
        getFactors(it.second.first, g1);
        getFactors(it.second.second, g2);
        for (auto it2 : g1) {
            int idx = it2.first, num = it2.second;
            if (now[idx] < num) {
                now[idx] = num;
            }
        }

        for (auto it2 : g1) {
            int idx = it2.first, num = it2.second;
            now[idx] -= num;
        }
        for (auto it2 : g2) {
            int idx = it2.first, num = it2.second;
            now[idx] += num;
        }
        dfs(v, u);
        for (auto it2 : g1) {
            int idx = it2.first, num = it2.second;
            now[idx] += num;
        }
        for (auto it2 : g2) {
            int idx = it2.first, num = it2.second;
            now[idx] -= num;
        }
    }
}

void dfs2(int u, int pre) {
    for (auto it : V[u]) {
        int v = it.first;
        if (v == pre) continue;
        res[v] = 1LL * res[u] * it.second.second % mod * quick(it.second.first, mod - 2) % mod;
        dfs2(v, u);
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        now.clear();

        res[1] = 1;
        V.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            V[i].clear();
        }

        for (int i = 1; i < n; i++) {
            int a, b, x, y;
            cin >> a >> b >> x >> y;
            int _g = __gcd(x, y);
            x /= _g, y /= _g;
            V[a].push_back({b, {x, y}});
            V[b].push_back({a, {y, x}});
        }

        dfs(1, 0);
        for (auto it : now) {
            res[1] = 1LL * res[1] * quick(it.first, it.second) % mod;
        }

        dfs2(1, 0);

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            (ans += res[i]) %= mod;
        }
        cout << ans << '\n';
    }
    return 0;
}