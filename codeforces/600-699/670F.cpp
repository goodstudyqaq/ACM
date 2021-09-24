#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

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

string work(int begin_idx, string a, string b) {
    int idx1 = begin_idx, idx2 = a.size() - 1;
    while (idx1 < a.size() && a[idx1] < b[0]) {
        idx1++;
    }
    while (idx2 >= 0 && a[idx2] > b[0]) {
        idx2--;
    }
    string copy_a = a;

    string res1 = a.insert(idx1, b);
    string res2 = copy_a.insert(idx2 + 1, b);
    debug(res1, res2);
    return min(res1, res2);
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a, b;
    cin >> a >> b;
    if (a == "0") {
        cout << 0 << endl;
        return 0;
    }

    int sz = a.size();
    // 长度的长度最多 7
    int length;
    for (int i = 1; i <= 7; i++) {
        int tmp = sz - i;
        int tmp2 = tmp;
        int num = 0;
        while (tmp) {
            tmp /= 10;
            num++;
        }
        if (num == i) {
            length = tmp2;
            break;
        }
    }
    debug(length);
    vector< int > have(10, 0), need(10, 0);
    for (int i = 0; i < sz; i++) {
        have[a[i] - '0']++;
    }
    for (int i = 0; i < b.size(); i++) {
        need[b[i] - '0']++;
    }
    int tmp = length;
    while (tmp) {
        need[tmp % 10]++;
        tmp /= 10;
    }

    for (int i = 0; i < 10; i++) {
        have[i] -= need[i];
    }

    string A = "";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < have[i]; j++) {
            A += to_string(i);
        }
    }
    debug(A, b);

    if (A == "") {
        cout << b << endl;
    } else if (b == "") {
        for (int i = 0; i < A.size(); i++) {
            if (A[i] != '0') {
                swap(A[0], A[i]);
                break;
            }
        }
        cout << A << endl;
    } else {
        if (A[0] == '0' && b[0] == '0') {
            int idx;
            for (int i = 0; i < A.size(); i++) {
                if (A[i] != '0') {
                    idx = i;
                    break;
                }
            }
            swap(A[0], A[idx]);
            debug(A);
            A.insert(idx + 1, b);
            cout << A << endl;
        } else if (A[0] == '0' && b[0] != '0') {
            string res1 = b + A;
            int idx = -1;
            for (int i = 0; i < A.size(); i++) {
                if (A[i] != '0') {
                    idx = i;
                    break;
                }
            }
            if (idx == -1) {
                cout << res1 << endl;
            } else {
                swap(A[idx], A[0]);
                string res2 = work(1, A, b);
                debug(res1, res2);
                res1 = min(res1, res2);
                cout << res1 << endl;
            }

        } else if (A[0] != '0' && b[0] == '0') {
            A.insert(1, b);
            cout << A << endl;
        } else {
            string res = work(0, A, b);
            cout << res << endl;
        }
    }
    return 0;
}
