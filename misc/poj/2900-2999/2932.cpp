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
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct Node {
    double r, x, y;
};
vector< Node > V;

bool check(int idx1, int idx2) {
    double x = V[idx1].x - V[idx2].x;
    double y = V[idx1].y - V[idx2].y;
    double r = V[idx1].r + V[idx2].r;
    return x * x + y * y <= r * r;
}

int main() {
    // freopen("data.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int N;
    cin >> N;
    V.resize(N + 1);
    vector< pair< double, int > > event;
    for (int i = 1; i <= N; i++) {
        cin >> V[i].r >> V[i].x >> V[i].y;
        event.push_back(make_pair(V[i].x - V[i].r, i));
        event.push_back(make_pair(V[i].x + V[i].r, i + N));
    }

    sort(event.begin(), event.end());
    set< pair< double, int > > S;
    vector< int > ans;
    for (int i = 0; i < event.size(); i++) {
        pair< double, int > it = event[i];
        // cout << i << ' ' << it.first << ' ' << it.second << endl;
        if (it.second <= N) {
            set< pair< double, int > >::iterator it2 = S.lower_bound(make_pair(V[it.second].y, it.second));
            if (it2 != S.end() && check(it2->second, it.second)) continue;
            if (it2 != S.begin()) {
                it2--;
                if (check(it2->second, it.second)) continue;
            }
            ans.push_back(it.second);
            S.insert(make_pair(V[it.second].y, it.second));
        } else {
            if (S.count(make_pair(V[it.second - N].y, it.second - N))) {
                S.erase(make_pair(V[it.second - N].y, it.second - N));
            }
        }
    }

    cout << ans.size() << endl;
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        if (i != 0) {
            cout << " ";
        }
        cout << ans[i];
    }
    cout << endl;
}