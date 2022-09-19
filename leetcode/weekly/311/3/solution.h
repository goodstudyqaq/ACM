/*
Code generated by https://github.com/goodStudyTnT/leetcode-tester
*/

#if __has_include("../../utils/cpp/help.h")
#include "../../utils/cpp/help.h"
#endif

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

struct Node {
    int nxt[26];
    int cnt;
    Node() {
        memset(nxt, -1, sizeof(nxt));
        cnt = 0;
    }
};

const int maxn = 1e6 + 5;
Node nodes[maxn];
int ncnt;
int root;

int new_node() {
    nodes[ncnt] = Node();
    return ncnt++;
}

void add(string& s) {
    int now = root;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        int go = s[i] - 'a';
        if (nodes[now].nxt[go] == -1) {
            nodes[now].nxt[go] = new_node();
        }
        now = nodes[now].nxt[go];
        nodes[now].cnt++;
    }
}

int work(string& s) {
    int now = root;
    int res = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        int go = s[i] - 'a';
        now = nodes[now].nxt[go];
        res += nodes[now].cnt;
    }
    return res;
}

class Solution {
   public:
    vector<int> sumPrefixScores(vector<string>& s) {
        int n = s.size();
        ncnt = 0;
        root = new_node();

        for (int i = 0; i < n; i++) {
            add(s[i]);
        }

        vector<int> ans(n);

        for (int i = 0; i < n; i++) {
            ans[i] = work(s[i]);
        }
        return ans;
    }
};