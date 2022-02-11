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

vector<int> ans;

bool to1(int idx);
bool to0(int idx);

vector<int> a;
int n;
bool to1(int idx) {
    if (idx + 2 > n) return false;
    if ((a[idx] ^ a[idx + 1] ^ a[idx + 2]) == 1) {
        ans.push_back(idx);
        a[idx] = a[idx + 1] = a[idx + 2] = 1;
        return true;
    }
    bool f = (a[idx + 2] ? to0(idx + 2) : to1(idx + 2));
    if (!f) return false;
    ans.push_back(idx);
    a[idx] = a[idx + 1] = a[idx + 2] = 1;
    return true;
}

bool to0(int idx) {
    if (idx + 2 > n) return false;

    if ((a[idx] ^ a[idx + 1] ^ a[idx + 2]) == 0) {
        ans.push_back(idx);
        a[idx] = a[idx + 1] = a[idx + 2] = 0;
        return true;
    }
    bool f = (a[idx + 2] ? to0(idx + 2) : to1(idx + 2));
    if (!f) return false;
    ans.push_back(idx);
    a[idx] = a[idx + 1] = a[idx + 2] = 0;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    int T;
    cin >> T;
    while (T--) {
        ans.clear();
        cin >> n;
        a.clear();
        a.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        if (a[1] == 1) {
            if (!to0(1)) {
                cout << "NO\n";
                continue;
            }
        }

        for (int i = 1; i <= n - 2; i++) {
            if (a[i] == 0 && a[i + 1] == 0 && a[i + 2] == 0) continue;
            if ((a[i] ^ a[i + 1] ^ a[i + 2]) == 0) {
                ans.push_back(i);
                a[i] = a[i + 1] = a[i + 2] = 0;
                continue;
            }
            if (a[i] == 1) {
                if (a[i + 2] == 1) {
                    ans.push_back(i - 1);
                    a[i] = a[i + 1] = 0;
                    continue;
                } else {
                    ans.push_back(i);
                    ans.push_back(i - 1);
                    a[i] = 0;
                    a[i + 2] = 1;
                    continue;
                }
            }
        }
        debug(ans);
        debug(a);

        bool f = true;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 1) {
                f = false;
                break;
            }
        }
        if (!f) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        cout << ans.size() << '\n';
        for (auto it : ans) {
            cout << it << ' ';
        }
        cout << '\n';
    }
    return 0;
}