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

const int mod = 1e9 + 7;
vector<int> a;
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, mx_k;
    cin >> n >> mx_k;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a.begin() + 1, a.begin() + 1 + n);
    vector<vector<vector<int>>> f;
    f.resize(2, vector<vector<int>>(n + 1, vector<int>(mx_k + 1, 0)));
    f[0][0][0] = 1;

    for (int i = 0; i <= n - 1; i++) {
        for (int j = 0; j <= i + 1; j++) {
            for (int k = 0; k <= mx_k; k++) {
                f[(i + 1) % 2][j][k] = 0;
            }
        }
        for (int j = 0; j <= i; j++) {
            for (int k = 0; k <= mx_k; k++) {
                if (f[i % 2][j][k] == 0) continue;
                int t = (a[i + 1] - a[i]) * j;
                if (k + t > mx_k) continue;
                // 起点 + 终点
                (f[(i + 1) % 2][j][k + t] += f[i % 2][j][k]) %= mod;

                // 非起点 + 非终点
                (f[(i + 1) % 2][j][k + t] += 1LL * f[i % 2][j][k] * j % mod) %= mod;

                // 起点
                (f[(i + 1) % 2][j + 1][k + t] += f[i % 2][j][k]) %= mod;

                // 终点
                if (j - 1 >= 0) {
                    (f[(i + 1) % 2][j - 1][k + t] += 1LL * f[i % 2][j][k] * j % mod) %= mod;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= mx_k; i++) {
        ans = (ans + f[n % 2][0][i]) % mod;
    }
    cout << ans << endl;
    return 0;
}