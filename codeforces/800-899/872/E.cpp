

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdlib>
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;
unordered_set< int > diff_x, diff_y;
vector< bool > vis;

int quick(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2) res = 1LL * res * a % mod;
        b /= 2;
        a = 1LL * a * a % mod;
    }
    return res;
}
typedef pair< int, int > pii;
vector< pii > nodes;

vector< vector< int > > V;
bool have_circle;
void dfs(int u, int pre) {
    vis[u] = 1;
    diff_x.insert(nodes[u].first);
    diff_y.insert(nodes[u].second);
    for (auto v : V[u]) {
        if (v == pre) continue;
        if (vis[v])
            have_circle = true;
        else
            dfs(v, u);
    }
}

int main() {
    int n;
    cin >> n;
    unordered_map< int, vector< pair< int, int > > > X, Y;
    nodes.resize(n + 1);
    vis.resize(n + 1, 0);
    V.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        nodes[i] = {x, y};
        X[x].push_back({y, i});
        Y[y].push_back({x, i});
    }

    for (auto it : X) {
        sort(it.second.begin(), it.second.end());
        for (int i = 0; i < it.second.size(); i++) {
            // 连左边
            int idx = i - 1;
            if (idx >= 0) {
                V[it.second[i].second].push_back(it.second[idx].second);
            }
            // 右边
            idx = i + 1;
            if (idx < it.second.size()) {
                V[it.second[i].second].push_back(it.second[idx].second);
            }
        }
    }

    for (auto it : Y) {
        sort(it.second.begin(), it.second.end());
        for (int i = 0; i < it.second.size(); i++) {
            // 连左边
            int idx = i - 1;
            if (idx >= 0) {
                V[it.second[i].second].push_back(it.second[idx].second);
            }
            idx = i + 1;
            if (idx < it.second.size()) {
                V[it.second[i].second].push_back(it.second[idx].second);
            }
        }
    }

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 0; j < V[i].size(); j++) {
    //         cout << i << ' ' << V[i][j] << endl;
    //     }
    // }

    int ans = 1;
    // 判环
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            diff_x.clear();
            diff_y.clear();
            have_circle = false;
            dfs(i, -1);
            int sz = diff_x.size() + diff_y.size();
            if (have_circle) {
                ans = 1LL * ans * quick(2, sz) % mod;
            } else {
                ans = 1LL * ans * (quick(2, sz) - 1) % mod;
            }
        }
    }

    ans = (ans + mod) % mod;
    cout << ans << endl;
    return 0;
}