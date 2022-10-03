#include <bits/stdc++.h>

#include "./copypaste/string/trie.hpp"
using namespace std;

/*
https://codeforces.com/contest/1739/submission/174501979
*/

template <int char_size, int margin>
struct AhoCorasick : Trie<char_size, margin> {
    using Trie<char_size, margin>::Trie;

    vector<int> fail;

    void update_node(int node_idx) {
        /*
         * Update node val
         */
        // this->nodes[node_idx].val += this->nodes[fail[node_idx]].val;
        return;
    }

    void build() {
        /*
         * Build failure function.
         */
        queue<int> Q;
        fail.resize(this->nodes.size());
        int root = this->root;
        fail[root] = root;

        for (int i = 0; i < char_size; i++) {
            if (this->nodes[root].nxt[i] == -1) {
                this->nodes[root].nxt[i] = root;
            } else {
                fail[this->nodes[root].nxt[i]] = root;
                Q.push(this->nodes[root].nxt[i]);
            }
        }

        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();

            // Do some update for this node.
            update_node(node);

            for (int i = 0; i < char_size; i++) {
                if (this->nodes[node].nxt[i] == -1) {
                    this->nodes[node].nxt[i] = this->nodes[fail[node]].nxt[i];
                } else {
                    fail[this->nodes[node].nxt[i]] = this->nodes[fail[node]].nxt[i];
                    Q.push(this->nodes[node].nxt[i]);
                }
            }
        }
    }
};