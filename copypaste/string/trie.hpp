#include <bits/stdc++.h>
using namespace std;
template <int char_size>
struct TrieNode {
    vector<int> nxt;
    TrieNode() : {
        nxt.resize(char_size, -1);
    }
};

template <int char_size, int margin>
struct Trie {
    using Node = TrieNode<char_size>;
    vector<Node> nodes;
    int root;

    Trie() : root(0) {
        nodes.push_back(Node());
    }

    void update_direct(int node) {
        /*
         * Update final node
         */
        return;
    }

    void update_child(int node, int child) {
        /*
         * Update node with child
         */
        return;
    }

    void add(const string &s, int s_idx, int node_idx) {
        /*
         * Add string s[s_idx..] to node node_idx by using DFS.
         * You can pass additional arguments to this function, and use them in update_direct and update_child.
         */
        if (s_idx == s.size()) {
            update_directly(node_idx);
        } else {
            const int c = s[s_idx] - margin;
            if (nodes[node_idx].nxt[c] == -1) {
                nodes[node_idx].nxt[c] = nodes.size();
                nodes.push_back(Node());
            }
            add(s, s_idx + 1, nodes[node_idx].nxt[c]);
            update_child(node_idx, nodes[node_idx].nxt[c]);
        }
    }

    void add(const string &s) {
        add(s, 0, root);
    }
};
