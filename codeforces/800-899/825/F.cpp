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
    string s;
    cin >> s;

    int n = s.size();
    vector<int> Next(n + 1);
    vector<vector<int>> cnt(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        Next[0] = -1;
        int ii = 0, j = -1;
        while (ii < n - i) {
            while (j != -1 && s[i + ii] != s[i + j]) j = Next[j];
            Next[++ii] = ++j;
            if (ii % (ii - Next[ii]) == 0) {
                // debug(i, ii, Next[ii]);
                cnt[i][i + ii - 1] = to_string(ii / (ii - Next[ii])).size() + (ii - Next[ii]);
            } else {
                cnt[i][i + ii - 1] = 1 + ii;
            }
        }
    }
    // debug(cnt);
    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
        dp[i] = cnt[0][i];
        for (int j = 1; j <= i; j++) {
            dp[i] = min(dp[i], cnt[j][i] + dp[j - 1]);
        }
    }
    cout << dp[n - 1] << endl;
    return 0;
}