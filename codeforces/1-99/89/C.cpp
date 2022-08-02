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

const int maxn = 5005;
int father[maxn * 4];

int find(int u) {
    return father[u] < 0 ? u : father[u] = find(father[u]);
}

int n, m;
int get_idx(int x, int y, int dir) {
    return ((x - 1) * m + y - 1) * 4 + dir + 1;
}

int d[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
map<char, int> M = {{'U', 0}, {'D', 1}, {'L', 2}, {'R', 3}};
char c[5] = "DURL";
void add(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int tmpx = x + d[i][0];
        int tmpy = y + d[i][1];
        if (tmpx >= 1 && tmpx <= n && tmpy >= 1 && tmpy <= m) {
            int idx = get_idx(x, y, i);
            int idx2 = get_idx(tmpx, tmpy, i);
            father[idx] = idx2;
        }
    }
}

pair<int, int> get_cor(int idx) {
    idx = (idx - 1) / 4 + 1;
    int x = (idx - 1) / m + 1;
    int y = (idx - 1) % m + 1;
    return {x, y};
}

vector<string> mp, mp2;

bool check(int x, int y) {
    if (mp[x][y] == '.') return false;
    memset(father, -1, sizeof(father));

    for (int i = 1; i <= n; i++) {
        mp2[i] = mp[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[x][y] == '.') {
                add(i, j);
            }
        }
    }
    return true;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    mp.resize(n + 1);
    mp2.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        s = " " + s;
        mp[i] = s;
    }
    int ans_val = 0, ans_num = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (check(i, j)) {
                int nowx = i, nowy = j, nowdir = M[mp2[i][j]];
                int val = 0;
                while (true) {
                    if (mp2[nowx][nowy] != '.') {
                        val++;
                        nowdir = M[mp2[nowx][nowy]];
                    }
                    add(nowx, nowy);
                    mp2[nowx][nowy] = '.';
                    int idx = get_idx(nowx, nowy, nowdir);
                    int go_idx = find(idx);
                    if (go_idx == idx) break;
                    auto it = get_cor(go_idx);
                    nowx = it.first, nowy = it.second;
                }

                if (val > ans_val) {
                    ans_val = val;
                    ans_num = 1;
                } else if (val == ans_val) {
                    ans_num++;
                }
            }
        }
    }
    cout << ans_val << ' ' << ans_num << endl;
    return 0;
}