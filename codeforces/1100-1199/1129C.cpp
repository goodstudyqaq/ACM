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
string s;
set<string> invalid{"1100", "1010", "0111", "1111"};
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int m;
    cin >> m;
    s.resize(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> s[i];
    }
    reverse(s.begin() + 1, s.begin() + 1 + m);
    vector<vector<int>> sum;
    sum.resize(m + 1, vector<int>(m + 1, 0));
    for (int len = 1; len <= m; len++) {
        for (int l = 1; l + len - 1 <= m; l++) {
            int r = l + len - 1;
            int res = 0;
            string now = "";
            int now_idx = l;
            while (now_idx <= r && now.size() < 4) {
                now += s[now_idx];
                if (!invalid.count(now)) {
                    if (now_idx == r) {
                        res = (res + 1) % mod;
                    } else {
                        res = (res + sum[now_idx + 1][r]) % mod;
                    }
                }
                now_idx++;
            }
            sum[l][r] = res;
        }
    }
    debug(sum);

    vector<vector<int>> sum2;
    sum2.resize(m + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= m; i++) {
        int res = 0;
        for (int j = i; j <= m; j++) {
            (res += sum[i][j]) %= mod;
            sum2[i][j] = res;
        }
    }

    reverse(s.begin() + 1, s.begin() + 1 + m);

    vector<vector<int>> lcs;
    lcs.resize(m + 1, vector<int>(m + 1, 0));
    vector<int> lcs_max;
    lcs_max.resize(m + 1, 0);

    for (int i = 1; i <= m; i++) {
        int mx = 0;
        for (int j = 1; j < i; j++) {
            if (s[i] == s[j]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            } else {
                lcs[i][j] = 0;
            }
            mx = max(mx, lcs[i][j]);
        }
        lcs_max[i] = mx;
    }
    debug(lcs_max);
    debug(sum2);

    vector<int> ans;
    ans.resize(m + 1, 0);
    int now = 0;
    for (int i = m; i >= 1; i--) {
        int ans_idx = m - i + 1;
        (now += sum2[i][m]) %= mod;
        int equal_len = lcs_max[ans_idx];
        debug(now, equal_len);
        if (equal_len != 0)
            (now -= sum2[i][i + equal_len - 1]) %= mod;
        ans[ans_idx] = now;
    }
    for (int i = 1; i <= m; i++) {
        ans[i] = (ans[i] + mod) % mod;
        cout << ans[i] << '\n';
    }
    return 0;
}