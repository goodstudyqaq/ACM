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

vector<long long> ten;
vector<pair<long long, string>> work(vector<int>& num, bool f) {
    int n = num.size();
    int LIMIT = 1 << n;
    vector<pair<long long, string>> res(n + 1, {-1, ""});
    for (int i = 0; i < LIMIT; i++) {
        long long v1 = 0, v2 = 0;
        int num1 = 0;
        string tmp = "";
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                v1 = v1 * 10 + num[j];
                num1++;
                tmp += "H";
            } else {
                v2 = v2 * 10 + num[j];
                tmp += "M";
            }
        }
        if (f) {
            v1 *= ten[n - num1];
            v2 *= ten[num1];
        }
        v1 += v2;
        if (res[num1].first < v1) {
            res[num1].first = v1;
            res[num1].second = tmp;
        }
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    ten.resize(n + 1);
    vector<int> num1, num2;
    for (int i = 0; i < n; i++) {
        num1.push_back(s[i] - '0');
        num2.push_back(s[i + n] - '0');
    }

    ten[0] = 1;
    for (int i = 1; i <= n; i++) {
        ten[i] = ten[i - 1] * 10;
    }

    auto V1 = work(num1, true);
    auto V2 = work(num2, false);

    long long res = -1;
    string ans;
    debug(V1);
    debug(V2);

    for (int i = 0; i <= n; i++) {
        long long tmp = V1[i].first + V2[n - i].first;
        if (res < tmp) {
            res = tmp;
            ans = V1[i].second + V2[n - i].second;
        }
    }
    debug(res);
    cout << ans << endl;
    return 0;
}