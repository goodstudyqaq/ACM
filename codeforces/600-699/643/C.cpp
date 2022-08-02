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

vector<int> t;
vector<long long> sum;
vector<double> val, sum1;
vector<vector<double>> dp;

double getslope(int p, int q, int j) {
    int f = j & 1;
    return ((dp[f][q] - val[q] + sum1[q] * sum[q]) - (dp[f][p] - val[p] + sum1[p] * sum[p])) / (sum[q] - sum[p]);
}

double getk(int idx) {
    return sum1[idx];
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    t.resize(n + 1);
    sum.resize(n + 1, 0);
    val.resize(n + 1, 0);
    sum1.resize(n + 1, 0);
    dp.resize(2, vector<double>(n + 1, 4e15));
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
        sum[i] = sum[i - 1] + t[i];
        val[i] = val[i - 1] + 1.0 * sum[i] / t[i];
        sum1[i] = sum1[i - 1] + 1.0 / t[i];
    }
    dp[0][0] = 0;

    for (int j = 1; j <= k; j++) {
        vector<int> Q(n + 1);
        int first = 0, tail = 0;
        Q[tail] = j - 1;
        int f = j & 1;
        for (int i = j; i <= n; i++) {
            while (first < tail && getslope(Q[first], Q[first + 1], j - 1) <= getk(i)) {
                first++;
            }
            dp[f][i] = dp[f ^ 1][Q[first]] + val[i] - val[Q[first]] - (sum1[i] - sum1[Q[first]]) * sum[Q[first]];
            debug(j, i, dp[f][i], Q[first]);
            while (first < tail && getslope(Q[tail], i, j - 1) <= getslope(Q[tail - 1], Q[tail], j - 1)) {
                tail--;
            }
            Q[++tail] = i;
        }
    }

    cout << fixed << setprecision(6);
    cout << dp[k & 1][n] << '\n';
    return 0;
}