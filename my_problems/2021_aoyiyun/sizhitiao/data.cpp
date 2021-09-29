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

// 验证正确性
// data1 ~ data5

bool check() {
    int val = rand() % 1000;
    return val < 400;
}

void work1() {
    int n = 100000;
    cout << n << endl;

    // 总和为 sum
    int sum = rand() % 10000;
    bool f = rand() % 2;
    if (f) sum *= -1;
    if (sum % 2) {
        sum++;
    }

    int half = sum / 2;
    while (true) {
        int now = 0;
        for (int i = 1; i <= n; i++) {
            if (i == n) {
                int tmp = sum - now;
                tmp = min(tmp, 10000);
                tmp = max(tmp, -10000);
                cout << tmp << ' ';
                now += tmp;
                continue;
            }
            if (check()) {
                // 变成 half
                int tmp = half - now;
                tmp = min(tmp, 10000);
                tmp = max(tmp, -10000);
                cout << tmp << ' ';
                now += tmp;
            } else {
                int val = rand() % 10001;
                bool f = rand() % 2;
                if (f) val *= -1;
                cout << val << ' ';
                now += val;
            }
        }
        if (now == sum) break;
    }
}

int main() {
    srand(time(NULL));
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("data5.in", "w", stdout);
    work1();
}