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

vector<int> x, b;
vector<double> dp;
vector<int> pre;

int n, l;
bool check(double val) {
    for (int i = 1; i <= n; i++) {
        dp[i] = sqrt(fabs(x[i] - l)) - val * b[i];
        pre[i] = 0;
        for (int j = 1; j < i; j++) {
            double tmp = sqrt(fabs(x[i] - x[j] - l)) - val * b[i] + dp[j];
            if (dp[i] > tmp) {
                dp[i] = tmp;
                pre[i] = j;
            }
        }
    }
    return dp[n] > 0;
}

void out() {
    vector<int> ans;
    int now = n;
    while (now != 0) {
        ans.push_back(now);
        now = pre[now];
    }
    reverse(ans.begin(), ans.end());
    for (auto it : ans) {
        cout << it << ' ';
    }
    cout << endl;
}

int main() {
    // freopen("data.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> l;
    x.resize(n + 1);
    b.resize(n + 1);
    dp.resize(n + 1);
    pre.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> b[i];
    }
    double l = 0, r = 1e6 + 1;
    for (int t = 1; t <= 100; t++) {
        double mid = (l + r) / 2;
        if (check(mid)) {  // a - b * mid > 0 -> mid < a / b
            l = mid;
        } else {
            r = mid;
        }
    }
    debug(l);
    out();
    return 0;
}