/*
n 个人坐成一列，每个人都有一个打算喝水的时间点 ti，一个人不到点是不会去喝水的。
另外，饮水机在第一个人座位的左侧，也就是说如果有多人同时要去喝水，那么位置靠左的人会先起身。
一个人在饮水机接水需要时间（但是走路不要时间），每个人接水消耗的时间一样。
由于没人喜欢排队，所以如果一个人发现在他的前方（编号小于他）的任意一个座位空了（说明那个人正在排队），他就会在自己的座位上等待，直到所有在他前方的人都回到座位上。
需要注意的一点是，如果有几个人同时打算起身，编号最靠前的会先起身，而靠后的会坐下。
*/
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

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
typedef pair<int, int> pii;
vector<pii> V;

const int maxn = 1e5 + 5;
long long ans[maxn];
int a[maxn];

int main() {
    // freopen("data.in", "r", stdin);
    int n, p;
    scanf("%d %d", &n, &p);

    int t;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &t);
        a[i] = t;
        V.push_back({t, i});
    }

    sort(V.begin(), V.end());

    set<int> S;
    int now_idx = 0;
    long long now_time = 0;
    int now_chose = -1;
    while (true) {
        debug(now_idx);
        if (now_chose == -1) {
            if (S.empty()) {
                if (now_idx == n) break;
                now_chose = V[now_idx].second;
                now_time = V[now_idx].first;
                now_idx++;
            } else {
                now_chose = *S.begin();
                S.erase(S.begin());
            }
        }

        ans[now_chose] = now_time + p;
        now_time += p;

        bool flag = false;
        while (now_idx < n && V[now_idx].first <= now_time) {
            if (V[now_idx].second < now_chose) {
                now_chose = V[now_idx].second;
                now_idx++;
                flag = true;
                break;
            } else {
                S.insert(V[now_idx].second);
                now_idx++;
            }
        }
        if (!flag) {
            now_chose = -1;
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%lld ", ans[i]);
    }
    puts("");
    return 0;
}