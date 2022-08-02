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
    int n;
    cin >> n;
    vector<char> c(n);
    vector<int> r(n), b(n);
    int the_r = 0, the_b = 0;
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> r[i] >> b[i];
        the_r += r[i];
        the_b += b[i];
    }
    int LIMIT = 1 << n;
    vector<vector<int>> dp(LIMIT, vector<int>(121, -1));
    vector<int> sumr(LIMIT, 0), sumb(LIMIT, 0);
    for (int i = 0; i < LIMIT; i++) {
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                if (c[j] == 'R') {
                    sumr[i]++;
                } else {
                    sumb[i]++;
                }
            }
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i < LIMIT; i++) {
        for (int j = 0; j <= 120; j++) {
            if (dp[i][j] == -1) continue;
            for (int k = 0; k < n; k++) {
                if ((i >> k) & 1) continue;
                int new_s = i | (1 << k);
                int new_r = min(sumr[i], r[k]);
                int new_b = min(sumb[i], b[k]);
                dp[new_s][j + new_r] = max(dp[new_s][j + new_r], dp[i][j] + new_b);
            }
        }
    }
    // debug(dp);

    int res = 1e9;
    for (int i = 0; i <= 120; i++) {
        if (dp[LIMIT - 1][i] != -1) {
            debug(i, dp[LIMIT - 1][i]);
            res = min(res, max(the_r - i, the_b - dp[LIMIT - 1][i]));
        }
    }
    cout << res + n << endl;
    return 0;
}