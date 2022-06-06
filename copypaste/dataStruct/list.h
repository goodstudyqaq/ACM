#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Node {
    int next, last;
    T w;
    Node(T _w = T(), int _next = -1, int _last = -1) : w(_w), next(_next), last(_last) {}
};

template <typename T>
struct List {
    vector<Node<T>> nodes;
    Node<T> ed;
    int init() {
        nodes.clear();
        ed = Node<T>();
        nodes.emplace_back(ed);
        return nodes.size() - 1;
    }

    void link(int a, int b) {
        nodes[a].next = b;
        nodes[b].last = a;
    }

    int new_node(int idx, char _w) {
        Node<T> it = Node<T>(_w);
        nodes.emplace_back(it);
        int sz = nodes.size() - 1;
        int last = nodes[idx].last;
        if (last != -1) {
            link(last, sz);
        }
        link(sz, idx);
        return sz;
    }

    int erase_node(int idx) {
        int last = nodes[idx].last, next = nodes[idx].next;

        if (last != -1) {
            nodes[last].next = -1;
        }
        if (next != -1) {
            nodes[next].last = -1;
        }

        if (last != -1 && next != -1) {
            link(last, next);
        }
        return last;
    }
};
