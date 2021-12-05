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

#define lowbit(x) x & -x

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    int cnt = 0;
    vector<double> p;
    p.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        if (p[i] > 0) {
            cnt++;
        }
    }

    if (cnt <= k) {
        for (int i = 0; i < n; i++) {
            if (p[i] == 0) {
                cout << 0 << ' ';
            } else {
                cout << 1 << ' ';
            }
        }
        cout << endl;
        return 0;
    }

    int LIMIT = 1 << n;
    vector<double> P(LIMIT, 0);
    vector<int> num(LIMIT, 0);

    for (int i = 0; i < n; i++) {
        P[1 << i] = p[i];
        num[1 << i] = 1;
    }

    for (int i = 1; i < LIMIT; i++) {
        if (num[i]) continue;
        P[i] = P[i - (lowbit(i))] + P[lowbit(i)];
        num[i] = num[i - (lowbit(i))] + num[lowbit(i)];
    }
    for (int i = 0; i < LIMIT; i++) {
        debug(i, P[i], num[i]);
    }

    vector<double> ans(n);

    vector<double> dp(LIMIT, 0);
    dp[0] = 1;
    for (int i = 1; i < LIMIT; i++) {
        if (num[i] > k) continue;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                dp[i] += dp[i - (1 << j)] * (p[j] / (1.0 - P[i - (1 << j)]));
            }
        }
        if (num[i] == k) {
            for (int j = 0; j < n; j++) {
                if ((i >> j) & 1) {
                    ans[j] += dp[i];
                }
            }
        }
    }
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}