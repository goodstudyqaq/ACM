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
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<string> s;
    s.resize(n + 1);
    vector<vector<int>> mi;
    mi.resize(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        int now = 0;
        while (now < s[i].size()) {
            int go = now;
            while (go < s[i].size() && s[i][now] == s[i][go]) {
                go++;
            }
            mi[i][s[i][now] - 'a'] = go - now;
            now = go;
        }
    }

    int LIMIT = 1 << n;
    vector<int> A;
    A.resize(LIMIT);
    vector<int> tmp_mi(26, 2e4 + 5);
    for (int i = 1; i < LIMIT; i++) {
        for (int j = 0; j < 26; j++) {
            tmp_mi[j] = 2e4 + 5;
        }

        for (int j = i; j > 0; j &= (j - 1)) {
            int idx = __builtin_ctz(j);
            for (int j = 0; j < 26; j++) {
                tmp_mi[j] = min(tmp_mi[j], mi[idx][j]);
            }
        }

        int res = 1;
        for (int j = 0; j < 26; j++) {
            res = 1LL * res * (tmp_mi[j] + 1) % mod;
        }
        if (__builtin_parity(i) == 0) {
            res = mod - res;
        }
        A[i] = res;
    }

    vector<int> F;
    F.resize(LIMIT);
    for (int i = 0; i < LIMIT; i++) {
        F[i] = A[i];
    }

    for (int i = 0; i < n; i++) {
        for (int mask = 0; mask < LIMIT; mask++) {
            if (mask & (1 << i)) {
                (F[mask] += F[mask ^ (1 << i)]) %= mod;
            }
        }
    }

    long long ans = 0;
    for (int i = 1; i < LIMIT; i++) {
        int cnt = 0;
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                cnt++;
                sum += j + 1;
            }
        }
        long long tmp = 1LL * F[i] * cnt * sum;
        ans ^= tmp;
    }
    cout << ans << endl;
    return 0;
}