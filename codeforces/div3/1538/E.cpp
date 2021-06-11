#include <bits/stdc++.h>

using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast< int >(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template < size_t N >
string to_string(bitset< N > v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast< char >('0' + v[i]);
    }
    return res;
}

template < typename A >
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

template < typename A, typename B >
string to_string(pair< A, B > p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
    return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

struct node {
    string pre, suf;

    long long val;
    node(string _p, string _s, long long _v)
        : pre(_p), suf(_s), val(_v) {}
    node() {}
};
map< string, node > M;

string haha = "haha";

bool check1(string a, string b) {
    debug(a, b);
    if (a.size() < b.size()) return false;
    for (int i = 0; i < b.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool check2(string a, string b) {
    debug(a, b);
    if (a.size() < b.size()) return false;
    int sz = b.size();
    for (int i = 0; i < sz; i++) {
        if (a[a.size() - 1 - i] != b[sz - 1 - i]) {
            return false;
        }
    }
    return true;
}

int main() {
    // freopen("data.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        M.clear();
        int n;
        cin >> n;
        string a, b, c;
        for (int i = 1; i <= n; i++) {
            cin >> a >> b >> c;
            if (b != "=") {
                node tmp = node(c, c, 0);
                if (c.find(haha) != string::npos) {
                    tmp.val++;
                }
                M[a] = tmp;
            } else {
                string d, e;
                cin >> d >> e;
                node tmp1 = M[c];
                node tmp2 = M[e];

                node c;
                c.val = tmp1.val + tmp2.val;
                c.pre = tmp1.pre;
                c.suf = tmp2.suf;

                if (tmp1.pre.size() < 3) {
                    c.pre += tmp2.pre;
                }
                if (tmp2.suf.size() < 3) {
                    c.suf = tmp1.suf + tmp2.suf;
                }

                for (int i = 1; i < 4; i++) {
                    string tmps = haha.substr(0, i);
                    string tmps2 = haha.substr(i, 4 - i);
                    if (check2(tmp1.suf, tmps) && check1(tmp2.pre, tmps2)) {
                        c.val++;
                    }
                }
                M[a] = c;
            }
        }
        cout << M[a].val << endl;
    }
}