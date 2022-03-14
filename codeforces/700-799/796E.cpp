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

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, p, k;
    cin >> n >> p >> k;
    int r;
    cin >> r;
    vector<int> a, b;
    a.resize(n + 1);
    b.resize(n + 1);
    for (int i = 1; i <= r; i++) {
        int tmp;
        cin >> tmp;
        a[tmp] = 1;
    }
    int s;
    cin >> s;
    for (int i = 1; i <= s; i++) {
        int tmp;
        cin >> tmp;
        b[tmp] = 1;
    }

    if (p >= ((n + k - 1) / k) * 2) {
        // 都可以
        int res = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] || b[i]) {
                res++;
            }
        }
        cout << res << endl;
        return 0;
    }

    vector<vector<vector<vector<int>>>> dp;
    // dp[0/1][j][l][r] 考虑前 i%2 道题，已经看了 j 次，a 还有 l 次剩余，b 还有 r 次剩余的最大题数
    const int inf = 1000;
    dp.resize(2, vector<vector<vector<int>>>(p + 1, vector<vector<int>>(k, vector<int>(k, -inf))));
    dp[0][p][0][0] = 0;
    for (int i = 0; i < n; i++) {
        int f = i % 2;
        for (int j = 0; j <= p; j++) {
            for (int l = 0; l < k; l++) {
                for (int r = 0; r < k; r++) {
                    dp[f ^ 1][j][l][r] = -inf;
                }
            }
        }

        for (int j = 0; j <= p; j++) {
            for (int l = 0; l < k; l++) {
                for (int r = 0; r < k; r++) {
                    if (dp[f][j][l][r] >= 0) {
                        // debug(i, j, l, r, dp[f][j][l][r]);
                        // 不看
                        dp[f ^ 1][j][max(l - 1, 0)][max(r - 1, 0)] = max(dp[f ^ 1][j][max(l - 1, 0)][max(r - 1, 0)], dp[f][j][l][r] + ((l > 0 && a[i + 1]) || (r > 0 && b[i + 1])));
                        // 看左边
                        if (j > 0 && a[i + 1] && l == 0) {
                            dp[f ^ 1][j - 1][k - 1][max(r - 1, 0)] = max(dp[f ^ 1][j - 1][k - 1][max(r - 1, 0)], dp[f][j][l][r] + 1);
                        }
                        // 看右边
                        if (j > 0 && b[i + 1] && r == 0) {
                            dp[f ^ 1][j - 1][max(l - 1, 0)][k - 1] = max(dp[f ^ 1][j - 1][max(l - 1, 0)][k - 1], dp[f][j][l][r] + 1);
                        }
                    }
                }
            }
        }
    }
    int res = 0;
    for (int j = 0; j <= p; j++) {
        for (int l = 0; l < k; l++) {
            for (int r = 0; r < k; r++) {
                res = max(res, dp[n % 2][j][l][r]);
            }
        }
    }

    cout << res << endl;
    return 0;
}