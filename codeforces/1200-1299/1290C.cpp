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
vector<int> f, val;
const int inf = 0x3f3f3f3f;

int find(int u) {
    return f[u] == u ? f[u] : f[u] = find(f[u]);
}

void un(int u, int v) {
    int fu = find(u), fv = find(v);
    f[fu] = fv;
    val[fv] += val[fu];
    val[fv] = min(val[fv], inf);
}

int n, k;
int Not(int u) {
    return k + u;
}

int getMin(int u) {
    return min(val[find(u)], val[find(Not(u))]);
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    cin >> n >> k >> s;
    f.resize(k * 2 + 1);
    val.resize(k * 2 + 1, 0);

    for (int i = 1; i <= k; i++) {
        f[i] = i;
        f[i + k] = i + k;
        val[i] = 1;
    }
    f[0] = 0;
    val[0] = inf;
    vector<vector<int>> p;
    p.resize(n + 1, vector<int>(2, 0));
    for (int j = 1; j <= k; j++) {
        int m;
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int val;
            cin >> val;
            if (p[val][0] == 0) {
                p[val][0] = j;
            } else {
                p[val][1] = j;
            }
        }
    }
    int ans = 0;
    debug(val.size());
    debug(p);
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '0') {
            if (p[i][1] == 0) {
                // 只有 1 个 一定选
                ans -= getMin(p[i][0]);
                un(0, Not(p[i][0]));
                ans += getMin(p[i][0]);
            } else {
                // 两个中选 1 个
                if (find(p[i][0]) != find(Not(p[i][1]))) {
                    ans -= getMin(p[i][0]) + getMin(p[i][1]);
                    un(p[i][0], Not(p[i][1]));
                    un(p[i][1], Not(p[i][0]));
                    ans += getMin(p[i][0]);
                }
            }
        } else {
            if (p[i][0] == 0) {
                cout << ans << '\n';
                continue;
            }

            if (p[i][1] == 0) {
                // 只有 1 个 一定不选
                ans -= getMin(p[i][0]);
                un(0, p[i][0]);
                ans += getMin(p[i][0]);
            } else {
                // 不选 or 都选
                if (find(p[i][0]) != find(p[i][1])) {
                    ans -= getMin(p[i][0]) + getMin(p[i][1]);
                    un(p[i][0], p[i][1]);
                    un(Not(p[i][0]), Not(p[i][1]));
                    ans += getMin(p[i][0]);
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}