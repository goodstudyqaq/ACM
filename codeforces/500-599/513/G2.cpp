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

    int n, k;
    cin >> n >> k;
    vector<int> p;
    p.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    vector<vector<double>> dp[2];
    dp[0].resize(n + 1, vector<double>(n + 1, 0));
    dp[1].resize(n + 1, vector<double>(n + 1, 0));
    // dp[x][i][j] 搞了 x 次后 a[i] 在 a[j] 前面的概率
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            dp[0][i][j] = 1.0;
        }
    }

    int all = n + n * (n - 1) / 2;
    for (int x = 1; x <= k; x++) {
        int f = x % 2;

        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                dp[f][i][j] = 0;
            }
        }

        for (int l = 1; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                for (int i = 1; i <= n; i++) {
                    for (int j = i + 1; j <= n; j++) {
                        int rev_i = i, rev_j = j;
                        if (l <= i && i <= r) {
                            rev_i = l + r - i;
                        }
                        if (l <= j && j <= r) {
                            rev_j = l + r - j;
                        }
                        if (rev_i > rev_j) swap(rev_i, rev_j);
                        if (l <= rev_i && rev_j <= r) {
                            dp[f][rev_i][rev_j] += (1.0 - dp[f ^ 1][i][j]) / (1.0 * all);
                        } else {
                            dp[f][rev_i][rev_j] += dp[f ^ 1][i][j] / (1.0 * all);
                        }
                    }
                }
            }
        }
    }

    double res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            debug(dp[k % 2][i][j]);
            if (p[i] > p[j]) {
                res += dp[k % 2][i][j];
            } else {
                res += (1.0 - dp[k % 2][i][j]);
            }
        }
    }

    cout << setprecision(9) << fixed;
    cout << res << endl;
}