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

string res;
bool check(string& s) {
    int now = 0;
    int n = s.size();
    while (now < n) {
        int go = now;
        while (go < n && s[go] == s[now]) go++;
        if (go == now + 1) {
            res = "";
            res += s[now];
            for (int i = 0; i < now; i++) {
                res += s[i];
            }
            for (int i = now + 1; i < n; i++) {
                res += s[i];
            }
            cout << res << '\n';
            return true;
        }
        now = go;
    }
    return false;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        int n = s.size();
        sort(s.begin(), s.end());

        if (check(s)) {
            continue;
        }

        int now = 0;
        while (now < n && s[now] == s[0]) now++;
        if (now == n || now == 1) {
            cout << s << '\n';
            continue;
        }
        int same_num = now;
        int else_num = n - now;
        if (same_num - 2 > else_num) {
            // 放后面
            string ans = "";
            for (int i = 0; i < same_num - else_num; i++) {
                ans += s[0];
            }
            int go = same_num;
            for (int i = 0; i < else_num; i++) {
                ans += s[go];
                ans += s[0];
                go++;
            }
            cout << ans << '\n';
        } else {
            // 放前面
            string ans = "";
            ans += s[0];
            ans += s[0];
            int go = same_num;
            for (int i = 0; i < same_num - 2; i++) {
                ans += s[go];
                ans += s[0];
                go++;
            }
            while (go < n) {
                ans += s[go];
                go++;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}